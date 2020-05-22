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
// TODO
 *============================================================================*/

//=============================================================================
// Inclusions - Associated Header File
//=============================================================================
#include "user_interface_fsm.h"

//=============================================================================
// Method Implementations - User Interface Finite State Machine Class
//

//=============================================================================
// Non-State Functions
//

//=============================================================================
// Constructor
//=============================================================================
void UI_FSM_Constructor(UI_FSM *me)
{
    DEBUG_PRINT("UI Constructor called");
    FSM_Constructor(&me->Parent, &UI_FSM_Initial_State);
    DEBUG_PRINT("UI Initial state called");

    // Initialized in the order they appear in state flow
    me->IsFirstTimeSettingMinAngle = TRUE;
    me->IsFirstTimeSettingMaxAngle = TRUE;
    me->HasUserSeenAttachGoniometerMessage = FALSE;
    me->ShallMainLoopUpdateAngleReading = FALSE;
    me->HasUserSeenAttachAnkleStrapMessage = FALSE;
    me->ShallMainLoopHandleCPMMessage = FALSE;

    Parameter_Constructor(&me->New_CPM_Speed,
                          Parameter_GetMinimumValue(&g_CPM_Speed),
                          Parameter_GetMinimumValue(&g_CPM_Speed),
                          Parameter_GetValue(&g_CPM_Speed));

        // One should not expect for the initial state
        // to do anything with this signal
        Event InitialEvent;
    InitialEvent.EventSignal = CONFIRM_BUTTON_PRESSED;
    FSM_ExecuteInitialState(&me->Parent, &InitialEvent);
}

//=============================================================================
// Print Message
//=============================================================================
void UI_FSM_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1])
{
    Screen_ClearDisplay();
    Screen_PrintString(&Message[0][0]);
    Screen_PrintString(&Message[1][0]);
}

//=============================================================================
// Validate Current Goniometer Measurement
//=============================================================================
bool UI_FSM_IsKneeAngleValid(UI_FSM *me)
{
    double MaxAngle = Parameter_GetValue(&g_MaximumAngle);
    double MinAngle = Parameter_GetValue(&g_MinimumAngle);

    // Below case is reading within range of user-set parameters (valid)
    if (g_KneeAngle <= MaxAngle &&
        g_KneeAngle >= MinAngle &&
        g_KneeAngle != INVALID_ANGLE)
    {
        // Don't need to print anything if valid
        return (TRUE);
    }

    // All below cases are outside of range of user-set parameters
    // or invalid.
    else if (g_KneeAngle > MaxAngle)
    {
        // Print knee angle too large error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle above");
        sprintf(&me->Message[0][0], "maximum limit!  ");
        UI_FSM_PrintMessage(me->Message);
    }
    else if (g_KneeAngle < MinAngle)
    {
        // Print knee angle too small error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle below ");
        sprintf(&me->Message[0][0], "minimum limit!  ");
        UI_FSM_PrintMessage(me->Message);
    }
    else if (g_KneeAngle == INVALID_ANGLE)
    {
        // Print knee angle invalid error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle is   ");
        sprintf(&me->Message[0][0], "INVALID_ANGLE ! ");
        UI_FSM_PrintMessage(me->Message);
    }
    else
    {
        // Print knee angle invalid error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle is   ");
        sprintf(&me->Message[0][0], "unspecified!   ");
        UI_FSM_PrintMessage(me->Message);
    }
    CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    return (FALSE);
}

void UI_FSM_DisplayCableReleasedPercent(UI_FSM *me)
{
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Cable Released %%"); // Double % shows "%"
    sprintf(&me->Message[1][0],
            "%lf %%",
            Parameter_GetValue(&g_CableReleasedPercent));
    UI_FSM_PrintMessage(me->Message);
}

//=============================================================================
// State Function Implementations -- User Interface Finite State Machine Class
//

