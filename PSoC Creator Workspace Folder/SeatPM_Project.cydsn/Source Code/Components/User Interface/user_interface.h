/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 *
 * File Name: user_interface.h
 * Author: Austin Pischer
 *
 * File Explanation:
 // TODO
 * This file contains the data members and function prototypes related to a
 * derived class of the finite state machine base class.
 *
 *============================================================================*/

// Start of multiple inclusion protection
#ifndef USER_INTERFACE_FSM_H
#define USER_INTERFACE_FSM_H

//=============================================================================
// Inclusions
//=============================================================================
#include <stdio.h>  // For sprintf

#include "cpm_runtime.h"           // For start/stop counting functions
#include "debug.h"                 // For bool type and debug functions
#include "finite_state_machine.h"  // For base class
#include "goniometer.h"            // For invalid angle definition
#include "motor.h"                 // For manipulating speed and cable retract
#include "parameter.h"             // For paramter class
#include "project.h"               // For PSoC components
#include "runtime.h"               // For displaying runtime of CPM useage
#include "screen.h"                // For screen functions

//=============================================================================
// Definitions
//=============================================================================
#define CPM_START_SPEED_DEGREES_PER_MINUTE 30
#define ABSOLUTE_MAXIMUM_KNEE_ANGLE 180
#define ABSOLUTE_MINIMUM_KNEE_ANGLE 90

//=============================================================================
// Type definitions
//=============================================================================
// Define "struct <tag>" as type "<tag>"
typedef struct UserInterface UserInterface;
typedef struct UserInterface_Event UserInterface_Event;

//=============================================================================
// External Global Variables from main.c
//=============================================================================
extern Motor g_CPM_Motor;

//=============================================================================
// Event Struct -- User Interface Finite State Machine
//=============================================================================
struct UserInterface_Event
{
    Event Parent;  // Achieving inheritance by requiring base class
};

//=============================================================================
// Data Members -- UserInterface Class (Derived from FiniteStateMachine)
//=============================================================================
struct UserInterface
{
    // Achieving inheritance by requiring base class.
    FiniteStateMachine Parent;

    // Message to be displayed on screen
    // NOTE: +1 for c-string null terminator
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1];

    // Conditionals
    bool IsFirstTimeSettingMinAngle;
    bool IsFirstTimeSettingMaxAngle;
    bool HasUserSeenAttachGoniometerMessage;
    bool ShallMainLoopUpdateAngleReading;
    bool HasUserSeenAttachAnkleStrapMessage;
    bool ShallMainLoopHandleCPMMessage;

    // Parameters
    Parameter New_CPM_Speed;
    Parameter KneeAngle;
    double KneeAngle_Raw;
};

//=============================================================================
// Signals used by UserInterface Class
//=============================================================================
typedef enum UserInterface_Signal UserInterface_Signal;
enum UserInterface_Signal
{
    CONFIRM_BUTTON_PRESSED,
    BACK_BUTTON_PRESSED,
    INCREMENT_BUTTON_PRESSED,
    DECREMENT_BUTTON_PRESSED,
    NO_OPERATION,
    INVALID_SIGNAL
};

//=============================================================================
// Method Members -- User Interface Finite State Machine Class
//=============================================================================
void UserInterface_Constructor(UserInterface *me);
bool UserInterface_IsKneeAngle_Raw_Valid(UserInterface *me);
void UserInterface_DisplayCableReleasedPercent(UserInterface *me);
void UserInterface_ExecuteCurrentStateFunction(UserInterface *me);
void UserInterface_PrintInvalidSignalMessage(UserInterface *me);
void Handle_EmergencyStop(bool IsKneeAngleValid, double KneeAngle);
bool UserInterface_ShallUpdateAngleReadingMessage(UserInterface *me,
                                                  double KneeAngle,
                                                  double LastKneeAngle);
void UserInterface_UpdateAngleReadingMessage(UserInterface *me,
                                             double KneeAngle);
bool UserInterface_ShallUpdateCPMRuntimeMessage(UserInterface *me,
                                                double KneeAngle,
                                                double LastKneeAngle,
                                                double LastTotalSeconds);
void UserInterface_UpdateCPMRuntimeMessage(UserInterface *me,
                                           double CurrenKneeAngle);
#endif  // End of multiple inclusion protection
        /* [] END OF FILE */