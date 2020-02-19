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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    Screen_Start();
    
    #ifdef AUSTIN_DEBUG
    //====== Screen Test Code =====
    DEBUG_PRINT("Hello, World!"); 
    #endif
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
