/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 09 2020

File Name: cpm_runtime.h
Author: Austin Pischer
File Description: //todo
==============================================================================*/
#include "user_interface.h"

//==============================================================================
// External Global Variables 
//==============================================================================
typedef struct UserInterface UserInterface;  // since "user_interface.h" includes this file, we must "forward declare" this type becuause it is not yet defined when the compiler inserts it into the "user_interface.h" file
extern UserInterface g_UserInterface; // declared in main, used in interrupt service routine

//==============================================================================
// Interrupt Service Routine Prototype 
//==============================================================================
CY_ISR_PROTO(Runtime_Timer_Interrupt_Handle);

//==============================================================================
// Function Declarations (Prototypes) 
//==============================================================================

/* Function Name: todo 
Requirements: 
Results: 
*/
void CPM_Runtime_Setup();

/* Function Name: //todo
Requirements: 
Results: 
*/
void CPM_Runtime_StartCounting();

/* Function Name: todo
Requirements: 
Results: 
*/
void CPM_Runtime_StopCounting();

/* [] END OF FILE */