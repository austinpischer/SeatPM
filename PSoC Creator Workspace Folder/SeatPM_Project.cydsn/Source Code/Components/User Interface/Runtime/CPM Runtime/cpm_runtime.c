#include "cpm_runtime.h"

//=============================================================================
// CPM Runtime Second Counter Interrupt
//=============================================================================
CY_ISR(CPM_Runtime_Timer_Interrupt_Handle)
{
    g_CPM_Runtime.TotalSeconds++;
}

//=============================================================================
// CPM Runtime Setup
//============================================================================='
void CPM_Runtime_Setup()
{
    CPM_Runtime_Timer_Interrupt_ClearPending();
    CPM_Runtime_Timer_Interrupt_StartEx(CPM_Runtime_Timer_Interrupt_Handle);
}

//=============================================================================
// CPM Runtime Start Counting
//=============================================================================
void CPM_Runtime_StartCounting()
{
    CPM_Runtime_Timer_Start();
}

//=============================================================================
// CPM Runtime Stop Counting
//=============================================================================
void CPM_Runtime_StopCounting()
{
    CPM_Runtime_Timer_Stop();
}

