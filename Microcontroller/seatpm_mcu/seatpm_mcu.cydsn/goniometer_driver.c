/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-01-31
 *
 * File Name: 
 *      goniometer_driver.c
 * File Description:
 *      
 * ============================================================================
*/

#include "project.h"
#include "goniometer_driver.h"

extern uint8 g_a0_Buffer[BUFFER_SIZE];
extern uint8 g_a1_Buffer[BUFFER_SIZE];
extern uint8 g_b0_Buffer[BUFFER_SIZE];
extern uint8 g_b1_Buffer[BUFFER_SIZE];

void InitializeGoniometerTranferConfigs(struct GoniometerTransferConfigs myConfigs)
{
    /* buffer */
    myConfigs.a0.buffer = g_a0_Buffer;
    myConfigs.a1.buffer = g_a1_Buffer;
    myConfigs.b0.buffer = g_b0_Buffer;
    myConfigs.b1.buffer = g_b1_Buffer;
    
    /* bufferSize */ 
    myConfigs.a0.bufferSize = BUFFER_SIZE;
    myConfigs.a1.bufferSize = BUFFER_SIZE;
    myConfigs.b0.bufferSize = BUFFER_SIZE;
    myConfigs.b1.bufferSize = BUFFER_SIZE;
    
    /* Address */
    myConfigs.a0.slaveAddress = A0_ADDR;
    myConfigs.a1.slaveAddress = A1_ADDR;
    myConfigs.b0.slaveAddress = B0_ADDR;
    myConfigs.b1.slaveAddress = B1_ADDR;
    
    /* Tranfer Pending */
    myConfigs.a0.xferPending = false;
    myConfigs.a1.xferPending = false;
    myConfigs.b0.xferPending = false;
    myConfigs.b1.xferPending = false;
}

bool Accel_MasterRead(CySCB_Type base,
                      cy_stc_scb_i2c_master_xfer_config_t xferConfig,
                      cy_stc_scb_i2c_context_t i2cContext,
                      uint32_t byteCount) 
{
    // Low-Level API code taken from 
    // file:///C:/Program%20Files%20(x86)/Cypress/PDL/3.1.0/
    //      doc/pdl_api_reference_manual/html/group__group__scb__i2c.html
    // and modified.

    if( (byteCount > sizeof(xferConfig.buffer)) ||
        (byteCount == 0) )
    {
        return false;
    }
    
    cy_en_scb_i2c_status_t status;

    /* Wait 100 ms until operation completion */
    uint32_t timeout = 100UL;
    /* Send Start condition, address and receive ACK/NACK response from slave*/
    status = Cy_SCB_I2C_MasterSendStart(&base,
                                        xferConfig.slaveAddress,
                                        CY_SCB_I2C_WRITE_XFER,
                                        timeout,
                                        &i2cContext);
    
    if (CY_SCB_I2C_SUCCESS == status)
    {
        uint32_t bytesRead = 0UL;
        cy_en_scb_i2c_command_t cmd = CY_SCB_I2C_ACK;
        /* Read data from the slave into the buffer */
        do
        {
            if (bytesRead == byteCount-1UL)
            {
                /* The last byte must be NACKed */
                cmd = CY_SCB_I2C_NAK;
            }
            /* Read byte and generate ACK / or prepare for NACK */
            status = Cy_SCB_I2C_MasterReadByte(&base, 
                                               cmd, 
                                               &xferConfig.buffer[bytesRead], 
                                               timeout, 
                                               &i2cContext);
            ++bytesRead;
        }
        while((status == CY_SCB_I2C_SUCCESS) && (bytesRead < byteCount));
    }
    /* Check status of transaction */
    if ((status == CY_SCB_I2C_SUCCESS)           ||
        (status == CY_SCB_I2C_MASTER_MANUAL_NAK) ||
        (status == CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK))
    {
        /* Send Stop condition on the bus */
        status = Cy_SCB_I2C_MasterSendStop(&base, timeout, &i2cContext);
        if (status == CY_SCB_I2C_SUCCESS)
        {
            /* Process received data */
            // Not doing any data processing - left to caller! -Austin
        }
    }
    else
    {
        /* Other statuses do not require any actions.
        * The received data should dropped.
        */
    }

    return true;
}

bool Accel_MasterWrite(CySCB_Type base,
                       cy_stc_scb_i2c_master_xfer_config_t xferConfig,
                       cy_stc_scb_i2c_context_t i2cContext,
                       uint32_t byteCount)
{

    // Low-Level API code taken from 
    // file:///C:/Program%20Files%20(x86)/Cypress/PDL/3.1.0/
    //      doc/pdl_api_reference_manual/html/group__group__scb__i2c.html
    // and modified.
    
    if( (byteCount > sizeof(xferConfig.buffer)) ||
        (byteCount == 0) )
    {
        return false;
    }

    cy_en_scb_i2c_status_t status;

    /* Wait 100 ms until operation completion */
    uint32_t timeout = 100UL;

    /* Send Start condition, address and receive ACK/NACK response from slave*/
    status = Cy_SCB_I2C_MasterSendStart(&base,
                                        xferConfig.slaveAddress, 
                                        CY_SCB_I2C_WRITE_XFER, 
                                        timeout, 
                                        &i2cContext);

    if (CY_SCB_I2C_SUCCESS == status)
    {
        uint32_t bytesWritten = 0UL; 
        /* Write data into the slave from the buffer */
        do
        {
            /* Write byte and receive ACK/NACK response */
            status = Cy_SCB_I2C_MasterWriteByte(&base,
                                                xferConfig.
                                                    buffer[bytesWritten], 
                                                timeout, 
                                                &i2cContext);
            ++bytesWritten;
        }
        while((status == CY_SCB_I2C_SUCCESS) && (bytesWritten < byteCount));
    }
    /* Check status of transaction */
    if ((status == CY_SCB_I2C_SUCCESS)           ||
        (status == CY_SCB_I2C_MASTER_MANUAL_NAK) ||
        (status == CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK))
    {
        /* Send Stop condition on the bus */
        status = Cy_SCB_I2C_MasterSendStop(&base, timeout, &i2cContext);
        if (status == CY_SCB_I2C_SUCCESS)
        {
            /* Data has been written into the slave */
        }
    }
    else
    {
        /* Other statuses do not require any actions */
    }
    
    return true;
}

/* [] END OF FILE */
