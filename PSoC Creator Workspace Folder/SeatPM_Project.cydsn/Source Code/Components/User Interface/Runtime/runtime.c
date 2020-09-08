/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: runtime.c
Author: Austin Pischer
File Description:
This file contains the implementations of the method members prototyped in
the associated header file "runtime.h"
=============================================================================*/

#include "runtime.h"

/* Function Name: Runtime_Constructor
Requirements: //todo
Results: 
*/
void Runtime_Constructor(Runtime *me)
{
    // CPM Runtime startup
    me->TotalSeconds = me->Hours = me->Minutes = me->Seconds = 0;
}

/* Function Name: Runtime_Update
Requirements: //todo
Results: 
*/
void Runtime_Update(Runtime *me)
{
    /* Get a copy of the current TotalSeconds so that it doesn't change
    due to an interrupt while executing this function */
    long int TotalSeconds_Copy = me->TotalSeconds;
    long int Remainder;

    const int seconds_in_a_minute = 60;
    const int minutes_in_an_hour = 60;

    /* Seconds to hms algorithm */
    me->Hours = (int)((TotalSeconds_Copy / seconds_in_a_minute) / minutes_in_an_hour);
    /* Calculate remaining seconds not accounted for in truncated "Hours" int*/
    Remainder =
        TotalSeconds_Copy - (me->Hours *
                             seconds_in_a_minute *
                             minutes_in_an_hour);
                             
    me->Minutes = (int)(Remainder / 60);
    Remainder = Remainder - (me->Minutes * 60);

    me->Seconds = (int)(Remainder);
}

/* Function Name: Runtime_Reset
Requirements: //todo
Results: 
*/
void Runtime_Reset(Runtime *me)
{
    me->TotalSeconds = 0;
    me->Hours = 0;
    me->Minutes = 0;
    me->Seconds = 0;
}

/* Function Name: Runtime_GetTotalSeconds
Requirements: Address of Runtime instance
Results: Returns value of TotalSeconds member of passed runtime instance
*/
long int Runtime_GetTotalSeconds(Runtime *me)
{
    return(me->TotalSeconds);
}
/* Function Name: Runtime_GetHours
Requirements: Address of Runtime instance
Results: Returns value of Hours member of passed runtime instance
*/
int Runtime_GetHours(Runtime *me)
{
    return(me->Hours);
}
/* Function Name: Runtime_GetMinutes
Requirements: Address of Runtime instance
Results: Returns value of Minutes member of passed runtime instance
*/
int Runtime_GetMinutes(Runtime *me)
{
    return(me->Minutes);
}
/* Function Name: Runtime_GetSeconds
Requirements: Address of Runtime instance
Results: Returns value of Seconds member of passed runtime instance
*/
int Runtime_GetSeconds(Runtime *me)
{
    return(me->Seconds);
}