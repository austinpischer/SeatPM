/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: cpm_runtime.c
Author: Austin Pischer
File Description:
This file contains the implementations of the method members prototyped in
the associated header file "cpm_runtime.h"
=============================================================================*/

#include "cpm_runtime.h"

//=============================================================================
// Runtime Second Counter Interrupt
//=============================================================================
CY_ISR(CPM_Runtime_Timer_Interrupt_Handle)
{
    g_CPM_Runtime.TotalSeconds++;
}

//=============================================================================
// Runtime Startup
//=============================================================================
void CPM_Runtime_Startup(Runtime *me)
{
    // CPM Runtime startup
    me->TotalSeconds = me->Hours = me->Minutes = me->Seconds = 0;

    // Start PSoC Timer component that triggers each second.
    CPM_Runtime_Timer_Interrupt_ClearPending();
    CPM_Runtime_Timer_Interrupt_StartEx(CPM_Runtime_Timer_Interrupt_Handle);
}

//=============================================================================
// Update Runtime
//=============================================================================
void CPM_Runtime_Update(Runtime *me)
{
    /* Get a copy of the current TotalSeconds so that it doesn't change
    due to an interrupt while executing this function */
    long long int TotalSeconds_Copy = me->TotalSeconds;
    long long int Remainder;

    const int seconds_in_a_minute = 60;
    const int minutes_in_an_hour = 60;

    /* Seconds to hms algorithm */
    me->Hours = (int)( 
        (TotalSeconds_Copy / seconds_in_a_minute) / minutes_in_an_hour);
    /* Calculate remaining seconds not accounted for in truncated "Hours" int*/
    Remainder =
        TotalSeconds_Copy - (me->Hours * 
                             seconds_in_a_minute * 
                             minutes_in_an_hour);
    me->Minutes = (int)(Remainder / 60);
    Remainder = Remainder - (me->Minutes * 60);
    me->Seconds = (int)(Remainder);
}

//=============================================================================
// Runtime Start Counting
//=============================================================================
void CPM_Runtime_StartCounting(Runtime *me)
{
    CPM_Runtime_Timer_Start();
}

//=============================================================================
// Runtime Stop Counting
//=============================================================================
void CPM_Runtime_StopCounting(Runtime *me)
{
    CPM_Runtime_Timer_Stop();
}

//=============================================================================
// Runtime Reset
//=============================================================================
void CPM_Runtime_Reset(Runtime *me)
{
    me->TotalSeconds = 0;
    CPM_Runtime_Update(me);
}