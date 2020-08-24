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
    DEBUG_PRINT("UI Constructor called\r\n");
    FSM_Constructor(&me->Parent, &UI_FSM_Initial_State);

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

    DEBUG_PRINT("Executing Initial State\r\n");
    FSM_ExecuteInitialState(&me->Parent, &InitialEvent);
}

//=============================================================================
// Print Message
//=============================================================================
void UI_FSM_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1])
{
    Screen_ClearDisplay();

    DEBUG_PRINT(&Message[0][0]);
    DEBUG_PRINT("\r\n");

    Screen_PrintString(&Message[0][0]);

    Screen_Position(1,0);

    DEBUG_PRINT(&Message[1][0]);
    DEBUG_PRINT("\r\n\r\n");

    Screen_PrintString(&Message[1][0]);
}

//=============================================================================
// Validate Current Goniometer Measurement
//=============================================================================
bool UI_FSM_IsKneeAngleValid(UI_FSM *me)
{
    Parameter_ValueValidationResult Result 
       = Parameter_ValidateValue(&me->KneeAngle);
    
    // Handle non-errors
    if(Result == VALUE_VALID)
    {
        return(TRUE);
    }
    // Handle errors
    else if (Result == VALUE_GREATER_THAN_MAXIMUM)
    {
        // Print knee angle too large error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle above");
        sprintf(&me->Message[1][0], "maximum limit!  ");
        UI_FSM_PrintMessage(me->Message);
    }
    else if (Result == VALUE_LESS_THAN_MINIMUM)
    {
        // Print knee angle too small error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle below ");
        sprintf(&me->Message[1][0], "minimum limit!  ");
        UI_FSM_PrintMessage(me->Message);
    }
    else if (Result == VALUE_EQUAL_TO_INVALID)
    {
        // Print knee angle invalid error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle is   ");
        sprintf(&me->Message[1][0], "INVALID_ANGLE ! ");
        UI_FSM_PrintMessage(me->Message);
    }
    else
    {
        // Print knee angle invalid error
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Knee Angle is   ");
        sprintf(&me->Message[1][0], "unspecified!   ");
        UI_FSM_PrintMessage(me->Message);
    }
    CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    return (FALSE);
}

//=============================================================================
// Display Cable Released Percent
//=============================================================================
void UI_FSM_DisplayCableReleasedPercent(UI_FSM *me)
{
    //                           1234567890123456
    sprintf(&me->Message[0][0], "Cable Released %%"); // Double % shows "%"
    sprintf(&me->Message[1][0],
            "%lf %%",
            Parameter_GetValue(&(g_CPM_Motor.PercentCableReleased)));
    UI_FSM_PrintMessage(me->Message);
}

//=============================================================================
// Execute Current State Function 
//=============================================================================
void UI_FSM_ExecuteCurrentStateFunction(UI_FSM *me)
{
    Event NoOperationEvent;
    NoOperationEvent.EventSignal = NO_OPERATION;
    DEBUG_PRINT("Executing State...\r\n");
    FSM_Dispatch(&me->Parent, &NoOperationEvent);
}

//=============================================================================
// Print Invalid Signal Message
//=============================================================================
void UI_FSM_PrintInvalidSignalMessage(UI_FSM *me)
{
    DEBUG_PRINT("ERROR: Invalid Singal!\r\n");
}

//=============================================================================
// State Function Implementations -- User Interface Finite State Machine Class
//

//=============================================================================
// Initial State
//=============================================================================
void UI_FSM_Initial_State(UI_FSM *me, Event const *MyEvent)
{
    DEBUG_PRINT("UI Initial State Called\r\n");

    // Print welcome message while UI starts up
    //                           1234567890123456
    sprintf(&me->Message[0][0], "   Welcome to   ");
    sprintf(&me->Message[1][0], "     SeatPM     ");
    UI_FSM_PrintMessage(me->Message);
    CyDelay(MESSAGE_ON_SCREEN_TIME_MS);

    // UI Startup Code Goes Here

    // Transition to Setting Minimum Angle
    DEBUG_PRINT("Transition to Set Minimum Knee Angle\r\n");
    FSM_Transition(&me->Parent,
                   &UI_FSM_SetMinimumKneeAngle_State);
    // Update display in next function without any inputs
    UI_FSM_ExecuteCurrentStateFunction(me);
} // End of initial state

