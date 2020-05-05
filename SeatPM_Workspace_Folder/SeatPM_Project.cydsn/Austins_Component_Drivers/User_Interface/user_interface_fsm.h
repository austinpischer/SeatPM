// TODO: File header


// Multiple Inlusion Protection
#ifndef USER_INTERFACE_FSM_H
#define USER_INTERFACE_FSM_H

//-----------------------------------------------------------------------------
// Inclusions
#include "finite_state_machine.h"
#include "goniometer_driver.h"
#include "project.h"
#include "stdio.h"

//-----------------------------------------------------------------------------
// Definitions
#define MESSAGE_ROWS 2
#define MESSAGE_CHARACTERS_PER_ROW 16

//-----------------------------------------------------------------------------
// Typedefs
// Define "struct <tag>" as type "<tag>"
typedef struct UserInterface_FSM UserInterface_FSM;
typedef struct UserInterface_FSM_Event UserInterface_FSM_Event;
    
// ----------------------------------------------------------------------------
// Event Struct -- User Interface Finite State Machine
struct UserInterface_FSM_Event
{
    Event Parent; // Acheiving inheritance by requiring base class
};

//=============================================================================
// Data Members -- UserInterface_FSM Class (Derived from FiniteStateMachine)
//=============================================================================
struct UserInterface_FSM
{ 
    // Acheiving inheritance by requiring base class.
    FiniteStateMachine Parent;
    
    // Message to be displayed on screen
    // NOTE: +1 for c-string null terminator
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW+1];
};

//=============================================================================
// Signals used by UserInterface_FSM Class
//=============================================================================
enum UserInterface_FSM_Signals
{
    UI_FSM_SIGNAL__BUTTON_CONFIRM_PRESSED,
    UI_FSM_SIGNAL__BUTTON_BACK_PRESSED,
    UI_FSM_SIGNAL__BUTTON_INCREMENT_PRESSED,
    UI_FSM_SIGNAL__BUTTON_DECREMENT_PRESSED,
};

//=============================================================================
// Method Members -- User Interface Finite State Machine Class
//=============================================================================

//-----------------------------------------------------------------------------
// General Functions
void UserInterface_FSM_Constructor(UserInterface_FSM *UI_FSM);

// Clears the UI Screen and then prints 
void UserInterface_FSM_PrintMessage(
                    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW+1]);
                                
//=============================================================================
// State Functions -- User Interface Finite State Machine Class
//=============================================================================

//-----------------------------------------------------------------------------
// Generic States
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
