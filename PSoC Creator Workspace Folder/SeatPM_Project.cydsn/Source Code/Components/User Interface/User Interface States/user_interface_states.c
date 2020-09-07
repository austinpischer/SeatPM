#include "user_interface_states.h"

//=============================================================================
// Initial State
//=============================================================================
void UserInterface_Initial_State(UserInterface *me, Event const *MyEvent)
{
    DEBUG_PRINT("UI Initial State Called\r\n");

    // Print welcome message while UI starts up
    //                           1234567890123456
    sprintf(&me->Message[0][0], "   Welcome to   ");
    sprintf(&me->Message[1][0], "     SeatPM     ");
    Screen_PrintMessage(me->Message);
    CyDelay(MESSAGE_ON_SCREEN_TIME_MS);

    // UI Startup Code Goes Here

    // Transition to Setting Minimum Angle
    DEBUG_PRINT("Transition to Set Minimum Knee Angle\r\n");
    FSM_Transition(&me->Parent, &UserInterface_SetMinimumKneeAngle_State);
    // Update display in next function without any inputs
    UserInterface_ExecuteCurrentStateFunction(me);
}  // End of initial state


//=============================================================================
// Set Minimum Knee Angle State
//=============================================================================
void UserInterface_SetMinimumKneeAngle_State(UserInterface *me,
                                             Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            DEBUG_PRINT("Transition to Set Maximum Knee Angle\r\n");
            FSM_Transition(&me->Parent,
                           &UserInterface_SetMaximumKneeAngle_State);
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case BACK_BUTTON_PRESSED:
            // Do nothing... this is the first user-accessible state
            break;

        case INCREMENT_BUTTON_PRESSED:
            // Only increment minval up to maxval
            if ((Parameter_GetMinimumValue(&me->KneeAngle) + 1) <=
                Parameter_GetMaximumValue(&me->KneeAngle))
            {
                Parameter_IncrementMinimumValue(&me->KneeAngle);
            }  // Otherwise do nothing
            break;

        case DECREMENT_BUTTON_PRESSED:
            // Decrement minval only down to absolute min
            if ((Parameter_GetMinimumValue(&me->KneeAngle) - 1) >=
                ABSOLUTE_MINIMUM_KNEE_ANGLE)
            {
                Parameter_DecrementMinimumValue(&me->KneeAngle);
            }  // Otherwise do nothing
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI \
                     at the Set Minimum Knee Angle State\r\n");
            break;
    }  // End of signal processing

    // One-off message
    if (me->IsFirstTimeSettingMinAngle == TRUE)
    {
        // Prompt user to set the minimum angle of the device
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Please set min. ");
        sprintf(&me->Message[1][0], "knee angle...   ");
        Screen_PrintMessage(me->Message);

        me->IsFirstTimeSettingMinAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned =
        !(me->Parent.CurrentState == &UserInterface_SetMinimumKneeAngle_State);

    if (HasStateTransitioned == FALSE)
    {
        // Print current minimum angle
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Min. knee angle ");
        sprintf(&me->Message[1][0], "= %4.1lf degrees",
                Parameter_GetMinimumValue(&me->KneeAngle));
        Screen_PrintMessage(me->Message);
    }
}  // End of set minimum knee angle state

