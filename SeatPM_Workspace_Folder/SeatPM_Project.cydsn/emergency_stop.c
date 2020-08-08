/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: emergency_stop.c
Author: Austin Pischer

File Explanation: This file holds the function implementation for an
emergency stop. This encapsulates / hides the inner-workings of the
emergency stop function such that it can easily change in the future.
==============================================================================*/
#include "emergency_stop.h"

void EmergencyStop()
{
    // Stop motor -- always comes first
    Motor_PWM_Stop();
    
    // Print Stop Message
    sprintf(&g_UserInterface.Message[0][0], "    EMERGENCY   ");
    sprintf(&g_UserInterface.Message[1][0], "      STOP      ");
    UI_FSM_PrintMessage(g_UserInterface.Message);
    
    // Stopping execution is stand in for emergency buttons cutting power
    for(;;)
    {
        // Do nothing forever
    }
}

/* [] END OF FILE */
