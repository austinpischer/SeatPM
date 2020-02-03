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

uint8 g_goni_a_thigh_accel_Buffer[BUFFER_SIZE];
uint8 g_goni_a_shank_accel_Buffer[BUFFER_SIZE];


//=============================================================================
// Main Function (Core 0)
//=============================================================================
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    struct goni_configs configs;
    InitializeGoniConfigs(&configs,
                          g_goni_a_thigh_accel_Buffer,
                          g_goni_a_shank_accel_Buffer);
    InitializeGoniAccels(&configs);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
