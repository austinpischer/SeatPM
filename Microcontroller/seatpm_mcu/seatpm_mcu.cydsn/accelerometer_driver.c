/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-02-01
 *
 * File Name: 
 *      accelerometer_driver.h
 * File Description:
 *      
 * ============================================================================
*/

#include "accelerometer_driver.h"


/******************************************************************************
 *
 */
bool Accel_MasterRead(CySCB_Type *hw,
                      cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                      cy_stc_scb_i2c_context_t *i2cContext,
                      uint32_t byteCount) 
{
    // Low-Level API code taken from 
    // file:///C:/Program%20Files%20(x86)/Cypress/PDL/3.1.0/
    //      doc/pdl_api_reference_manual/html/group__group__scb__i2c.html
    // and modified.

    if( (byteCount > sizeof(xferConfig->buffer)) ||
        (byteCount == 0) )
    {
        return false;
    }
    
    cy_en_scb_i2c_status_t status;

    /* Wait 100 ms until operation completion */
    uint32_t timeout = 100UL;
    /* Send Start condition, address and receive ACK/NACK response from slave*/
    status = Cy_SCB_I2C_MasterSendStart(hw,
                                        xferConfig->slaveAddress,
                                        CY_SCB_I2C_WRITE_XFER,
                                        timeout,
                                        i2cContext);
    
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
            status = Cy_SCB_I2C_MasterReadByte(hw, 
                                               cmd, 
                                               &xferConfig->buffer[bytesRead], 
                                               timeout, 
                                               i2cContext);
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
        status = Cy_SCB_I2C_MasterSendStop(hw, timeout, i2cContext);
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


/******************************************************************************
 *
 */
bool Accel_MasterWrite(CySCB_Type *hw,
                       cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                       cy_stc_scb_i2c_context_t *i2cContext,
                       uint32_t byteCount)
{

    // Low-Level API code taken from 
    // file:///C:/Program%20Files%20(x86)/Cypress/PDL/3.1.0/
    //      doc/pdl_api_reference_manual/html/group__group__scb__i2c.html
    // and modified.
    
    if( (byteCount > sizeof(xferConfig->buffer)) ||
        (byteCount == 0) )
    {
        return false;
    }

    cy_en_scb_i2c_status_t status;

    /* Wait 100 ms until operation completion */
    uint32_t timeout = 100UL;

    /* Send Start condition, address and receive ACK/NACK response from slave*/
    status = Cy_SCB_I2C_MasterSendStart(hw,
                                        xferConfig->slaveAddress, 
                                        CY_SCB_I2C_WRITE_XFER, 
                                        timeout, 
                                        i2cContext);

    if (CY_SCB_I2C_SUCCESS == status)
    {
        uint32_t bytesWritten = 0UL; 
        /* Write data into the slave from the buffer */
        do
        {
            /* Write byte and receive ACK/NACK response */
            status = Cy_SCB_I2C_MasterWriteByte(hw,
                                                xferConfig->
                                                    buffer[bytesWritten], 
                                                timeout, 
                                                i2cContext);
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
        status = Cy_SCB_I2C_MasterSendStop(hw, timeout, i2cContext);
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

/******************************************************************************
 *
 */
void Accel_ReadDataRegisters(CySCB_Type *hw,
                             cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                             cy_stc_scb_i2c_context_t *i2cContext)
{
    // First, write first ADXL345 Register Number you want to read
    xferConfig->buffer[0] = DATAX0;
    Accel_MasterWrite(hw, xferConfig, i2cContext, 1); // Write 1 byte
    
    // Then, read as many bytes of data as needed:
    // (address increments automatically, as data registers are subsequent)
    // DATAX0 through DATAZ1, 6 total bytes to read
    Accel_MasterRead(hw, xferConfig, i2cContext, 6);
    // Accel data is now in xferConfig.buffer[0], … , xferConfig.buffer[5]
}

/******************************************************************************
 *
 */
void Accel_WriteConfigRegister(const uint8 RegisterAddress, 
                                uint8 value, 
                                CySCB_Type *hw,
                                cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                                cy_stc_scb_i2c_context_t *i2cContext)
{
    xferConfig->buffer[0] = RegisterAddress;
    xferConfig->buffer[1] = value;
    Accel_MasterWrite(hw, xferConfig, i2cContext, 2); // Write 2 bytes
}

/*******************************************************************************
 * Function:    void SetUpAccelerometer()
 * 
 * Description: Writes values to all the various accelerometer config registers.
 */
void SetUpAccelerometer(CySCB_Type *hw,
                        cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                        cy_stc_scb_i2c_context_t *i2cContext)
{
    /* A setting of 0 in the measure bit places the part into standby mode,
     * and a setting of 1 places the part into measurement mode. The
     * ADXL345 powers up in standby mode with minimum power consumption.
     */
    const uint8 MeasurementMode = 0b00001000;
    Accel_WriteConfigRegister(POWER_CTL, MeasurementMode, hw, xferConfig, i2cContext);

    /*  
     *  Setting
     *  D1  D0  g Range
     *  0   0   +- 2g
     *  0   1   +- 4g
     *  1   0   +- 8g
     *  1   1   +- 16g 
     * 
     * Defines the range of measurement
     * In 2g mode,
     *  +511 means 2g,
     *  -511 means -2g
     * In 16g mode,
     *  +511 means 16g,
     *  -511 means -16g
     * 
     * Austin: 
     * In 2g mode, 1g = 255
     * In 4g mode, 1g = 217
     * In 8g mode, 1g = 63
     * In 16g mode, 1g = 31
     * 
     * We get the least noise on every axis in 16g mode, so lets use that.
     * 
     */
    uint8 DataRange = 0b00000011;
    Accel_WriteConfigRegister(DATA_FORMAT, DataRange, hw, xferConfig, i2cContext);

}


/* [] END OF FILE */
