/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "austin_debug.h"
#include "goniometer_driver.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    /* Hardware Startup */
    I2C_Start();
    Screen_Start();
    
    /* Goniometer Setup */
    Goniometer KneeGoniometer;
    
    
    #ifdef AUSTIN_DEBUG
    //====== Screen Test Code =====
    DEBUG_PRINT("Hello, World!");
    CyDelay(2000); // Wait 2 seconds
    
    DEBUG_PRINT("Init Goni");
    
    
    //=====
    #endif
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
