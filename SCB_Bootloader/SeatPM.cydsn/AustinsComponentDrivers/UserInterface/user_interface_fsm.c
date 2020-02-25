#include "user_interface_fsm.h"

//=============================================================================
// User Interface FSM function prototypes:
// 
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM)
{
    // TODO
}
                                
void UserInterface_FSM_UpdateCurrentKneeAngleString (
                                            UserInterface_FSM *UI_FSM, 
                                            Goniometer* KneeGoniometer)
{
    if(KneeGoniometer->CurrentAngle == INVALID_ANGLE)
    {
        // Convert invaid angle to string 0123456789123456
        sprintf(UI_FSM->KneeAngleString, "Crnt=INVALID deg");
    }
    else
    {
        // Angle is valid: print "Crnt=___.__ deg"
        // Where % represents the angle number argument,
        // 6 is the number of characters in the field
        // .5 is the precision of the field 
        //      (i.e. number of number characters is 5, plus decimal delimiter)
        // lf means that we are printing a double (i.e. long float)
        sprintf(UI_FSM->KneeAngleString,
                "Crnt=%6.5lf deg",
                KneeGoniometer->CurrentAngle);
    }
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
 
                                