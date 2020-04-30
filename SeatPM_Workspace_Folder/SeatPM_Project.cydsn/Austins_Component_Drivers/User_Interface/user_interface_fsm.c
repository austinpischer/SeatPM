// TODO: File header

//-----------------------------------------------------------------------------
// Inclusions
#include "austin_debug.h"
#include "user_interface_fsm.h"

//=============================================================================
// Method Implementations -- User Interface Finite State Machine Class
//=============================================================================

//-----------------------------------------------------------------------------
// General Functions


void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM)
{
    DEBUG_PRINT("UI Constructor called");
    FSM_Constructor(&UI_FSM->Parent, &UserInterface_FSM_Initial_State);
    DEBUG_PRINT("UI Initial state called");
    
    // One should not expect for the initial state to do anything with this signal
    Event InitialEvent;
    InitialEvent.EventSignal = UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED; 
    FSM_ExecuteInitialState(&UI_FSM->Parent, &InitialEvent);
}


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

//-----------------------------------------------------------------------------
void UserInterface_FSM_Initial_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
    DEBUG_PRINT("UI Initial State Called called");
    
    // Print "SeatPM" to screen while UI starts up
    sprintf(&UI_FSM->Message[0][0], "   Welcome to   ");
    sprintf(&UI_FSM->Message[1][0], "     SeatPM     ");
    UserInterface_FSM_PrintMessage(UI_FSM->Message);
    
    // UI Startup Code Goes Here
    
    // Transition to Setting Minimum Angle
    FSM_Transition(&UI_FSM->Parent,
                   &UserInterface_FSM_SetMinimumAngle_State);
}
 
//-----------------------------------------------------------------------------
// Goniometer Configuration States

void UserInterface_FSM_SetMinimumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 

void UserInterface_FSM_SetMaximumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_AttachGoniometerMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_GoniometerReadingCheck_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
void UserInterface_FSM_InvalidGoniometerReading_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *MyEvent)
{
    switch(MyEvent->EventSignal)
    {
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
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
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
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
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
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
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
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
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
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
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
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
        case UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_BACK_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED :
            // TODO
        break;
        
        case UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED :
            // TODO
        break;
        
        default :
            // TODO
        break;
    }
}
 
                                

/* [] END OF FILE */
