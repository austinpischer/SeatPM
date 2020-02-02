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

/* ============================================================================
 *
 */
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


/* [] END OF FILE */
