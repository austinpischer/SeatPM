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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    //========================================================================
    // Screen Startup Code
    Screen_Start();
    char TestString[] = "Test";
    Screen_PrintString(TestString);

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
