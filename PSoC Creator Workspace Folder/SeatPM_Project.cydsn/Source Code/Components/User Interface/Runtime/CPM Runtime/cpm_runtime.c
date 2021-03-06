/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: cpm_runtime.c
Author: Austin Pischer
File Description: This file contains the implementations/definitions for the
functions prototyped/declared in cpm_runtime.h. Please see that file for a
high level explanation of this set of functions.
==============================================================================*/

//==============================================================================
// Associated Header File 
//==============================================================================
#include "cpm_runtime.h"

//=============================================================================
// CPM Runtime Second Counter Interrupt
//=============================================================================
CY_ISR(CPM_Runtime_Timer_Interrupt_Handle)
{
    g_UserInterface.CPM_Runtime.TotalSeconds++;
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

/* [] END OF FILE */
