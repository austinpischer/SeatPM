/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: runtime.h
Author: Austin Pischer
File Description:
This file contains the data and method members for the runtime subcomponent.
The intent of this class is to make it easy to keep track of the time
spent in continuous passive motion in other parts of the code.
=============================================================================*/

// Multiple Inclusion Protections
#ifndef CPM_RUNTIME_H
#define CPM_RUNTIME_H
    
//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"

//=============================================================================
// Data Members
//=============================================================================
typedef struct Runtime Runtime;
struct Runtime
{
    long long int TotalSeconds;
    int Hours;
    int Minutes;
    int Seconds;
};

//=============================================================================
// External Global Variables
//=============================================================================
// (Required to be defined in main, used in the interrupt functions)
extern Runtime g_CPM_Runtime;

//=============================================================================
// Interrupt Function Prototype
//=============================================================================
CY_ISR_PROTO(CPM_Runtime_Timer_Interrupt_Handle);

//=============================================================================
// Method Member Prototypes
//=============================================================================

/* Function: Runtime Startup
   Description: Must be run before infinite loop in main()
*/
void CPM_Runtime_Startup(Runtime *me);

/* Function: Runtime Update
   Description: Updates the Hours/Minutes/Seconds of the passed Runtime
                to reflect its TotalSeconds value.
*/
void CPM_Runtime_Update(Runtime *me);

/* Function: Runtime Start Counting
   Description: Starts incrementing the TotalSeconds value
*/
void CPM_Runtime_StartCounting(Runtime *me);

/* Function: Runtime Stop Counting
   Description: Stops incrementing the TotalSeconds value
*/
void CPM_Runtime_StopCounting(Runtime *me);

/* Function: Runtime Reset
   Description: Sets the TotalSeconds value to zero
*/
void CPM_Runtime_Reset(Runtime *me);
#endif