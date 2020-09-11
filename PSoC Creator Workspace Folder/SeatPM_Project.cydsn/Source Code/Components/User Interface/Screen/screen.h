/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: screen.h
Author: Austin Pischer
File Description: //todo
==============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef SCREEN_H
#define SCREEN_H

//==============================================================================
// Inclusions 
//==============================================================================
#include "project.h"
#include "debug.h"

//==============================================================================
// Definitions 
//==============================================================================
#define MESSAGE_ROWS 2
#define MESSAGE_CHARACTERS_PER_ROW 16
#define MESSAGE_ON_SCREEN_TIME_MS 500

//==============================================================================
// Function Definitions 
//==============================================================================

/* Function Name: Screen_Setup
Requirements: //todo
Results: //todo
*/
void Screen_Setup(); 

/* Function Name: Screen_PrintMessage
Requirements: //todo
Results: //todo
*/
void Screen_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1]);

#endif // End of Multiple Inclusion Protection
/* [] END OF FILE */