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
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM)
{
    DEBUG_PRINT("UI Constructor called");
    FSM_Constructor(&UI_FSM->Parent, &UserInterface_FSM_Initial_State);
    DEBUG_PRINT("UI Initial state called");

    UI_FSM->IsFirstTimeSettingMinAngle = TRUE;
    UI_FSM->IsFirstTimeSettingMaxAngle = TRUE;
    UI_FSM->IsFirstSetup = TRUE;
    
    // One should not expect for the initial state to do anything with this signal
    Event InitialEvent;
    InitialEvent.EventSignal = CONFIRM_BUTTON_PRESSED; 
    FSM_ExecuteInitialState(&UI_FSM->Parent, &InitialEvent);
}

//=============================================================================
// Print Message
//=============================================================================
void UserInterface_FSM_PrintMessage(
                    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW+1])
{
    Screen_ClearDisplay();
    Screen_PrintString(&Message[0][0]);
    Screen_PrintString(&Message[1][0]);
}
                                
//=============================================================================
// State Function Implementations -- User Interface Finite State Machine Class


//=============================================================================
// Initial State
//=============================================================================
void UserInterface_FSM_Initial_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
    DEBUG_PRINT("UI Initial State Called called");
    
    // Print welcome message while UI starts up
    //                               1234567890123456
    sprintf(&UI_FSM->Message[0][0], "   Welcome to   ");
    sprintf(&UI_FSM->Message[1][0], "     SeatPM     ");
    UserInterface_FSM_PrintMessage(UI_FSM->Message);
    
    // UI Startup Code Goes Here
    
    // Transition to Setting Minimum Angle
    FSM_Transition(&UI_FSM->Parent,
                   &UserInterface_FSM_SetMinimumAngle_State);
}
 
//=============================================================================
// Goniometer Configuration States

//=============================================================================
// Set Minimum Angle State
//=============================================================================
void UserInterface_FSM_SetMinimumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{ 

    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            FSM_Transition(&UI_FSM->Parent,
                           &UserInterface_FSM_SetMaximumAngle_State);
        break;
        
        case BACK_BUTTON_PRESSED :
            // Do nothing... this is the first user-accessible state
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            Parameter_SetValue(&g_MinimumAngle, Parameter_GetValue(&g_MinimumAngle)+1);
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            Parameter_SetValue(&g_MinimumAngle, Parameter_GetValue(&g_MinimumAngle)-1);
        break;
        
        default :
            // TODO
        break;
    } // End of switch statmenet

    if(UI_FSM->IsFirstTimeSettingMinAngle == TRUE)
    {
        // Prompt user to set the minimum angle of the device
        //                               1234567890123456
        sprintf(&UI_FSM->Message[0][0], "Please set min. ");
        sprintf(&UI_FSM->Message[1][0], "knee angle...   ");
        UserInterface_FSM_PrintMessage(UI_FSM->Message);

        UI_FSM->IsFirstTimeSettingMinAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Print current minimum angle
    //                               1234567890123456
    sprintf(&UI_FSM->Message[0][0], "Min. knee angle");
    sprintf(&UI_FSM->Message[1][0], "= %4.1lf degrees", Parameter_GetValue(&g_MinimumAngle));
    UserInterface_FSM_PrintMessage(UI_FSM->Message);
}
 