//=============================================================================
// Goniometer Configuration States

//=============================================================================
// Set Minimum Knee Angle State
//=============================================================================
void UI_FSM_SetMinimumKneeAngle_State(UI_FSM *me, Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        DEBUG_PRINT("Transition to Set Maximum Knee Angle\r\n");
        FSM_Transition(&me->Parent,
                       &UI_FSM_SetMaximumKneeAngle_State);
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case BACK_BUTTON_PRESSED:
        // Do nothing... this is the first user-accessible state
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Do not increment minval above maxval
        if(Parameter_GetMinimumValue(&me->KneeAngle)+1 
            > Parameter_GetMaximumValue(&me->KneeAngle))
        {
            // Do not increment
        }
        else
        {
            Parameter_SetMinimumValue(&me->KneeAngle, 
                Parameter_GetMinimumValue(&me->KneeAngle)+1);
        }
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Do not  decrement minval below abs min
        if(Parameter_GetMinimumValue(&me->KneeAngle)-1 
            < ABSOLUTE_MINIMUM_KNEE_ANGLE)
        {
            // Do not decrement
        }
        else
        {
            Parameter_SetMinimumValue(&me->KneeAngle, 
                    Parameter_GetMinimumValue(&me->KneeAngle)-1);   
        }
        break;

    case NO_OPERATION:
        // Do nothing
        break;

    default:
        DEBUG_PRINT("Error: Invalid signal has been received by the UI \
                     at the Set Minimum Knee Angle State\r\n");
        break;
    } // End of signal processing
    
    // One-off message
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

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_SetMinimumKneeAngle_State);

    if(HasStateTransitioned == FALSE)
    {
         // Print current minimum angle
         //                           1234567890123456
        sprintf(&me->Message[0][0], "Min. knee angle ");
        sprintf(&me->Message[1][0], "= %4.1lf degrees",
                Parameter_GetMinimumValue(&me->KneeAngle));
        UI_FSM_PrintMessage(me->Message);
    }
} // End of set minimum knee angle state

