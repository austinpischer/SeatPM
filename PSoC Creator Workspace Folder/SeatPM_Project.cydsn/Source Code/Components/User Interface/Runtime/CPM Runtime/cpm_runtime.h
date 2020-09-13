/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 09 2020

File Name: cpm_runtime.h
Author: Austin Pischer
File Description: This file contains the declarations/prototypes for a set of
functions related to counting the total number of seconds spent in continuous
passive motion. Doing so requires the global instance of the userinterface which
contains a runtime instance, which accessed during an interrupt.
==============================================================================*/
#include "user_interface.h"

//==============================================================================
// External Global Variables
//==============================================================================
typedef struct UserInterface
    UserInterface;  // since "user_interface.h" includes this file, we must
                    // "forward declare" this type becuause it is not yet
                    // defined when the compiler inserts it into the
                    // "user_interface.h" file
extern UserInterface
    g_UserInterface;  // declared in main, used in interrupt service routine

//==============================================================================
// Interrupt Service Routine Prototype
//==============================================================================
/* Function Name: Runtime Timer Interrupt
Requirements: - Interrupt Component in TopDesign.cysch named
                "CPM_Runtime_Timer_Interrupt"
Results: Increments value TotalSeconds member of CPM_Runtime member of
         g_UserInterface
*/
CY_ISR_PROTO(Runtime_Timer_Interrupt_Handle);

//==============================================================================
// Function Declarations (Prototypes)
//==============================================================================

/* Function Name: CPM_Runtime_Setup
Requirements: - Interrupt Component in TopDesign.cysch named
                "CPM_Runtime_Timer_Interrupt"
Results: Initializes the interrupt to be triggered by the Runtimer Timer
*/
void CPM_Runtime_Setup();

/* Function Name: CPM_Runtime_StartCounting
Requirements: - Timer Counter PWM (TCPWM) component in TopDesign.cysch
                configured as a Timer, named "CPM_Runtime_Timer"
Results: Runtime timers begins triggering the associated interrupt to increment
         TotalSeconds member of CPM_Runtime member of g_UserInterface every 1
         seconds
*/
void CPM_Runtime_StartCounting();

/* Function Name: CPM_Runtime_StopCounting
Requirements: - Timer Counter PWM (TCPWM) component in TopDesign.cysch
                configured as a Timer, named "CPM_Runtime_Timer"
Results: Runtime timer stops triggering the associated interrupt.
*/
void CPM_Runtime_StopCounting();

/* [] END OF FILE */