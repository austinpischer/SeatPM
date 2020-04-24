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

#include "user_interface_buttons.h"
#include "austin_debug.h"

CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin)
{
    DEBUG_PRINT("Confirm Button Pressed\r\n");
    SCREEN_DEBUG("Confirm");
}

CY_ISR_PROTO(Button_Back_ISR_Handler_Austin)
{
    DEBUG_PRINT("Back Button Pressed\r\n");
    SCREEN_DEBUG("Confirm");
}
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin)
{
    DEBUG_PRINT("Increment Button Pressed\r\n");
    SCREEN_DEBUG("Confirm");
}

CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin)
{
    DEBUG_PRINT("Decrement Button Pressed\r\n");
    SCREEN_DEBUG("Confirm");
}



/* [] END OF FILE */
