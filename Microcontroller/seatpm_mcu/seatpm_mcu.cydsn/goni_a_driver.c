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
 *      goni_a_driver.c
 * File Description:
 *      
 * ============================================================================
*/

#include "goni_a_driver.h"

void goni_a_ISR()
{
    goni_a_Interrupt();
}

/* ============================================================================
 *
 */
bool goni_a_isMasterBusy()
{
    /* MasterGetStatus() returns a series of bits:
     * "Each I2C master status is encoded in a separate bit, 
     *  therefore multiple bits may be set to indicate the current status."
     * CY_SCB_I2C_MASTER_BUSY is (0x00010000UL), so we AND that macro
     *  with the returned status. 
     * If the result of the AND is 1, the master I2C device is 
     *  busy transmitting.
     * If the result of the AND is 0, the master I2C device is not busy.
     * Therefore, we return if the AND result is NOT zero,
     *  meaning master is busy.
     */
    return(0 != (goni_a_MasterGetStatus() & CY_SCB_I2C_MASTER_BUSY));
}


/* ============================================================================
 *
 */
bool goni_a_Read(transfer_config config)
{
    i2c_status readStatus;
    
    readStatus = goni_a_MasterRead(&config);
    
    if(readStatus != CY_SCB_I2C_SUCCESS)
    {
        return false;
    }
    
    // "The buffer must not be modified 
    // and must stay allocated until read operation completion."
    // Thus, wait until Prmary I2C is not busy.
    while(goni_a_isMasterBusy())
    {
        // Do nothing while busy
    }
    
    return true;
}

/* ============================================================================
 *
 */
bool goni_a_Write(transfer_config config, uint8 numberOfBytes)
{
    i2c_status writeStatus;
    
    writeStatus = goni_a_MasterWrite(&config);
    
    if(writeStatus != CY_SCB_I2C_SUCCESS)
    {
        return false;
    }
    
    // "The buffer must not be modified 
    // and must stay allocated until read operation completion."
    // Thus, wait until Prmary I2C is not busy.
    while(goni_a_isMasterBusy())
    {
        // Do nothing while busy
    }
    
    return true;
}

/* ============================================================================
 *
 */




/* [] END OF FILE */