//=============================================================================
// Set Maximum Angle State
//=============================================================================
void UserInterface_FSM_SetMaximumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            if(IsFirstSetup == TRUE)
            {
                 // Go to attach goniometer state
                FSM_Transition(&UI_FSM->Parent,
                            &UserInterface_FSM_AttachAnkleStrapMessage_State);
            }
            else
            {
                // Skip attach goniometer message state
                FSM_Transition(&UI_FSM->Parent,
                               &UserInterface_FSM_GoniometerReadingCheck_State);
            }
        break;
        
        case BACK_BUTTON_PRESSED :
        // Go back to minimum angle state
            FSM_Transition(&UI_FSM->Parent,
                           &UserInterface_FSM_SetMinimumAngle_State);
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            Parameter_SetValue(&g_MaximumAngle, Parameter_GetValue(&g_MaximumAngle)+1);
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            Parameter_SetValue(&g_MaximumAngle, Parameter_GetValue(&g_MaximumAngle)-1);
        break;
        
        default :
            // TODO
        break;
    }

        if(UI_FSM->IsFirstTimeSettingMaxAngle == TRUE)
    {
        // Prompt user to set the max angle of the device
        //                               1234567890123456
        sprintf(&UI_FSM->Message[0][0], "Please set max. ");
        sprintf(&UI_FSM->Message[1][0], "knee angle...   ");
        UserInterface_FSM_PrintMessage(UI_FSM->Message);

        UI_FSM->IsFirstTimeSettingMinAngle = FALSE;
        CyDelay(MESSAGE_ON_SCREEN_TIME_MS);
    }

    // Print current maximum angle
    //                               1234567890123456
    sprintf(&UI_FSM->Message[0][0], "Max. knee angle");
    sprintf(&UI_FSM->Message[1][0], "= %4.1lf degrees", Parameter_GetValue(&g_MaximumAngle));
    UserInterface_FSM_PrintMessage(UI_FSM->Message);
}

//=============================================================================
// Attach Goniometer Message
//============================================================================= 
void UserInterface_FSM_AttachGoniometerMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // Go to goniometer reading check state
            FSM_Transition(&(UI_FSM->Parent), UserInterface_FSM_GoniometerReadingCheck_State);
        break;
        
        case BACK_BUTTON_PRESSED :
            FSM_Transition(&(UI_FSM->Parent), UserInterface_FSM_SetMaximumAngle_State);
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // Do nothing
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // Do nothing
        break;
        
        default :
            // TODO
        break;

            // Prompt user to attach goniometer
            //                               1234567890123456
            sprintf(&UI_FSM->Message[0][0], "Please attach   ");
            sprintf(&UI_FSM->Message[1][0], "the knee brace. ");
            UserInterface_FSM_PrintMessage(UI_FSM->Message);
    }
}
 
//=============================================================================
// Goniometer Reading Check State
//=============================================================================
void UserInterface_FSM_GoniometerReadingCheck_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            bool KneeAngleIsValid = 
             !(g_KneeAngle > Parameter_GetValue(&g_MaximumAngle) || 
               g_KneeAngle < Parameter_GetValue(&g_MinimumAngle) ||
               g_KneeAngle == INVALID_ANGLE)
            if(KneeAngleIsValid != TRUE)
            {
                FSM_Transition(&UI_FSM->Parent, UserInterface_FSM_InvalidGoniometerReading_State)
            }
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }

    // Print current vs max and min
    //                               1234567890123456
    sprintf(&UI_FSM->Message[0][0], "Current %4.1lf deg");
    sprintf(&UI_FSM->Message[1][0], "Min=%3lf Max=%3lf");
    UserInterface_FSM_PrintMessage(UI_FSM->Message);
}
 
//=============================================================================
// Invalid Goniometer Reading State
//=============================================================================
void UserInterface_FSM_InvalidGoniometerReading_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 

//-----------------------------------------------------------------------------
// Ankle Strap Configuration States 
void UserInterface_FSM_AttachAnkleStrapMessage_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
        switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_AnkleStrapRetractRelease_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_DisplayCableReleaseAmount_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
        switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 

//-----------------------------------------------------------------------------
// CPM Use States
void UserInterface_FSM_ConfirmCPMStartup_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
        switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_ContinuousPassiveMotion_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_ConfirmSpeedChange_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case CONFIRM_BUTTON_PRESSED :
            // TODO
        break;
        
        case BACK_BUTTON_PRESSED :
            // TODO
        break;
        
        case INCREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        case DECREMENT_BUTTON_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
                                

/* [] END OF FILE */
