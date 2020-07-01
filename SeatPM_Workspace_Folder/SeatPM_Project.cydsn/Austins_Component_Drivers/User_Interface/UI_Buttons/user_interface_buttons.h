// Todo: File header

// Start of Multiple Inclusion Protection
#ifndef USER_INTERFACE_BUTTONS_H
#define USER_INTERFACE_BUTTONS_H

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "user_interface_fsm.h"
#include "austin_parameter.h"

//=============================================================================
// External Variables (defined in main.c)
//=============================================================================
extern Parameter g_CPM_Speed;
extern UI_FSM g_UserInterface;
    
#ifdef FLAG_DISPATCH
extern bool g_Dispatch_ConfirmButton;
extern bool g_Dispatch_BackButton;
extern bool g_Dispatch_IncrementButton;
extern bool g_Dispatch_DecrementButton;
#endif

//=============================================================================
// Function Prototypes
//=============================================================================
void UI_Button_Dispatch(const enum UI_FSM_Signals ButtonSignal);
void Enable_UI_Button_Interrupts();

//=============================================================================
// Interrupt Function Prototypes
//=============================================================================
// Normal UI Buttons
CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin);
CY_ISR_PROTO(Button_Back_ISR_Handler_Austin);
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin);
CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin);

// Emergency Stop Buttons
CY_ISR_PROTO(Button_EmergencyStop_Right_Interrupt_Handler);
CY_ISR_PROTO(Button_EmergencyStop_Left_Interrupt_Handler);
    
#endif // Enf of multiple inclusion protection

/* [] END OF FILE */
