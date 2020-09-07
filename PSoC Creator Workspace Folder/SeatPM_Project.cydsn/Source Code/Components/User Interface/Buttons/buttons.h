/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: user_interface_buttons.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * This file protoypes all of the funtions that make the SeatPM's user
 * interface's buttons come to life. It also includes all the external global
 * variables from main.c and all the inclusions needed for the function
 * definitions in the associated file user_interface_buttons.c.
 *============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef USER_INTERFACE_BUTTONS_H
#define USER_INTERFACE_BUTTONS_H

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "debug.h"
#include "feature_branches.h"
#include "user_interface.h"
#include "buttons.h"
#include "parameter.h"
#include "emergency_stop.h"

//=============================================================================
// External Variables (defined in main.c)
//=============================================================================
extern UserInterface g_UserInterface;
//#ifdef DISPATCH_IN_MAIN
extern UserInterface_Signal g_SignalToDispatch;
//#endif

//=============================================================================
// Function Prototypes
//=============================================================================
void Buttons_Dispatch(const enum UserInterface_Signal ButtonSignal);
void Buttons_Setup();

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
