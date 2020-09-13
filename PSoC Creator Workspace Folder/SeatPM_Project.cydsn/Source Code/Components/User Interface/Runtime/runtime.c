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

//==============================================================================
// Constructor 
//==============================================================================
void Runtime_Constructor(Runtime *me)
{
    // CPM Runtime startup
    me->TotalSeconds = me->Hours = me->Minutes = me->Seconds = 0;
}

//==============================================================================
// Update 
//==============================================================================
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

//==============================================================================
// Reset 
//==============================================================================
void Runtime_Reset(Runtime *me)
{
    me->TotalSeconds = 0;
    me->Hours = 0;
    me->Minutes = 0;
    me->Seconds = 0;
}

//==============================================================================
// Get Total Seconds 
//==============================================================================
long int Runtime_GetTotalSeconds(Runtime *me)
{
    return(me->TotalSeconds);
}


//==============================================================================
// Get Hours  
//==============================================================================
int Runtime_GetHours(Runtime *me)
{
    return(me->Hours);
}

//==============================================================================
// Get Minutes 
//==============================================================================
int Runtime_GetMinutes(Runtime *me)
{
    return(me->Minutes);
}

//==============================================================================
// Get Seconds 
//==============================================================================
int Runtime_GetSeconds(Runtime *me)
{
    return(me->Seconds);
}