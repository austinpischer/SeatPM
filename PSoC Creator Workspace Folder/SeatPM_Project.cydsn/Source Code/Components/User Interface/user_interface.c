/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: user_interface_fsm.c
 * Author: Austin Pischer
 * 
 * File Explanation:
 * Thisfile contains all the function implementations for those defined in
 * user_interface_fsm.c.
 * 
 * The majority of the functions in this file are states, which consist of
 * switch statements that handle dispatched signals.
 *============================================================================*/

//=============================================================================
// Inclusions - Associated Header File
//=============================================================================
#include "user_interface.h"
#include "user_interface_states.h"

//=============================================================================
// Constructor
//=============================================================================
void UserInterface_Constructor(UserInterface *me)
{
    DEBUG_PRINT("UI Constructor called\r\n");
    FSM_Constructor(&me->Parent, &UserInterface_Initial_State);

    // Initialized in the order they appear in state flow
    me->IsFirstTimeSettingMinAngle = TRUE;
    me->IsFirstTimeSettingMaxAngle = TRUE;
    me->HasUserSeenAttachGoniometerMessage = FALSE;
    me->ShallMainLoopUpdateAngleReading = FALSE;
    me->HasUserSeenAttachAnkleStrapMessage = FALSE;
    me->ShallMainLoopHandleCPMMessage = FALSE;
    
    // One should not expect for the initial state
    // to do anything with this signal
    Event InitialEvent;
    InitialEvent.EventSignal = CONFIRM_BUTTON_PRESSED;
    
    Parameter_Constructor(&me->New_CPM_Speed,0,100,0,-1);
    
    Parameter_Constructor(&me->KneeAngle,
                          ABSOLUTE_MINIMUM_KNEE_ANGLE,
                          ABSOLUTE_MAXIMUM_KNEE_ANGLE, 
                          INVALID_ANGLE,
                          INVALID_ANGLE);
    
        
    me->KneeAngle_Raw = INVALID_ANGLE;

    DEBUG_PRINT("Executing Initial State\r\n");
    FSM_ExecuteInitialState(&me->Parent, &InitialEvent);
}

//=============================================================================
// Validate Raw Goniometer Measurement
//=============================================================================
bool UserInterface_IsKneeAngle_Raw_Valid(UserInterface *me)
{
    DEBUG_PRINT("Raw Knee Angle Validation Check:\r\n");

    // Handle errors
    if (me->KneeAngle_Raw > me->KneeAngle.MaximumValue)
    {
        // Print knee angle too large error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle above");
        sprintf(&me->Message[1][0], "maximum limit!  ");
        Screen_PrintMessage(me->Message);
    }
    else if (me->KneeAngle_Raw < me->KneeAngle.MinimumValue)
    {
        // Print knee angle too small error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle below ");
        sprintf(&me->Message[1][0], "minimum limit!  ");
        Screen_PrintMessage(me->Message);
    }
    else if (me->KneeAngle_Raw == me->KneeAngle.InvalidValue)
    {
        // Print knee angle invalid error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle is   ");
        sprintf(&me->Message[1][0], "INVALID_ANGLE ! ");
        Screen_PrintMessage(me->Message);
    }
    // Handle non-errors
    else
    {
        return(TRUE);
    }
    CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    return (FALSE);
}

//=============================================================================
// Display Cable Released Percent
//=============================================================================
void UserInterface_DisplayCableReleasedPercent(UserInterface *me)
{
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Cable Released %%"); // Double % shows "%"
    sprintf(&me->Message[1][0],
            "%lf %%",
            Parameter_GetValue(&(g_CPM_Motor.PercentCableReleased)));
    Screen_PrintMessage(me->Message);
}


//=============================================================================
// Execute Current State Function 
//=============================================================================
void UserInterface_ExecuteCurrentStateFunction(UserInterface *me)
{
    Event NoOperationEvent;
    NoOperationEvent.EventSignal = NO_OPERATION;
    DEBUG_PRINT("Executing State...\r\n");
    FSM_Dispatch(&me->Parent, &NoOperationEvent);
}

//=============================================================================
// Print Invalid Signal Message
//=============================================================================
void UserInterface_PrintInvalidSignalMessage(UserInterface *me)
{
    DEBUG_PRINT("ERROR: Invalid Singal!\r\n");
}

//=============================================================================
// Shall Update Angle Reading
//=============================================================================
bool UserInterface_ShallUpdateAngleReadingMessage(UserInterface *me, double KneeAngle, double LastKneeAngle)
{
    return (me->ShallMainLoopUpdateAngleReading == TRUE &&
            KneeAngle != LastKneeAngle);
}

//=============================================================================
// Update Angle Reading
//=============================================================================
void UserInterface_UpdateAngleReadingMessage(UserInterface *me, double KneeAngle)
{
    sprintf(&me->Message[0][0], "Current=%4.1lfdeg", KneeAngle);
    Screen_PrintMessage(me->Message);
}

//=============================================================================
// Shall Update CPM Runtime Message
//=============================================================================
bool UserInterface_ShallUpdateCPMRuntimeMessage(UserInterface *me, 
                                double KneeAngle, 
                                   double LastKneeAngle,
                                   double LastTotalSeconds)
{
    return (me->ShallMainLoopHandleCPMMessage == TRUE &&
            KneeAngle != LastKneeAngle &&
            Runtime_GetTotalSeconds(&g_CPM_Runtime) != LastTotalSeconds);
}

//=============================================================================
// Update CPM Runtime Message
//=============================================================================
void UserInterface_UpdateCPMRuntimeMessage(UserInterface *me, double KneeAngle)
{
    // Update the runtime
    Runtime_Update(&g_CPM_Runtime);
    // Print message
    sprintf(&me->Message[0][0], "RT: %2dh %2dm %2ds",
            Runtime_GetHours(&g_CPM_Runtime),
            Runtime_GetMinutes(&g_CPM_Runtime),
            Runtime_GetSeconds(&g_CPM_Runtime));
    sprintf(&me->Message[1][0], "Angle = %4.1lfdeg", KneeAngle);
    Screen_PrintMessage(me->Message);
}
/* [] END OF FILE */