//=============================================================================
// Initial State
//=============================================================================
void UI_FSM_Initial_State(UI_FSM *me, Event const *MyEvent)
{
    DEBUG_PRINT("UI Initial State Called called");

    // Print welcome message while UI starts up
    //                           1234567890123456
    sprintf(&me->Message[0][0], "   Welcome to   ");
    sprintf(&me->Message[1][0], "     SeatPM     ");
    UI_FSM_PrintMessage(me->Message);

    // UI Startup Code Goes Here

    // Transition to Setting Minimum Angle
    FSM_Transition(&me->Parent,
                   &UI_UI_FSM_SetMinimumKneeAngle_StateFSM);
}

//=============================================================================
// Goniometer Configuration States

//=============================================================================
// Set Minimum Knee Angle State
//=============================================================================
void UI_UI_FSM_SetMinimumKneeAngle_StateFSM(UI_FSM *me, Event const *MyEvent)
{

    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        FSM_Transition(&me->Parent,
                       &UI_FSM_SetMaximumKneeAngle_State);
        break;

    case BACK_BUTTON_PRESSED:
        // Do nothing... this is the first user-accessible state
        break;

    case INCREMENT_BUTTON_PRESSED:
        Parameter_SetValue(&g_MinimumAngle,
                           Parameter_GetValue(&g_MinimumAngle) + 1);
        break;

    case DECREMENT_BUTTON_PRESSED:
        Parameter_SetValue(&g_MinimumAngle,
                           Parameter_GetValue(&g_MinimumAngle) - 1);
        break;

    default:
        // TODO
        break;
    } // End of signal processing

    if (me->IsFirstTimeSettingMinAngle == TRUE)
    {
        // Prompt user to set the minimum angle of the device
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Please set min. ");
        sprintf(&me->Message[1][0], "knee angle...   ");
        UI_FSM_PrintMessage(me->Message);

        me->IsFirstTimeSettingMinAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Print current minimum angle
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Min. knee angle ");
    sprintf(&me->Message[1][0], "= %4.1lf degrees",
            Parameter_GetValue(&g_MinimumAngle));
    UI_FSM_PrintMessage(me->Message);
}

//=============================================================================
// Set Maximum Knee Angle State
//=============================================================================
void UI_FSM_SetMaximumKneeAngle_State(UI_FSM *me, Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        FSM_Transition(&me->Parent,
                       &UI_FSM_GoniometerReadingCheck_State);
        break;

    case BACK_BUTTON_PRESSED:
        // Go back to minimum angle state
        FSM_Transition(&me->Parent,
                       &UI_UI_FSM_SetMinimumKneeAngle_StateFSM);
        break;

    case INCREMENT_BUTTON_PRESSED:
        Parameter_SetValue(&g_MaximumAngle,
                           Parameter_GetValue(&g_MaximumAngle) + 1);
        break;

    case DECREMENT_BUTTON_PRESSED:
        Parameter_SetValue(&g_MaximumAngle,
                           Parameter_GetValue(&g_MaximumAngle) - 1);
        break;

    default:
        // TODO
        break;
    } // End of signal processing

    if (me->IsFirstTimeSettingMaxAngle == TRUE)
    {
        // Prompt user to set the max angle of the device
        //                               1234567890123456
        sprintf(&me->Message[0][0], "Please set max. ");
        sprintf(&me->Message[1][0], "knee angle...   ");
        UI_FSM_PrintMessage(me->Message);

        me->IsFirstTimeSettingMinAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Print current maximum angle
    //                               1234567890123456
    sprintf(&me->Message[0][0], "Max. knee angle");
    sprintf(&me->Message[1][0],
            "= %4.1lf degrees",
            Parameter_GetValue(&g_MaximumAngle));
    UI_FSM_PrintMessage(me->Message);
}

