// TODO; File header

#include "user_interface_buttons.h"
#include "austin_debug.h"
#include "user_interface_fsm.h" 

/* Helper function for button interrupt implementations */ 
void UI_Button_Dispatch(const enum UI_FSM_Signals ButtonSignal)
{
    UI_FSM_Event NewEvent;
    NewEvent.Parent.EventSignal = ButtonSignal;
    FSM_Dispatch(&g_UserInterface.Parent, &NewEvent.Parent);
}

void Enable_UI_Button_Interrupts()
{
    Button_Confirm_ISR_StartEx(Button_Confirm_ISR_Handler_Austin);
    Button_Back_ISR_StartEx(Button_Back_ISR_Handler_Austin);
    Button_Increment_ISR_StartEx(Button_Increment_ISR_Handler_Austin);
    Button_Decrement_ISR_StartEx(Button_Decrement_ISR_Handler_Austin);
}

/* Confirm Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nConfirm Button Pressed\r\n");
    SCREEN_DEBUG("Confirm");
    UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
}

/* Back Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Back_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nBack Button Pressed\r\n");
    SCREEN_DEBUG("Back");
    UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
}

/* Increment Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nIncrement Button Pressed\r\n");
    SCREEN_DEBUG("Increment");
    UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
}

/* Decrement Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nDecrement Button Pressed\r\n");
    SCREEN_DEBUG("Decrement");
    UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
}

/* [] END OF FILE */
