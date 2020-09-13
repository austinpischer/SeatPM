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
 * This file contains the data members and function prototypes related to a
 * derived class of the finite state machine base class. This is the core
 * of the logical control flow of the SeatPM device. Therefore, this class
 * is only meant to have one (global) instance, located in the main.c file.
 *
 * Please see the finite_state_machine.h file for a high level explanation of
 * a finite state machine. Supplement with information with a google search.
 *
 * The possible states and their definitions can be found in the files
 * "user_interface_states.h" and "user_interface_states.c", respectively.
 *
 * Thus, the functions in this file are not states and rather are meant to
 * simplify and improve the readability of code in other parts of the project.
 *============================================================================*/

// Start of multiple inclusion protection
#ifndef USER_INTERFACE_FSM_H
#define USER_INTERFACE_FSM_H

//=============================================================================
// Inclusions
//=============================================================================
#include <stdio.h>  // For sprintf

#include "cpm_runtime.h"
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
    bool Is_First_Time_Setting_Min_Angle;
    bool Is_First_Time_Setting_Max_Angle;
    bool Has_User_Seen_Attach_Goniometer_Message;
    bool Shall_Main_Loop_Update_Angle_Reading;
    bool Has_User_Seen_Attach_Ankle_Strap_Message;
    bool Shall_Main_Loop_Handle_CPM_Message;

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

/* Function Name: UserInterface_Constructor
Requirements: - Address of the UserInterface instance
Results: Initializes all the data members of the Userinterface method.
*/
void UserInterface_Constructor(UserInterface *me);

/* Function Name: UserInterface_IsKneeAngle_Raw_Valid
Requirements: Address of the UserInterface instance
Results: Returns true if the KneeAngle_Raw member of the instance is within
         the min/max values of the KneeAngle parameter member of the instance.
*/
bool UserInterface_IsKneeAngle_Raw_Valid(UserInterface *me);

/* Function Name: UserInterface_DisplayCableReleasedPercent
Requirements: - Address of the UserInterface instance
Results: Displayed the percent of cable released on the user interface screen.
*/
void UserInterface_DisplayCableReleasedPercent(UserInterface *me);

/* Function Name: UserInterface_ExecuteCurrentStateFunction
Requirements: - Address of the UserInterface instance
Results: Instance's current state function is ran without the user pressing
         a button. This is usually used to indicate to the user that 
         the UI has transitioned states.
         This function allows each state's code to be more self-containting,
         and readable, as opposed to preemptively displaying messages related
         to another state.
*/
void UserInterface_ExecuteCurrentStateFunction(UserInterface *me);

/* Function Name: UserInterface_PrintInvalidSignalMessage
Requirements: - Address of the UserInterface instance
Results: Prints invalid signal message over debug.
*/
void UserInterface_PrintInvalidSignalMessage(UserInterface *me);


/* Function Name: UserInterface_ShallUpdateAngleReadingMessage
Requirements: - Address of the UserInterface instance
              - The value of the current knee angle
              - The value of the knee angle the last time this function
                was called (meant to be called in the infinite loop of main.c)
Results: Returns true if the angle reading message on the screen should be
         updated or displayed at all.
         Return false if the message should not be update or displayed.
*/
bool UserInterface_ShallUpdateAngleReadingMessage(UserInterface *me,
                                                  double KneeAngle,
                                                  double LastKneeAngle);

/* Function Name: UserInterface_UpdateAngleReadingMessage
Requirements: - Address of the UserInterface instance
              - The value of the knee angle to be displayed
              - Should only be called if
                UserInterface_ShallUpdateAngleReadingMessage()
                returns true
              - Intended to be ran repeatedly in the infinite loop of main()
Results: Prints a message to the user interface's screen displaying the
         current angle on one row while preserving the other row's message
*/
void UserInterface_UpdateAngleReadingMessage(UserInterface *me,
                                             double KneeAngle);

/* Function Name: UserInterface_ShallUpdateCPMRuntimeMessage
Requirements: - Address of the UserInterface instance
              - The value of the current knee angle
              - The value of the knee angle the last time this function
                was called (meant to be called in the infinite loop of main.c)
              - The value of the TotalSeconds of the instance's runtime member
                the last time this function was called (meant to be called in
                the infinite loop of main.c)
Results: Returns true if the CPM runtime message should be displayed on the
         user interface's screen, or updated. Also updates the current knee ang.
         Returns false if the CPM runtime message should not be displayed or
         updated.
*/
bool UserInterface_ShallUpdateCPMRuntimeMessage(UserInterface *me,
                                                double KneeAngle,
                                                double LastKneeAngle,
                                                long int LastTotalSeconds);

/* Function Name: UserInterface_UpdateCPMRuntimeMessage
Requirements: - Address of the UserInterface instance
              - The Knee Angle to be displayed
Results: Prints the total time spent in the current CPM session, as well as
         the current knee angle, to the screen.
*/
void UserInterface_UpdateCPMRuntimeMessage(UserInterface *me, double KneeAngle);

/* Function Name: UserInterface_EmergencyStop
Requirements: - Address of the UserInterface instance
Results: Stops the motor, prints emergency stop message, and halts all further
         execution. Note, in the future this code should shut off all power to
         the SeatPM device, but that functionality went out of scope during
         the COVID19 shutdown.
*/
void UserInterface_EmergencyStop(UserInterface *me);

/* Function Name: UserInterface_HandleEmergencyStopCondition
Requirements: - Address of the UserInterface instance
              - boolean true/false value representing the validity of the
               current knee angle
              - The current knee angle value
Results: If the knee angle is valid, then nothing happens.
         If the knee angle is not valid, then emergency stop is called,
         stopping the motor and halting all execution.
*/
void UserInterface_HandleEmergencyStopCondition(UserInterface *me,
                                                bool IsKneeAngleValid,
                                                double KneeAngle);
#endif  // End of multiple inclusion protection
        /* [] END OF FILE */