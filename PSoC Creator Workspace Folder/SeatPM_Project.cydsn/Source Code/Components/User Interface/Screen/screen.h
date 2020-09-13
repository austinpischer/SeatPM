/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: screen.h
Author: Austin Pischer
File Description: This file contains the function declarations(prototypes) 
related to the SeatPM's screen. These functions are meant to act as a layer
of abstraction between the PSoC CharLCD Component APIs and the rest of the code.

The current screen is a 16x2 Character LCD.
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
Requirements: A CharLCD component in TopDesign.cysch named "UI_Screen"
Results: Starts the screen and clears it.
*/
void Screen_Setup(); 

/* Function Name: Screen_PrintMessage
Requirements: - A CharLCD component in TopDesign.cysch named "UI_Screen"
              - A two dimensional char array (or reference to the first 
                character of one) with the dimensions MESSAGE_ROWS
                by MESSAGE_CHARACTERS_PER_ROW + 1
Results: The chars present in the message are displayed on the screen and
         are also output to debug.
*/
void Screen_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1]);

#endif // End of Multiple Inclusion Protection
/* [] END OF FILE */