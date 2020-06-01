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
    DEBUG_PRINT("Confirm Button ISR Started\r\n");
    Button_Confirm_ISR_ClearPending();
    Button_Confirm_ISR_StartEx(Button_Confirm_ISR_Handler_Austin);

    DEBUG_PRINT("Back Button ISR Started\r\n");
    Button_Back_ISR_ClearPending();
    Button_Back_ISR_StartEx(Button_Back_ISR_Handler_Austin);

    DEBUG_PRINT("Increment Button ISR Started\r\n");
    Button_Increment_ISR_ClearPending();
    Button_Increment_ISR_StartEx(Button_Increment_ISR_Handler_Austin);
    
    DEBUG_PRINT("Decrement Button ISR Started\r\n");
    Button_Decrement_ISR_ClearPending();
    Button_Decrement_ISR_StartEx(Button_Decrement_ISR_Handler_Austin);
}

/* Confirm Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nConfirm Button Pressed\r\n");
    UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
}

/* Back Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Back_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nBack Button Pressed\r\n");
    UI_Button_Dispatch(BACK_BUTTON_PRESSED);
}

/* Increment Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nIncrement Button Pressed\r\n");
    UI_Button_Dispatch(INCREMENT_BUTTON_PRESSED);
}

/* Decrement Button Interrupt Implementation*/
CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nDecrement Button Pressed\r\n");
    UI_Button_Dispatch(DECREMENT_BUTTON_PRESSED);
}

/* [] END OF FILE */
