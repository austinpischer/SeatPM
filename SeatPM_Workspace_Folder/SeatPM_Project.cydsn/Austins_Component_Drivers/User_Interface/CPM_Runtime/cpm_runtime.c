#include "cpm_runtime.h"

CY_ISR(CPM_Runtime_Timer_Interrupt_Handle)
{
    g_CPM_Runtime.TotalSeconds++;
}

void CPM_Runtime_Startup(Runtime *me)
{
    // CPM Runtime startup
    me->TotalSeconds = me->Hours = me->Minutes = me->Seconds = 0;

    // Start PSoC Timer component that triggers each second.
    CPM_Runtime_Timer_Interrupt_ClearPending();
    CPM_Runtime_Timer_Interrupt_StartEx(CPM_Runtime_Timer_Interrupt_Handle);
    CPM_Runtime_Timer_Start();
}

//=============================================================================
// Update CPM Runtime
//============================================================================
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
    /* Calculate remaining seconds not accounted for in truncated "Hours" int */
    Remainder =
        TotalSeconds_Copy - (me->Hours * seconds_in_a_minute * minutes_in_an_hour);
    me->Minutes = (int)(Remainder / 60);
    Remainder = Remainder - (me->Minutes * 60);
    me->Seconds = (int)(Remainder);
}