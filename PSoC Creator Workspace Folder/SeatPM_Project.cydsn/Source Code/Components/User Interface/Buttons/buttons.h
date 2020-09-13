/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: user_interface_buttons.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * This file protoypes all of the funtions that make the SeatPM's user
 * interface's buttons come to life. It also includes all the external global
 * variables from main.c and all the inclusions needed for the function
 * definitions in the associated file user_interface_buttons.c.
 *============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef USER_INTERFACE_BUTTONS_H
#define USER_INTERFACE_BUTTONS_H

//==============================================================================
// Inclusions
//==============================================================================
#include "project.h"
#include "debug.h"
#include "feature_branches.h"
#include "user_interface.h"
#include "buttons.h"
#include "parameter.h"
#include "emergency_stop.h"

//==============================================================================
// External Variables (defined in main.c)
//==============================================================================
extern UserInterface g_UserInterface;
//#ifdef DISPATCH_IN_MAIN
extern UserInterface_Signal g_SignalToDispatch;
//#endif

//==============================================================================
// Function Prototypes
//==============================================================================

/* Function Name: Buttons_Dispatch()
Requirements: - External Userinterface Instance named "g_UserInterface"
              - Signal to dispatch (see userinterface.h for enumeration)
Results: Signal is dispatched to the user interface instance, meaning
         that the current state function is executed with the
         button's conditional being meet
*/
void Buttons_Dispatch(const enum UserInterface_Signal ButtonSignal);

/* Function Name: Buttons_Setup()
Requirements: - Interrupt components in Topdesign.cysch named:
                - Button_Confirm_ISR
                - Button_Back_ISR
                - Button_Increment_ISR
                - Button_Decrement_ISR
                - Button_EmergencyStop_Left_Interrupt
                - Button_EmergencyStop_Right_Interrupt
Results: All button interrupts are enabled properly
*/
void Buttons_Setup();

//==============================================================================
// Interrupt Function Prototypes - User Interface Buttons
//==============================================================================

/* Function Name: Confirm Buttton Interrupt Service Routine
Requirements: - CyGlobalIntEnable must be run in main (not a function)
              - Buttons_Setup() must be run in main             
Results: - "Confirm button pressed" signal is dispatched to user interface
*/
CY_ISR_PROTO(Button_Confirm_ISR_Handler_Austin);

/* Function Name: Back Buttton Interrupt Service Routine
Requirements: - CyGlobalIntEnable must be run in main (not a function)
              - Buttons_Setup() must be run in main             
Results: - "Back button pressed" signal is dispatched to user interface
*/
CY_ISR_PROTO(Button_Back_ISR_Handler_Austin);

/* Function Name: Increment Buttton Interrupt Service Routine
Requirements: - CyGlobalIntEnable must be run in main (not a function)
              - Buttons_Setup() must be run in main             
Results: - "Increment button pressed" signal is dispatched to user interface
*/
CY_ISR_PROTO(Button_Increment_ISR_Handler_Austin);

/* Function Name: Decrement Buttton Interrupt Service Routine
Requirements: - CyGlobalIntEnable must be run in main (not a function)
              - Buttons_Setup() must be run in main             
Results: - "Decrement button pressed" signal is dispatched to user interface
*/
CY_ISR_PROTO(Button_Decrement_ISR_Handler_Austin);

//==============================================================================
// Interrupt Function Prototypes - Emergency Stop Buttons
//==============================================================================

/* Function Name: Left Emergency Buttton Interrupt Service Routine
Requirements: - CyGlobalIntEnable must be run in main (not a function)
              - Buttons_Setup() must be run in main             
Results: - Motor stops and all execution is stopped (infinite loop)
            Note: this functions should not exist and rather pressing the
            button should cut power to the device, but that functionality went
            out of scope during the COVID19 shutdown
*/
CY_ISR_PROTO(Button_EmergencyStop_Right_ISR_Handler);

/* Function Name: Left Emergency Buttton Interrupt Service Routine
Requirements: - CyGlobalIntEnable must be run in main (not a function)
              - Buttons_Setup() must be run in main             
Results: - Motor stops and all execution is stopped (infinite loop)
            Note: this functions should not exist and rather pressing the
            button should cut power to the device, but that functionality went
            out of scope during the COVID19 shutdown
*/
CY_ISR_PROTO(Button_EmergencyStop_Left_ISR_Handler);
    
#endif // Enf of multiple inclusion protection

/* [] END OF FILE */
