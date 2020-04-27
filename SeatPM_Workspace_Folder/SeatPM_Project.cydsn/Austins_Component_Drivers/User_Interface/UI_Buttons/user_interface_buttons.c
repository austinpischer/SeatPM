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
#include "user_interface_fsm.h" 

/* Helper function for button interrupt implementations */ 
void UI_Button_Dispatch(const enum UserInterface_FSM_Signals ButtonSignal)
{
    UserInterface_FSM_Event NewEvent;
    NewEvent.Parent.EventSignal = ButtonSignal;
    FSM_Dispatch(&g_UI_FSM.Parent, &NewEvent.Parent);
}

/* Confirm Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin)
{
    DEBUG_PRINT("Confirm Button Pressed\r\n");
    SCREEN_DEBUG("Confirm");
    UI_Button_Dispatch(UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED);
}

/* Back Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Back_ISR_Handler_Austin)
{
    DEBUG_PRINT("Back Button Pressed\r\n");
    SCREEN_DEBUG("Back");
    UI_Button_Dispatch(UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED);
}

/* Increment Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin)
{
    DEBUG_PRINT("Increment Button Pressed\r\n");
    SCREEN_DEBUG("Increment");
    UI_Button_Dispatch(UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED);
}

/* Decrement Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin)
{
    DEBUG_PRINT("Decrement Button Pressed\r\n");
    SCREEN_DEBUG("Decrement");
    UI_Button_Dispatch(UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED);
}

/* [] END OF FILE */
