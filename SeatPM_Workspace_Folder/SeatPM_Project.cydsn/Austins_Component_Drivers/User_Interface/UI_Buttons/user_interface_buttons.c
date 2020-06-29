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
    
    DEBUG_PRINT("Emergency Stop Button (Left) ISR Started \r\n");
    Button_EmergencyStop_Left_Interrupt_ClearPending();
    Button_EmergencyStop_Left_Interrupt_StartEx(Button_EmergencyStop_Left_Interrupt_Handler);
       
    DEBUG_PRINT("Emergency Stop Button (Right) ISR Started \r\n");
    Button_EmergencyStop_Right_Interrupt_ClearPending();
    Button_EmergencyStop_Right_Interrupt_StartEx(Button_EmergencyStop_Right_Interrupt_Handler);
}

/* Confirm Button Interrupt Implementation*/
CY_ISR(Button_Confirm_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nConfirm Button Pressed\r\n");
    
    #ifdef FLAG_DISPATCH
    g_Dispatch_ConfirmButton = TRUE;
    #else
    UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
    #endif 
    
}

/* Back Button Interrupt Implementation*/
CY_ISR(Button_Back_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nBack Button Pressed\r\n");
    
    #ifdef FLAG_DISPATCH
    g_Dispatch_BackButton = TRUE;
    #else
    UI_Button_Dispatch(BACK_BUTTON_PRESSED);
    #endif
}

/* Increment Button Interrupt Implementation*/
CY_ISR(Button_Increment_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nIncrement Button Pressed\r\n");
    
    #ifdef FLAG_DISPATCH
    g_Dispatch_IncrementButton = TRUE;
    #else
    UI_Button_Dispatch(INCREMENT_BUTTON_PRESSED);
    #endif
}

/* Decrement Button Interrupt Implementation*/
CY_ISR(Button_Decrement_ISR_Handler_Austin)
{
    DEBUG_PRINT("\r\nDecrement Button Pressed\r\n");
    
    #ifdef FLAG_DISPATCH
    g_Dispatch_DecrementButton = TRUE;
    #else
    UI_Button_Dispatch(DECREMENT_BUTTON_PRESSED);
    #endif
}

CY_ISR(Button_EmergencyStop_Right_Interrupt_Handler)
{
    Motor_PWM_Stop(); // Stop motor
    sprintf(&g_UserInterface.Message[0][0], "    EMERGENCY   ");
    sprintf(&g_UserInterface.Message[1][0], "      STOP      ");
    UI_FSM_PrintMessage(g_UserInterface.Message);
    for(;;)
    {
        // Do nothing (aka stop device)
    };
}

CY_ISR_PROTO(Button_EmergencyStop_Left_Interrupt_Handler)
{
    Motor_PWM_Stop();
    sprintf(&g_UserInterface.Message[0][0], "    EMERGENCY   ");
    sprintf(&g_UserInterface.Message[0][0], "      STOP      ");
    UI_FSM_PrintMessage(g_UserInterface.Message);
    for(;;)
    {
        // Do nothing (aka stop device)
    };
}

/* [] END OF FILE */
