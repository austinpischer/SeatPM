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
 *      main_cm0p.c
 * File Description:
 *      Main function for the CM0p (Core 0) processor. Operation begins here.
 *
 * ============================================================================
*/
#include "project.h"
#include "goniometer_driver.h"

//=============================================================================
// Global Variables
//=============================================================================
// All global variables should be named with a preceding "g_"

// Accelerometer RX/TX buffers
// The SeatPM has 2 goniometers with 2 accelerometers each.
// Each accelerometer needs a read buffer and a write buffer.
//      Thus, a/b refers to the goniometer
//      and 0/1 refers to each accelerometer in the goniometer 

uint8 g_a0_Buffer[BUFFER_SIZE];
uint8 g_a1_Buffer[BUFFER_SIZE];
uint8 g_b0_Buffer[BUFFER_SIZE];
uint8 g_b1_Buffer[BUFFER_SIZE];

//=============================================================================
// Main Function (Core 0)
//=============================================================================
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    struct GoniometerTransferConfigs configs;
    InitializeGoniometerTranferConfigs(configs);
    
    goni_a_MasterWrite(&configs.a0);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
