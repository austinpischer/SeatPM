#include "user_interface.h"

typedef struct UserInterface UserInterface;  // since "user_interface.h" includes this file, we must "forward declare" this type becuause it is not yet defined when the compiler inserts it into the "user_interface.h" file
extern UserInterface g_UserInterface; // declared in main, used in interrupt service routine

CY_ISR_PROTO(Runtime_Timer_Interrupt_Handle);
void CPM_Runtime_Setup();
void CPM_Runtime_StartCounting();
void CPM_Runtime_StopCounting();
