/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: emergency_stop.h
Author: Austin Pischer  

File Explanation:
This header file contains everything needed for the function implementations
of the emergency stop function that is implemented in the associated
file "emergency_stop.c"
==============================================================================*/

// Start Multiple inclusion protection
#ifndef EMERGENCY_STOP_H
#define EMERGENCY_STOP_H
    
//=============================================================================
// Inclusions
//=============================================================================
#include <stdio.h> // for printf
#include "user_interface_fsm.h" // for user interface "class"
    
//=============================================================================
// External Global Variables
//=============================================================================
extern UI_FSM g_UserInterface;
    
//=============================================================================
// Function Prototypes 
//=============================================================================
void EmergencyStop();
    
// End Multiple inclusion protection
#endif
/* [] END OF FILE */