//=============================================================================
// Set Maximum Knee Angle State
//=============================================================================
void UI_FSM_SetMaximumKneeAngle_State(UI_FSM *me, Event const *MyEvent)
{
    switch (MyEvent->EventSignal)
    {
    case CONFIRM_BUTTON_PRESSED:
        DEBUG_PRINT("Transition to Goniometer Reading Check\r\n");
        FSM_Transition(&me->Parent,
                       &UI_FSM_GoniometerReadingCheck_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case BACK_BUTTON_PRESSED:
        // Go back to minimum angle state
        DEBUG_PRINT("Transition to Set Minimum Knee Angle\r\n");
        FSM_Transition(&me->Parent,
                       &UI_FSM_SetMinimumKneeAngle_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case INCREMENT_BUTTON_PRESSED:
        if(Parameter_GetMaximumValue(&me->KneeAngle)+1 > ABSOLUTE_MAXIMUM_KNEE_ANGLE)
        {
            // Do not increment
        }
        else
        {
            Parameter_SetMaximumValue(&me->KneeAngle, 
                Parameter_GetMaximumValue(&me->KneeAngle)+1);
        }
        break;

    case DECREMENT_BUTTON_PRESSED:
        if(Parameter_GetMaximumValue(&me->KneeAngle)-1 < Parameter_GetMinimumValue(&me->KneeAngle))
        {
            // Do not decrement
        }
        else
        {
            Parameter_SetMaximumValue(&me->KneeAngle, Parameter_GetMaximumValue(&me->KneeAngle)-1);
        }
        break;

    case NO_OPERATION:
        // Do nothing
        break;

    default:
                DEBUG_PRINT("Error: Invalid signal has been received by the UI \
                            at the Set Maximum Knee Angle State\r\n");
        break;
    } // End of signal processing

    // One-off message
    if (me->IsFirstTimeSettingMaxAngle == TRUE)
    {
        // Prompt user to set the max angle of the device
        //                               1234567890123456
        sprintf(&me->Message[0][0], "Please set max. ");
        sprintf(&me->Message[1][0], "knee angle...   ");
        UI_FSM_PrintMessage(me->Message);

        me->IsFirstTimeSettingMaxAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_SetMaximumKneeAngle_State);

    if(HasStateTransitioned == FALSE)
    {
        // Print current maximum angle
        //                               1234567890123456
        sprintf(&me->Message[0][0], "Max. knee angle");
        sprintf(&me->Message[1][0],
                "= %4.1lf degrees",
                Parameter_GetMaximumValue(&me->KneeAngle));
        UI_FSM_PrintMessage(me->Message);
    }
}// End of Set Maximum Knee Angle State

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
            DEBUG_PRINT("Transition to Ankle Strap R/R\r\n");
            me->ShallMainLoopUpdateAngleReading = FALSE; 
            FSM_Transition(&me->Parent, UI_FSM_AnkleStrapRetractRelease_State);
            // Update display in next function without any inputs
            UI_FSM_ExecuteCurrentStateFunction(me);
        }
        // Else, knee angle is invalid, so do nothing.
        break;

    case BACK_BUTTON_PRESSED:
        // Go back to set maximum angle
        DEBUG_PRINT("Transition to Set Maximum Knee Angle\r\n");
        me->ShallMainLoopUpdateAngleReading = FALSE; 
        FSM_Transition(&me->Parent, UI_FSM_SetMaximumKneeAngle_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
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
        DEBUG_PRINT("Error: Invalid signal has been received by the UI \
                    at the Check Goniometer Reading Check State\r\n");
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

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_GoniometerReadingCheck_State);

    if(HasStateTransitioned == FALSE)
    {
        // Print current vs max and min
        //                           1234567890123456
        sprintf(&me->Message[0][0], 
                "Current=%4.1lfdeg", 
                Parameter_GetValue(&me->KneeAngle));
        sprintf(&me->Message[1][0],
                "Min=%3.0lf Max=%3.0lf",
                Parameter_GetMinimumValue(&me->KneeAngle),
                Parameter_GetMaximumValue(&me->KneeAngle));
        UI_FSM_PrintMessage(me->Message);

        //0123456789123456
        //Cur  Min    Max
        //xxx.x xxx.x xxx.x
        // Enable a piece of code in the main loop that
        // repeatedly updates the "current angle" of this state
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
            // Update display in next function without any inputs
            UI_FSM_ExecuteCurrentStateFunction(me);
        }
        // Else, knee angle is invalid, so do nothing.
        break;

    case BACK_BUTTON_PRESSED:
        FSM_Transition(&me->Parent, UI_FSM_GoniometerReadingCheck_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Only release cable and show percent release while button is pressed
        // and knee angle is valid
        if(UI_FSM_IsKneeAngleValid(me) == TRUE)
        {
            Motor_SetPercentCableReleased(&g_CPM_Motor, 
                Motor_GetPercentCableReleased(&g_CPM_Motor)+1);
            UI_FSM_DisplayCableReleasedPercent(me);
            CyDelay(1000);//TODO
        }
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Only retract cable and show percent release while button is pressed
        // and knee angle is valid
        if(UI_FSM_IsKneeAngleValid(me) == TRUE)
        {
            Motor_SetPercentCableReleased(&g_CPM_Motor, 
                Motor_GetPercentCableReleased(&g_CPM_Motor)-1);
            UI_FSM_DisplayCableReleasedPercent(me);
            CyDelay(1000);//TODO
        }
        break;
    
    case NO_OPERATION:
        // Do nothing
        break;

    default:
        DEBUG_PRINT("Error: Invalid signal has been received by the UI \
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
        UI_FSM_PrintMessage(me->Message);
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
        me->HasUserSeenAttachAnkleStrapMessage = TRUE;
    }

    
    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_AnkleStrapRetractRelease_State);

    if(HasStateTransitioned == FALSE)
    {
        // Prompt user to retract/release the cable
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Release Cable[+]");
        sprintf(&me->Message[1][0], "Retract Cable[-]");
        UI_FSM_PrintMessage(me->Message);
    }

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
            Motor_SetSpeed(&g_CPM_Motor, 30);
            CPM_Runtime_StartCounting(&g_CPM_Runtime);
            FSM_Transition(&me->Parent, UI_FSM_ContinuousPassiveMotion_State);
            // Update display in next function without any inputs
            UI_FSM_ExecuteCurrentStateFunction(me);
        }
        break;

    case BACK_BUTTON_PRESSED:
        // Go to Attach Ankle Strap State
        FSM_Transition(&me->Parent, UI_FSM_AnkleStrapRetractRelease_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
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
        DEBUG_PRINT("Error: Invalid signal has been received by the UI \
                    at the Confirm CPM Startup State\r\n");
        break;
    }

    // Dont print message if state transitioned in signal processing
    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_ConfirmCPMStartup_State);

    if(HasStateTransitioned == FALSE)
    {
        // Prompt user to retract/release the cable
        //                           1234567890123456
        sprintf(&me->Message[0][0], "Start motion at ");
        sprintf(&me->Message[1][0], 
                "%d deg/min?", 
                CPM_START_SPEED_DEGREES_PER_MINUTE);
        UI_FSM_PrintMessage(me->Message);
    }
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
        /* "Soft stop": Stop motor and go back to confirmation state */
        Motor_Stop(&g_CPM_Motor);
        CPM_Runtime_StopCounting(&g_CPM_Runtime);
        me->ShallMainLoopHandleCPMMessage = FALSE;
        FSM_Transition(&me->Parent, UI_FSM_ConfirmCPMStartup_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case BACK_BUTTON_PRESSED:
        /* "Soft stop": Stop motor and go back to confirmation state */
        Motor_Stop(&g_CPM_Motor);
        CPM_Runtime_StopCounting(&g_CPM_Runtime);
        me->ShallMainLoopHandleCPMMessage = FALSE;
        FSM_Transition(&me->Parent, UI_FSM_ConfirmCPMStartup_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case INCREMENT_BUTTON_PRESSED:
        // Make sure we increment from current speed
        Parameter_SetValue(&me->New_CPM_Speed, Motor_GetSpeed(&g_CPM_Motor));
        // Set new value to current + 1
        Parameter_IncrementValue(&me->New_CPM_Speed);
        me->ShallMainLoopHandleCPMMessage = FALSE;
        // Go to change speed state
        FSM_Transition(&me->Parent, UI_FSM_ConfirmSpeedChange_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case DECREMENT_BUTTON_PRESSED:
        // Make sure we decrement from current speed
        Parameter_SetValue(&me->New_CPM_Speed, Motor_GetSpeed(&g_CPM_Motor));
        // Set new value to current - 1
        Parameter_DecrementValue(&me->New_CPM_Speed);
        me->ShallMainLoopHandleCPMMessage = FALSE;
         // Go to change speed state
        FSM_Transition(&me->Parent, UI_FSM_ConfirmSpeedChange_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case NO_OPERATION:
        // Do nothing
        break;

    default:
        DEBUG_PRINT("Error: Invalid signal has been received by the UI \
                        at the Continuous Passive Motion State\r\n");
        break;
    }// End of signal handling

    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_ContinuousPassiveMotion_State);

    if (HasStateTransitioned == FALSE)
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
        Motor_SetSpeed(&g_CPM_Motor, Parameter_GetValue(&me->New_CPM_Speed));
        // Go to CPM state
        FSM_Transition(&me->Parent, UI_FSM_ContinuousPassiveMotion_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
        break;

    case BACK_BUTTON_PRESSED:
        // Set new to current
        Parameter_SetValue(&me->New_CPM_Speed, Motor_GetSpeed(&g_CPM_Motor));
        // Go to CPM state
        FSM_Transition(&me->Parent, UI_FSM_ContinuousPassiveMotion_State);
        // Update display in next function without any inputs
        UI_FSM_ExecuteCurrentStateFunction(me);
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
        DEBUG_PRINT("Error: Invalid signal has been received by the UI \
                    at the Confirm Speed Change State\r\n");
        break;
    }

    bool HasStateTransitioned = 
        !(me->Parent.CurrentState == &UI_FSM_ConfirmSpeedChange_State);

    if(HasStateTransitioned == FALSE)
    {
        // Prompt user to change the speed of the device
        //                           1234567890123456
        sprintf(&me->Message[0][0], 
                "Crnt= %4.1d dpm",
                Motor_GetSpeed(&g_CPM_Motor));
        sprintf(&me->Message[1][0], 
                "New = %4.1lf dpm", 
                Parameter_GetValue(&me->New_CPM_Speed));
        UI_FSM_PrintMessage(me->Message);
    }
}

/* [] END OF FILE */