//=============================================================================
// Goniometer Reading Check State
//=============================================================================
void UI_FSM_GoniometerReadingCheck_State(UI_FSM *me, Event const *MyEvent)
{
    /*Event Handling*/
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        // Print invalid message if invalid
        if (UI_FSM_IsKneeAngleValid(me) == TRUE)
        {
            // If knee angle is valid, tell user to attach ankle strap
            FSM_Transition(&me->Parent, UI_FSM_AnkleStrapRetractRelease_State);
        }
        // Else, knee angle is invalid, so do nothing.
        break;

    case BACK_BUTTON_PRESSED:
        // Go back to set maximum angle
        FSM_Transition(&me->Parent, UI_FSM_SetMaximumKneeAngle_State);
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Do nothing
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Do nothing
        break;

    default:
        // TODO
        break;
    } // End of signal processing

    // Skip attach goniometer message if user has already seen it
    if (me->HasUserSeenAttachGoniometerMessage == FALSE)
    {
        // Prompt user to attach goniometer
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Please attach   ");
        sprintf(&me->Message[1][0], "the knee brace. ");
        UI_FSM_PrintMessage(me->Message);
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
        me->HasUserSeenAttachGoniometerMessage = TRUE;
    }

    // Print current vs max and min
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Current %4.1lf deg", g_KneeAngle);
    sprintf(&me->Message[1][0],
            "Min=%3lf Max=%3lf",
            Parameter_GetValue(&g_MinimumAngle),
            Parameter_GetValue(&g_MaximumAngle));
    UI_FSM_PrintMessage(me->Message);

    // Turn off main loop updating current angle line
    // Only have effect if this state has already been executed
    me->ShallMainLoopUpdateAngleReading = FALSE; // Maybe not the right place

    // Make the main loop update the current angle measurement.
    if (me->Parent.currentState == &UI_FSM_GoniometerReadingCheck_State)
    {
        me->ShallMainLoopUpdateAngleReading = TRUE;
    }
} // End of Goniometer Reading Check State

//=============================================================================
// Ankle Strap Retract/Release State
//=============================================================================
void UI_FSM_AnkleStrapRetractRelease_State(UI_FSM *me,
                                           Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        if (UI_FSM_IsKneeAngleValid(me) == TRUE)
        {
            // If knee angle is valid, go to CPM startup state
            FSM_Transition(&me->Parent, UI_FSM_ConfirmCPMStartup_State);
        }
        // Else, knee angle is invalid, so do nothing.
        break;

    case BACK_BUTTON_PRESSED:
        FSM_Transition(&me->Parent, UI_FSM_GoniometerReadingCheck_State);
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Only release cable and show percent release while button is pressed
        // and knee angle is valid
        while (Button_Increment_Read() != FALSE &&
               UI_FSM_IsKneeAngleValid(me) == TRUE)
        {
            // TODO: Slow this down?
            Parameter_SetValue(&g_CableReleasedPercent,
                           Parameter_GetValue(&g_CableReleasedPercent) + 1);
            UI_FSM_DisplayCableReleasedPercent(me);
            CyDelay(100);//TODO
        }
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Only retract cable and show percent release while button is pressed
        // and knee angle is valid
        while (Button_Decrement_Read() != FALSE &&
               UI_FSM_IsKneeAngleValid(me) == TRUE)
        {
            // TODO: Slow this down?
            Parameter_SetValue(&g_CableReleasedPercent,
                           Parameter_GetValue(&g_CableReleasedPercent) - 1);
            UI_FSM_DisplayCableReleasedPercent(me);
            CyDelay(100);//TODO
        }
        break;

    default:
        // TODO
        break;
    }

    if (me->HasUserSeenAttachAnkleStrapMessage == FALSE)
    {
        // Prompt user to attach goniometer
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Please attach   ");
        sprintf(&me->Message[1][0], "the ankle strap. ");
        UI_FSM_PrintMessage(me->Message);
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
        me->HasUserSeenAttachAnkleStrapMessage = TRUE;
    }

    // Prompt user to retract/release the cable
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Release Cable[+]");
    sprintf(&me->Message[1][0], "Retract Cable[-]");
    UI_FSM_PrintMessage(me->Message);
}

//=============================================================================
// CPM Use States
//

