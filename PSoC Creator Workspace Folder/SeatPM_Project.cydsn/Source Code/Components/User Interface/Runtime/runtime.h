/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: runtime.h
Author: Austin Pischer
File Description:
This file contains the data and method members for the runtime data model.
The intent of this class is to make it easy to keep track of the time
spent in continuous passive motion in other parts of the code.
=============================================================================*/

// Multiple Inclusion Protections
#ifndef RUNTIME_H
#define RUNTIME_H
    
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
    long int TotalSeconds;
    int Hours;
    int Minutes;
    int Seconds;
};

//=============================================================================
// Method Member Prototypes
//=============================================================================

/* Function Name: Runtime_Constructor
   Requirements: Address of Runtime instance
   Results: Runtime instance has data members initialized
*/
void Runtime_Constructor(Runtime *me);

/* Function Name: Runtime_Update
   Requirements: Address of Runtime instance
   Results: The Hours, Minutes, and Seconds data members of the passed runtime
            instance are changed to reflect the value of the TotalSeconds member
*/
void Runtime_Update(Runtime *me);

/* Function Name: Runtime_Reset
   Requirements: Address of Runtime instance
   Results: Sets TotalSeconds, Hours, Minutes, and Seconds to 0
*/
void Runtime_Reset(Runtime *me);

/* Simple "get" functions */
long int Runtime_GetTotalSeconds(Runtime *me);
int Runtime_GetHours(Runtime *me);
int Runtime_GetMinutes(Runtime *me);
int Runtime_GetSeconds(Runtime *me);

#endif

/* [] END OF FILE */