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

#ifndef USER_INTERFACE_BUTTONS_H
#define USER_INTERFACE_BUTTONS_H
  
#include "project.h"
#include "user_interface_fsm.h"

extern UserInterface_FSM g_UI_FSM;
    
void UI_Button_Dispatch(const enum UserInterface_FSM_Signals ButtonSignal);

void Enable_UI_Button_Interrupts();

CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin);
CY_ISR_PROTO(Button_Back_ISR_Handler_Austin);
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin);
CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin);
    
#endif

/* [] END OF FILE */
