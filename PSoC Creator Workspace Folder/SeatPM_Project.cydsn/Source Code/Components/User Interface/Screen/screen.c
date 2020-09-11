/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: screen.c
Author: Austin Pischer
File Description: //todo
==============================================================================*/

//==============================================================================
// Associated Header File 
//==============================================================================
#include "screen.h"

//==============================================================================
// Screen Setup 
//==============================================================================
void Screen_Setup()
{
    UI_Screen_Start();
    UI_Screen_ClearDisplay();
}

//==============================================================================
// Screen Print Message 
//==============================================================================
void Screen_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1])
{
    UI_Screen_ClearDisplay();
    UI_Screen_PrintString(&Message[0][0]);
    UI_Screen_Position(1,0);
    UI_Screen_PrintString(&Message[1][0]);

    DEBUG_PRINT(&Message[0][0]);
    DEBUG_PRINT("\r\n"); //newline
    DEBUG_PRINT(&Message[1][0]);
    DEBUG_PRINT("\r\n\r\n"); //two newlines
}
/* [] END OF FILE */