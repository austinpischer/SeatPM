/*
TODO
*/
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
