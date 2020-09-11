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
#include "debug.h" // For bool type and debug functions
#include "finite_state_machine.h" // For base class
#include "goniometer.h" // For invalid angle definition
#include "motor.h"  // For manipulating speed and cable retract
#include "parameter.h" // For paramter class
#include "project.h" // For PSoC components
#include "runtime.h" // For displaying runtime of CPM useage
#include "screen.h" // For screen functions
#include "cpm_runtime.h"

//=============================================================================
// Definitions
//=============================================================================
#define CPM_START_SPEED_DEGREES_PER_MINUTE 30
#define ABSOLUTE_MAXIMUM_KNEE_ANGLE 180
#define ABSOLUTE_MINIMUM_KNEE_ANGLE 90

//=============================================================================
// Event Struct -- User Interface Finite State Machine
//=============================================================================
typedef struct UserInterface_Event UserInterface_Event;
struct UserInterface_Event
{
    Event Parent;  // Achieving inheritance by requiring base class
};

//=============================================================================
// Data Members -- UserInterface Class (Derived from FiniteStateMachine)
//=============================================================================
typedef struct UserInterface UserInterface;
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
    
    Motor CPM_Motor;
    Runtime CPM_Runtime;
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
//todo: all
/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_Constructor(UserInterface *me);

/* Function Name: 
Requirements: 
Results: 
*/
bool UserInterface_IsKneeAngle_Raw_Valid(UserInterface *me);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_DisplayCableReleasedPercent(UserInterface *me);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_ExecuteCurrentStateFunction(UserInterface *me);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_PrintInvalidSignalMessage(UserInterface *me);

/* Function Name: 
Requirements: 
Results: 
*/
void Handle_EmergencyStop(bool IsKneeAngleValid, double KneeAngle);

/* Function Name: 
Requirements: 
Results: 
*/
bool UserInterface_ShallUpdateAngleReadingMessage(UserInterface *me,
                                                  double KneeAngle,
                                                  double LastKneeAngle);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_UpdateAngleReadingMessage(UserInterface *me,
                                             double KneeAngle);

/* Function Name: 
Requirements: 
Results: 
*/
bool UserInterface_ShallUpdateCPMRuntimeMessage(UserInterface *me,
                                                double KneeAngle,
                                                double LastKneeAngle,
                                                long int LastTotalSeconds);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_UpdateCPMRuntimeMessage(UserInterface *me,
                                           double KneeAngle);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_EmergencyStop(UserInterface *me);

/* Function Name: 
Requirements: 
Results: 
*/
void UserInterface_HandleEmergencyStopCondition(UserInterface *me,
                                                bool IsKneeAngleValid,
                                                double KneeAngle);
#endif  // End of multiple inclusion protection
/* [] END OF FILE */