//=============================================================================
// Set Maximum Knee Angle State
//=============================================================================
void UserInterface_SetMaximumKneeAngle_State(UserInterface *me,
                                             Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            DEBUG_PRINT("Transition to Goniometer Reading Check\r\n");
            FSM_Transition(&me->Parent,
                           &UserInterface_GoniometerReadingCheck_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case BACK_BUTTON_PRESSED:
            // Go back to minimum angle state
            DEBUG_PRINT("Transition to Set Minimum Knee Angle\r\n");
            FSM_Transition(&me->Parent,
                           &UserInterface_SetMinimumKneeAngle_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case INCREMENT_BUTTON_PRESSED:
            // only increment up to absolute max
            if ((Parameter_GetMaximumValue(&me->KneeAngle) + 1) <=
                ABSOLUTE_MAXIMUM_KNEE_ANGLE)
            {
                Parameter_IncrementMaximumValue(&me->KneeAngle);
            }
            break;

        case DECREMENT_BUTTON_PRESSED:
            // only decrement down to minimum
            if ((Parameter_GetMaximumValue(&me->KneeAngle) - 1) >=
                Parameter_GetMinimumValue(&me->KneeAngle))
            {
                Parameter_DecrementMaximumValue(&me->KneeAngle);
            }
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI \
                            at the Set Maximum Knee Angle State\r\n");
            break;
    }  // End of signal processing

    // One-off message
    if (me->IsFirstTimeSettingMaxAngle == TRUE)
    {
        // Prompt user to set the max angle of the device
        //                               1234567890123456
        sprintf(&me->Message[0][0], "Please set max. ");
        sprintf(&me->Message[1][0], "knee angle...   ");
        Screen_PrintMessage(me->Message);

        me->IsFirstTimeSettingMaxAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned =
        !(me->Parent.CurrentState == &UserInterface_SetMaximumKneeAngle_State);

    if (HasStateTransitioned == FALSE)
    {
        // Print current maximum angle
        //                               1234567890123456
        sprintf(&me->Message[0][0], "Max. knee angle");
        sprintf(&me->Message[1][0], "= %4.1lf degrees",
                Parameter_GetMaximumValue(&me->KneeAngle));
        Screen_PrintMessage(me->Message);
    }
}  // End of Set Maximum Knee Angle State

//=============================================================================
// Goniometer Reading Check State
//=============================================================================
void UserInterface_GoniometerReadingCheck_State(UserInterface *me,
                                                Event const *MyEvent)
{
    /*Event Handling*/
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            // Print invalid message if invalid
            if (UserInterface_IsKneeAngle_Raw_Valid(me) == TRUE)
            {
                // If knee angle is valid, tell user to attach ankle strap
                DEBUG_PRINT("Transition to Ankle Strap R/R\r\n");
                me->ShallMainLoopUpdateAngleReading = FALSE;
                FSM_Transition(&me->Parent,
                               UserInterface_AnkleStrapRetractRelease_State);
                // Update display in next function without any inputs
                UserInterface_ExecuteCurrentStateFunction(me);
            }
            // Else, knee angle is invalid, so do nothing.
            break;

        case BACK_BUTTON_PRESSED:
            // Go back to set maximum angle
            DEBUG_PRINT("Transition to Set Maximum Knee Angle\r\n");
            me->ShallMainLoopUpdateAngleReading = FALSE;
            FSM_Transition(&me->Parent,
                           UserInterface_SetMaximumKneeAngle_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case INCREMENT_BUTTON_PRESSED:
            // Do nothing
            break;

        case DECREMENT_BUTTON_PRESSED:
            // Do nothing
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI"
                "at the Check Goniometer Reading Check State\r\n");
            break;
    }  // End of signal processing

    // Skip attach goniometer message if user has already seen it
    if (me->HasUserSeenAttachGoniometerMessage == FALSE)
    {
        // Prompt user to attach goniometer
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Please attach   ");
        sprintf(&me->Message[1][0], "the knee brace. ");
        Screen_PrintMessage(me->Message);
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
        me->HasUserSeenAttachGoniometerMessage = TRUE;
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned = !(me->Parent.CurrentState ==
                                  &UserInterface_GoniometerReadingCheck_State);

    if (HasStateTransitioned == FALSE)
    {
        // Print current vs max and min
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Current=%4.1lfdeg",
                Parameter_GetValue(&me->KneeAngle));
        sprintf(&me->Message[1][0], "Min=%3.0lf Max=%3.0lf",
                Parameter_GetMinimumValue(&me->KneeAngle),
                Parameter_GetMaximumValue(&me->KneeAngle));
        Screen_PrintMessage(me->Message);

        // 0123456789123456
        // Cur  Min    Max
        // xxx.x xxx.x xxx.x
        // Enable a piece of code in the main loop that
        // repeatedly updates the "current angle" of this state
        me->ShallMainLoopUpdateAngleReading = TRUE;
    }
}  // End of Goniometer Reading Check State

//=============================================================================
// Ankle Strap Retract/Release State
//=============================================================================
void UserInterface_AnkleStrapRetractRelease_State(UserInterface *me,
                                                  Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            // Go to CPM startup state
            FSM_Transition(&me->Parent, UserInterface_ConfirmCPMStartup_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            // Else, knee angle is invalid, so do nothing.
            break;

        case BACK_BUTTON_PRESSED:
            FSM_Transition(&me->Parent,
                           UserInterface_GoniometerReadingCheck_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case INCREMENT_BUTTON_PRESSED:
            // Only release cable and show percent release while button is
            // pressed and knee angle is valid
            Motor_SetPercentCableReleased(
                &me->CPM_Motor, Motor_GetPercentCableReleased(&me->CPM_Motor) + 1);
            break;

        case DECREMENT_BUTTON_PRESSED:
            // Only retract cable and show percent release while button is
            // pressed and knee angle is valid
            Motor_SetPercentCableReleased(
                &me->CPM_Motor, Motor_GetPercentCableReleased(&me->CPM_Motor) - 1);
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI \
                    at the Ankle Strap Retract/Release State\r\n");
            break;
    }

    // One-off message
    if (me->HasUserSeenAttachAnkleStrapMessage == FALSE)
    {
        // Prompt user to attach goniometer
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Please attach   ");
        sprintf(&me->Message[1][0], "the ankle strap. ");
        Screen_PrintMessage(me->Message);
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
        me->HasUserSeenAttachAnkleStrapMessage = TRUE;
        // Prompt user to retract/release the cable
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Release Cable[+]");
        sprintf(&me->Message[1][0], "Retract Cable[-]");
        Screen_PrintMessage(me->Message);
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned =
        !(me->Parent.CurrentState ==
          &UserInterface_AnkleStrapRetractRelease_State);

    if (HasStateTransitioned == FALSE)
    {
        UserInterface_DisplayCableReleasedPercent(me);
    }
}

//=============================================================================
// Confirm CPM Startup State
//=============================================================================
void UserInterface_ConfirmCPMStartup_State(UserInterface *me,
                                           Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            // Go to CPM State
            Motor_SetSpeed(&me->CPM_Motor, 30);
            CPM_Runtime_StartCounting();
            FSM_Transition(&me->Parent,
                           UserInterface_ContinuousPassiveMotion_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case BACK_BUTTON_PRESSED:
            // Go to Attach Ankle Strap State
            FSM_Transition(&me->Parent,
                           UserInterface_AnkleStrapRetractRelease_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case INCREMENT_BUTTON_PRESSED:
            // Do Nothing
            break;

        case DECREMENT_BUTTON_PRESSED:
            // Do Nothing
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI \
                    at the Confirm CPM Startup State\r\n");
            break;
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned =
        !(me->Parent.CurrentState == &UserInterface_ConfirmCPMStartup_State);

    if (HasStateTransitioned == FALSE)
    {
        // Prompt user to retract/release the cable
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Start motion at ");
        sprintf(&me->Message[1][0], "%d deg/min?",
                CPM_START_SPEED_DEGREES_PER_MINUTE);
        Screen_PrintMessage(me->Message);
    }
}

//=============================================================================
// CPM State
//=============================================================================
void UserInterface_ContinuousPassiveMotion_State(UserInterface *me,
                                                 Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            /* "Soft stop": Stop motor and go back to confirmation state */
            Motor_Stop(&me->CPM_Motor);
            CPM_Runtime_StopCounting();
            me->ShallMainLoopHandleCPMMessage = FALSE;
            FSM_Transition(&me->Parent, UserInterface_ConfirmCPMStartup_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case BACK_BUTTON_PRESSED:
            /* "Soft stop": Stop motor and go back to confirmation state */
            Motor_Stop(&me->CPM_Motor);
            CPM_Runtime_StopCounting();
            me->ShallMainLoopHandleCPMMessage = FALSE;
            FSM_Transition(&me->Parent, UserInterface_ConfirmCPMStartup_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case INCREMENT_BUTTON_PRESSED:
            // Make sure we increment from current speed
            Parameter_SetValue(&me->New_CPM_Speed,
                               Motor_GetSpeed(&me->CPM_Motor));
            // Set new value to current + 1
            Parameter_IncrementValue(&me->New_CPM_Speed);
            me->ShallMainLoopHandleCPMMessage = FALSE;
            // Go to change speed state
            FSM_Transition(&me->Parent, UserInterface_ConfirmSpeedChange_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case DECREMENT_BUTTON_PRESSED:
            // Make sure we decrement from current speed
            Parameter_SetValue(&me->New_CPM_Speed,
                               Motor_GetSpeed(&me->CPM_Motor));
            // Set new value to current - 1
            Parameter_DecrementValue(&me->New_CPM_Speed);
            me->ShallMainLoopHandleCPMMessage = FALSE;
            // Go to change speed state
            FSM_Transition(&me->Parent, UserInterface_ConfirmSpeedChange_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI \
                        at the Continuous Passive Motion State\r\n");
            break;
    }  // End of signal handling

    bool HasStateTransitioned = !(me->Parent.CurrentState ==
                                  &UserInterface_ContinuousPassiveMotion_State);

    if (HasStateTransitioned == FALSE)
    {
        me->ShallMainLoopHandleCPMMessage = TRUE;
    }
}

//=============================================================================
// Confirm Speed ChangeState
//=============================================================================
void UserInterface_ConfirmSpeedChange_State(UserInterface *me,
                                            Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED:
            // Set current to new
            Motor_SetSpeed(&me->CPM_Motor,
                           Parameter_GetValue(&me->New_CPM_Speed));
            // Go to CPM state
            FSM_Transition(&me->Parent,
                           UserInterface_ContinuousPassiveMotion_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case BACK_BUTTON_PRESSED:
            // Set new to current
            Parameter_SetValue(&me->New_CPM_Speed,
                               Motor_GetSpeed(&me->CPM_Motor));
            // Go to CPM state
            FSM_Transition(&me->Parent,
                           UserInterface_ContinuousPassiveMotion_State);
            // Update display in next function without any inputs
            UserInterface_ExecuteCurrentStateFunction(me);
            break;

        case INCREMENT_BUTTON_PRESSED:
            Parameter_IncrementValue(&me->New_CPM_Speed);
            break;

        case DECREMENT_BUTTON_PRESSED:
            Parameter_DecrementValue(&me->New_CPM_Speed);
            break;

        case NO_OPERATION:
            // Do nothing
            break;

        default:
            DEBUG_PRINT(
                "Error: Invalid signal has been received by the UI \
                    at the Confirm Speed Change State\r\n");
            break;
    }

    bool HasStateTransitioned =
        !(me->Parent.CurrentState == &UserInterface_ConfirmSpeedChange_State);

    if (HasStateTransitioned == FALSE)
    {
        // Prompt user to change the speed of the device
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Crnt= %4.1d dpm",
                Motor_GetSpeed(&me->CPM_Motor));
        sprintf(&me->Message[1][0], "New = %4.1lf dpm",
                Parameter_GetValue(&me->New_CPM_Speed));
        Screen_PrintMessage(me->Message);
    }
}
/* [] END OF FILE */