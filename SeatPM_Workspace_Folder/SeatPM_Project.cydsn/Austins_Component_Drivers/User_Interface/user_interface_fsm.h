/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: user_interface_fsm.h
 * Author: Austin Pischer
 * 
 * File Explanation:
// TODO
 *============================================================================*/

// Start of multiple inclusion protection
#ifndef USER_INTERFACE_FSM_H
#define USER_INTERFACE_FSM_H

//=============================================================================
// Inclusions
//=============================================================================
#include "finite_state_machine.h" // For base class
#include "goniometer_driver.h" // For ???
#include "project.h" // For PSoC
#include "stdio.h"  // For sprintf
#include "austin_debug.h" // For bool type
#include "austin_parameter.h" // For paramter class

//=============================================================================
// Definitions
//=============================================================================
#define MESSAGE_ROWS 2
#define MESSAGE_CHARACTERS_PER_ROW 16
#define MESSAGE_ON_SCREEN_TIME_MS 500 

//=============================================================================
// Type definitions
//=============================================================================
// Define "struct <tag>" as type "<tag>"
typedef struct UserInterface_FSM UserInterface_FSM;
typedef struct UserInterface_FSM_Event UserInterface_FSM_Event;

//=============================================================================
// External Global Variables from main.c
//=============================================================================
extern Parameter g_MinimumAngle;
extern Parameter g_MaximumAngle;
extern Parameter g_CPM_Speed;
extern Parameter g_CableReleasedPercent;
    
//=============================================================================
// Event Struct -- User Interface Finite State Machine
//=============================================================================
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

    bool IsFirstTimeSettingMinAngle;
    bool IsFirstTimeSettingMaxAngle;
    bool IsFirstSetup;
};

//=============================================================================
// Signals used by UserInterface_FSM Class
//=============================================================================
enum UserInterface_FSM_Signals
{
    CONFIRM_BUTTON_PRESSED,
    BACK_BUTTON_PRESSED,
    INCREMENT_BUTTON_PRESSED,
    DECREMENT_BUTTON_PRESSED,
    NO_OPERATION, //???
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
                                
#endif // End of multiple inclusion protection
/* [] END OF FILE */