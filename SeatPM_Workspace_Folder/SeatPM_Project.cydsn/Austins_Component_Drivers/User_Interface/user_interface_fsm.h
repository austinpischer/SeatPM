#ifndef USER_INTERFACE_FSM_H
#define USER_INTERFACE_FSM_H

#include "finite_state_machine.h"
#include "goniometer_driver.h"
#include "project.h"
#include "stdio.h"

#define MESSAGE_ROWS 2
#define MESSAGE_CHARACTERS_PER_ROW 16

// Define "struct <tag>" as type "<tag>"
typedef struct UserInterface_FSM UserInterface_FSM;
typedef struct UserInterface_FSM_Event UserInterface_FSM_Event;

// Derived class inheriting from FiniteStateMachine base class
struct UserInterface_FSM
{ 
    // Parent must be first member of struct so an instance of this struct can be cast to parent
    FiniteStateMachine Parent; // Acheiving inheritance by requiring base class
    char CurrentMessage[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW+1]; // +1 for c string null terminator 
};


// Derived class of Event 
struct UserInterface_FSM_Event
{
    Event Parent; // Acheiving inheritance by requiring base class
};

// Signals used by UserInterface_FSM
enum UserInterface_FSM_Signals
{
    UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED,
    UI_FSM_SIGNAL__BUTTON_BACK_PRESSED,
    UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED,
    UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED,
};

//=============================================================================
// User Interface FSM general function prototypes:
// 
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM);
                                
//=============================================================================
// User Interface FSM state function protoypes:
void UserInterface_FSM_Initial_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
//-----------------------------------------------------------------------------
// Goniometer Configuration States
void UserInterface_FSM_SetMinimumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_SetMaximumAngle_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_AttachGoniometerMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_GoniometerReadingCheck_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_InvalidGoniometerReading_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);

//-----------------------------------------------------------------------------
// Ankle Strap Configuration States 
void UserInterface_FSM_AttachAnkleStrapMessage_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_AnkleStrapRetractRelease_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_DisplayCableReleaseAmount_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);

//-----------------------------------------------------------------------------
// CPM Use States
void UserInterface_FSM_ConfirmCPMStartup_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_ContinuousPassiveMotion_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
void UserInterface_FSM_ConfirmSpeedChange_State(
                                UserInterface_FSM *UI_FSM, 
                                Event const *event);
                                
#endif
/* [] END OF FILE */
