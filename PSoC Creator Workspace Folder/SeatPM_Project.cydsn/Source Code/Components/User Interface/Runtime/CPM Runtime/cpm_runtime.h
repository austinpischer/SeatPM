#include "runtime.h"

// (Required to be defined in main, used in the interrupt functions)
extern Runtime g_CPM_Runtime;

CY_ISR_PROTO(Runtime_Timer_Interrupt_Handle);
void CPM_Runtime_Setup();
void CPM_Runtime_StartCounting();
void CPM_Runtime_StopCounting();
