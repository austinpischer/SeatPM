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
    me->Is_First_Time_Setting_Min_Angle = TRUE;
    me->Is_First_Time_Setting_Max_Angle = TRUE;
    me->Has_User_Seen_Attach_Goniometer_Message = FALSE;
    me->Shall_Main_Loop_Update_Angle_Reading = FALSE;
    me->Has_User_Seen_Attach_Ankle_Strap_Message = FALSE;
    me->Shall_Main_Loop_Handle_CPM_Message = FALSE;

    // One should not expect for the initial state
    // to do anything with this signal
    Event InitialEvent;
    InitialEvent.EventSignal = CONFIRM_BUTTON_PRESSED;

    Parameter_Constructor(&me->New_CPM_Speed, 0, 100, 0, -1);

    Parameter_Constructor(&me->KneeAngle, ABSOLUTE_MINIMUM_KNEE_ANGLE,
                          ABSOLUTE_MAXIMUM_KNEE_ANGLE, INVALID_ANGLE,
                          INVALID_ANGLE);

    me->KneeAngle_Raw = INVALID_ANGLE;

    Runtime_Constructor(&me->CPM_Runtime);
    Motor_Constructor(&me->CPM_Motor);

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
    if (me->KneeAngle_Raw > me->KneeAngle.Maximum)
    {
        // Print knee angle too large error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle above");
        sprintf(&me->Message[1][0], "maximum limit!  ");
        Screen_PrintMessage(me->Message);
    }
    else if (me->KneeAngle_Raw < me->KneeAngle.Minimum)
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
        return (TRUE);
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
    sprintf(&me->Message[0][0], "Cable Released %%");  // Double % shows "%"
    sprintf(&me->Message[1][0], "%lf %%",
            Parameter_GetValue(&(me->CPM_Motor.PercentCableReleased)));
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
bool UserInterface_ShallUpdateAngleReadingMessage(UserInterface *me,
                                                  double KneeAngle,
                                                  double LastKneeAngle)
{
    return (me->Shall_Main_Loop_Update_Angle_Reading == TRUE &&
            KneeAngle != LastKneeAngle);
}

//=============================================================================
// Update Angle Reading
//=============================================================================
void UserInterface_UpdateAngleReadingMessage(UserInterface *me,
                                             double KneeAngle)
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
                                                long int LastTotalSeconds)
{
    return(me->Shall_Main_Loop_Handle_CPM_Message == TRUE &&
           (KneeAngle != LastKneeAngle ||
           Runtime_GetTotalSeconds(&me->CPM_Runtime) != LastTotalSeconds));
}

//=============================================================================
// Update CPM Runtime Message
//=============================================================================
void UserInterface_UpdateCPMRuntimeMessage(UserInterface *me, double KneeAngle)
{
    // Update the runtime values
    Runtime_Update(&me->CPM_Runtime);
    // Print message
    sprintf(&me->Message[0][0], "RT: %2dh %2dm %2ds",
            Runtime_GetHours(&me->CPM_Runtime),
            Runtime_GetMinutes(&me->CPM_Runtime),
            Runtime_GetSeconds(&me->CPM_Runtime));
    sprintf(&me->Message[1][0], "Angle = %4.1lfdeg", KneeAngle);
    Screen_PrintMessage(me->Message);
}

//=============================================================================
// Handle Emergency Stop Condition
//=============================================================================
void UserInterface_EmergencyStop(UserInterface *me)
{
    // Stop motor -- always comes first
    Motor_Stop(&me->CPM_Motor);

    // Print Stop Message
    sprintf(&me->Message[0][0], "    EMERGENCY   ");
    sprintf(&me->Message[1][0], "      STOP      ");
    Screen_PrintMessage(me->Message);

    // Stopping execution is stand in for emergency buttons cutting power
    for (;;)
    {
        // Do nothing forever
    }
}

//=============================================================================
// Handle Emergency Stop Condition
//=============================================================================
void UserInterface_HandleEmergencyStopCondition(UserInterface *me,
                                                bool IsKneeAngleValid,
                                                double KneeAngle)
{
    if (IsKneeAngleValid == FALSE &&
        me->Has_User_Seen_Attach_Ankle_Strap_Message == TRUE)
    {
        // Print to debug what went wrong
        char8 debug[64];
        sprintf(debug,
                "current = %lf,\r\n"
                "val = %lf,\r\n"
                "min = %lf,\r\n"
                "max = %lf\r\n\r\n",
                KneeAngle, Parameter_GetValue(&me->KneeAngle),
                Parameter_GetMinimum(&me->KneeAngle),
                Parameter_GetMaximum(&me->KneeAngle));
        DEBUG_PRINT(debug);

        UserInterface_EmergencyStop(me);
    }
}
/* [] END OF FILE */
