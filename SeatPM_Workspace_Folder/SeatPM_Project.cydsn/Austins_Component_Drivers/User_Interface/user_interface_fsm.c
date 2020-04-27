/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "user_interface_fsm.h"

//=============================================================================
// User Interface FSM function prototypes:
// 
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM)
{
    FSM_Constructor(&UI_FSM->Parent, &UserInterface_FSM_Initial_State);
}
                                
//=============================================================================
// User Interface FSM state function protoypes:
void UserInterface_FSM_Initial_State(
                                UserInterface_FSM *UI_FSM,
                                Event const *MyEvent)
{
    Screen_ClearDisplay();
    sprintf(&UI_FSM->CurrentMessage[0][0], "     SeatPM     ");
    Screen_PrintString(&UI_FSM->CurrentMessage[0][0]);

    FSM_Transition((FiniteStateMachine *)UI_FSM, &UserInterface_FSM_SetMinimumAngle_State);
        // NOTE: "(FiniteStateMachine *)UI_FSM" casts the passed in pointer as
        //       a FiniteStateMachine Pointer, meaning that it accesses the UI_FSM struct
        //       from the start of its data, which in this case is the Parent FSM struct,
        //       and reads the data members as a FiniteStateMachine struct
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
