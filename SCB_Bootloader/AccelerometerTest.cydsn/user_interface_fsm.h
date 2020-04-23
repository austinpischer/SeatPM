#ifndef USER_INTERFACE_FSM_H
#define USER_INTERFACE_FSM_H

#include "finite_state_machine.h"
#include "goniometer_driver.h"
#include "project.h"
#include "stdio.h"

// Define "struct <tag>" as type "<tag>"
typedef struct UserInterface_FSM UserInterface_FSM;
typedef struct UserInterface_FSM_Event UserInterface_FSM_Event;

// Derived class of FiniteStateMachine base class
struct UserInterface_FSM
{
    
    FiniteStateMachine parent; // Acheiving inheritance by requiring base class
    char KneeAngleString[17]; // Limit to 16 characters + null terminator
};

// Derived class of Event 
struct UserInterface_FSM_Event
{
    Event parent; // Acheiving inheritance by requiring base class
};

// Signals used by UserInterface_FSM
enum UserInterface_FSM_Signals
{
    INCREMENT_BUTTON_PRESSED_SIGNAL,
    DECREMENT_BUTTON_PRESSED_SIGNAL,
    CONFIRM_BUTTON_PRESSED_SIGNAL,
    BACK_BUTTON_PRESSED_SIGNAL
};

//=============================================================================
// User Interface FSM function prototypes:
// 
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM);

void UserInterface_FSM_UpdateCurrentKneeAngleString(
                                            UserInterface_FSM *UI_FSM, 
                                            Goniometer* KneeGoniometer);
                                
//=============================================================================
// User Interface FSM state function protoypes:
void UserInterface_FSM_Initial_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
//-----------------------------------------------------------------------------
// Goniometer Configuration States
void UserInterface_FSM_SetMinimumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_SetMaximumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_AttachGoniometerMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_GoniometerReadingCheck_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_InvalidGoniometerReading_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);

//-----------------------------------------------------------------------------
// Ankle Strap Configuration States 
void UserInterface_FSM_AttachAnkleStrapMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_AnkleStrapRetractRelease_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_DisplayCableReleaseAmount_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);

//-----------------------------------------------------------------------------
// CPM Use States
void UserInterface_FSM_ConfirmCPMStartup_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_ContinuousPassiveMotion_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
void UserInterface_FSM_ConfirmSpeedChange_State(
                                UserInterface_FSM *UI_FSM, 
                                UserInterface_FSM_Event const *event);
                                
#endif
/* [] END OF FILE */
