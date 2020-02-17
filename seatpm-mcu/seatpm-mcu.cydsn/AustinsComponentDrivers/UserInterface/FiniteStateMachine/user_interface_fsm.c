#include "user_interface_fsm.h"

//=============================================================================
// User Interface FSM function prototypes:
// 
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM)
{
    // TODO
}
                                
//=============================================================================
// User Interface FSM state function protoypes:
void UserInterface_FSM_Initial_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
//-----------------------------------------------------------------------------
// Goniometer Configuration States
void UserInterface_FSM_SetMinimumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_SetMaximumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_AttachGoniometerMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_GoniometerReadingCheck_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_InvalidGoniometerReading_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 

//-----------------------------------------------------------------------------
// Ankle Strap Configuration States 
void UserInterface_FSM_AttachAnkleStrapMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_AnkleStrapRetractRelease_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_DisplayCableReleaseAmount_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 

//-----------------------------------------------------------------------------
// CPM Use States
void UserInterface_FSM_ConfirmCPMStartup_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_ContinuousPassiveMotion_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
void UserInterface_FSM_ConfirmSpeedChange_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event)
{
    // TODO
}
 
                                