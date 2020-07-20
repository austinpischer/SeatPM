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
#include "goniometer_driver.h"    // For ???
#include "project.h"              // For PSoC
#include "stdio.h"                // For sprintf
#include "austin_debug.h"         // For bool type
#include "austin_parameter.h"     // For paramter class

//=============================================================================
// Definitions
//=============================================================================
#define MESSAGE_ROWS 2
#define MESSAGE_CHARACTERS_PER_ROW 16
#define MESSAGE_ON_SCREEN_TIME_MS 2000
#define CPM_START_SPEED_DEGREES_PER_MINUTE 30

//=============================================================================
// Type definitions
//=============================================================================
// Define "struct <tag>" as type "<tag>"
typedef struct UI_FSM UI_FSM;
typedef struct UI_FSM_Event UI_FSM_Event;

//=============================================================================
// External Global Variables from main.c
//=============================================================================
extern Parameter g_MinimumAngle;
extern Parameter g_MaximumAngle;
extern Parameter g_CPM_Speed;
extern Parameter g_CableReleasedPercent;
extern Parameter g_CurrentAngle;

//=============================================================================
// Event Struct -- User Interface Finite State Machine
//=============================================================================
struct UI_FSM_Event
{
    Event Parent; // Acheiving inheritance by requiring base class
};

//=============================================================================
// Data Members -- UI_FSM Class (Derived from FiniteStateMachine)
//=============================================================================
struct UI_FSM
{
    // Acheiving inheritance by requiring base class.
    FiniteStateMachine Parent;

    // Message to be displayed on screen
    // NOTE: +1 for c-string null terminator
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1];

    bool IsFirstTimeSettingMinAngle;
    bool IsFirstTimeSettingMaxAngle;
    bool HasUserSeenAttachGoniometerMessage;
    bool ShallMainLoopUpdateAngleReading;
    bool HasUserSeenAttachAnkleStrapMessage;
    bool ShallMainLoopHandleCPMMessage;

    Parameter New_CPM_Speed;
};

//=============================================================================
// Signals used by UI_FSM Class
//=============================================================================
enum UI_FSM_Signals
{
    CONFIRM_BUTTON_PRESSED,
    BACK_BUTTON_PRESSED,
    INCREMENT_BUTTON_PRESSED,
    DECREMENT_BUTTON_PRESSED,
    NO_OPERATION,
};

//=============================================================================
// Method Members -- User Interface Finite State Machine Class
//=============================================================================

//-----------------------------------------------------------------------------
// General Functions
void UI_FSM_Constructor(UI_FSM *me);

// Clears the UI Screen and then prints
void UI_FSM_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1]);
bool UI_FSM_IsKneeAngleValid(UI_FSM *me);
void UI_FSM_DisplayCableReleasedPercent(UI_FSM *me);
void UI_FSM_ExecuteCurrentStateFunction(UI_FSM *me);
void UI_FSM_PrintInvalidSignalMessage(UI_FSM *me);

//=============================================================================
// State Functions -- User Interface Finite State Machine Class
//=============================================================================

//-----------------------------------------------------------------------------
// Generic States
void UI_FSM_Initial_State(UI_FSM *me, Event const *event);
//-----------------------------------------------------------------------------
// Goniometer Configuration States
void UI_FSM_SetMinimumKneeAngle_State(UI_FSM *me,Event const *event);
void UI_FSM_SetMaximumKneeAngle_State(UI_FSM *me, Event const *event);
void UI_FSM_GoniometerReadingCheck_State(UI_FSM *me,Event const *event);
void UI_FSM_AnkleStrapRetractRelease_State(UI_FSM *me, Event const *event);

//-----------------------------------------------------------------------------
// CPM Use States
void UI_FSM_ConfirmCPMStartup_State(UI_FSM *me, Event const *event);
void UI_FSM_ContinuousPassiveMotion_State(UI_FSM *me, Event const *event);
void UI_FSM_ConfirmSpeedChange_State(UI_FSM *me, Event const *event);

#endif // End of multiple inclusion protection
       /* [] END OF FILE */