//=============================================================================
// Confirm CPM Startup State
//=============================================================================
void UI_FSM_ConfirmCPMStartup_State(
    UI_FSM *me,
    Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        // Go to CPM State
        if(UI_FSM_IsKneeAngleValid(me) == TRUE)
        {   
            Parameter_SetValue(&g_CPM_Speed, 30);
            FSM_Transition(&me->Parent, UI_FSM_ContinuousPassiveMotion_State);
        }
        break;

    case BACK_BUTTON_PRESSED:
        // Go to Attach Ankle Strap State
        FSM_Transition(&me->Parent, UI_FSM_AnkleStrapRetractRelease_State);
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Do Nothing
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Do Nothing
        break;

    default:
        // TODO
        break;
    }

        // Prompt user to retract/release the cable
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Start motion at ");
    sprintf(&me->Message[1][0], 
            "%d deg/min?", 
            CPM_START_SPEED_DEGREES_PER_MINUTE);
    UI_FSM_PrintMessage(me->Message);
}

//=============================================================================
// CPM State
//=============================================================================
void UI_FSM_ContinuousPassiveMotion_State(
    UI_FSM *me,
    Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        Parameter_SetValue(&g_CPM_Speed, 0);
        FSM_Transition(&me->Parent, UI_FSM_ConfirmCPMStartup_State);
        break;

    case BACK_BUTTON_PRESSED:
        Parameter_SetValue(&g_CPM_Speed, 0);
        FSM_Transition(&me->Parent, UI_FSM_ConfirmCPMStartup_State);
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Go to change speed state
        Parameter_SetValue(&me->New_CPM_Speed,
                           Parameter_GetValue(&g_CPM_Speed)+1);
        FSM_Transition(&me->Parent, UI_FSM_ConfirmSpeedChange_State);
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Go to change speed state
        Parameter_SetValue(&me->New_CPM_Speed,
                           Parameter_GetValue(&g_CPM_Speed)-1);
        FSM_Transition(&me->Parent, UI_FSM_ConfirmSpeedChange_State);
        break;

    default:
        // TODO
        break;
    }// End of signal handling

    if (me->Parent.currentState == &UI_FSM_ContinuousPassiveMotion_State)
    {
        me->ShallMainLoopHandleCPMMessage = TRUE;
    }
}

//=============================================================================
// Confirm Speed ChangeState
//=============================================================================
void UI_FSM_ConfirmSpeedChange_State(
    UI_FSM *me,
    Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        // Set current to new
        Parameter_SetValue(&g_CPM_Speed, Parameter_GetValue(&me->New_CPM_Speed));
        // Go to CPM state
        FSM_Transition(&me->Parent, UI_FSM_ContinuousPassiveMotion_State);
        break;

    case BACK_BUTTON_PRESSED:
        // Set new to current
        Parameter_SetValue(&me->New_CPM_Speed, Parameter_GetValue(&g_CPM_Speed));
        // Go to CPM state
        FSM_Transition(&me->Parent, UI_FSM_ContinuousPassiveMotion_State);
        break;

    case INCREMENT_BUTTON_PRESSED:
        Parameter_SetValue(&me->New_CPM_Speed,
                           Parameter_GetValue(&me->New_CPM_Speed)+1);
        break;

    case DECREMENT_BUTTON_PRESSED:
        Parameter_SetValue(&me->New_CPM_Speed,
                           Parameter_GetValue(&me->New_CPM_Speed)-1);
        break;

    default:
        // TODO
        break;
    }

            // Prompt user to retract/release the cable
    //                           1234567890123456
    sprintf(&me->Message[0][0], 
            "Crnt= %4.1lf dpm",
            Parameter_GetValue(&g_CPM_Speed));
    sprintf(&me->Message[1][0], 
            "New = %4.1lf dpm", 
            Parameter_GetValue(&me->New_CPM_Speed));
    UI_FSM_PrintMessage(me->Message);
}

/* [] END OF FILE */
