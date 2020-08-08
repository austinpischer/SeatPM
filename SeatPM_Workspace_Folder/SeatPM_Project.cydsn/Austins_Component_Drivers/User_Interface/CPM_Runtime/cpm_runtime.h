
#ifndef CPM_RUNTIME_H
#define CPM_RUNTIME_H
    
#include "project.h"
    
typedef struct Runtime Runtime;
struct Runtime
{
    long long int TotalSeconds;
    int Hours;
    int Minutes;
    int Seconds;
};

// Global Variables (must be defined in main)
// Used in the interrupt function
extern Runtime g_CPM_Runtime;

// Interrupt Function Prototype
CY_ISR_PROTO(CPM_Runtime_Timer_Interrupt_Handle);

// Function Prototypes
void CPM_Runtime_Startup();
void CPM_Runtime_Update(Runtime *me);
#endif