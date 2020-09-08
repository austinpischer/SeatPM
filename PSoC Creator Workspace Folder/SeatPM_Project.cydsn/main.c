/*=============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: main.c
Author: Austin Pischer
File Description:
The main() function is where the program always starts executuion.
In addition, all of the global variables in this program should be
declared before the main function.
Also if something is really specific to the SeatPM then it should
probably belong here. For example, "Knee Angle" as opposed to "Angle"
=============================================================================*/

//=============================================================================
// Inclusions
//=============================================================================
/* Inclusions for "coding" */
#include <stdio.h>             // for printf
#include "debug.h"             // For debug macros
#include "feature_branches.h"  // For macros for opposing features
#include "project.h"           // For PSoC components (TopDesign.cysch)

/* Inclusions for main SeatPM components */
#include "buttons.h"         // For UI button components
#include "cpm_runtime.h"     // For CPM runtime components
#include "parameter.h"       // For Parameter functions
#include "potentiometer.h"   // For potentiometer functions
#include "runtime.h"         // For runtime class
#include "user_interface.h"  // For UI class

#ifdef ACCELEROMETER_GONIOMETER_ENABLED
#include "goniometer.h"
#else
#include "potentiometer.h"
#endif

//=============================================================================
// Global Variables
//=============================================================================
UserInterface g_UserInterface;  // Methods accessed by button interrupts

#ifdef DISPATCH_IN_MAIN
UserInterface_Signal g_SignalToDispatch;  // Updated by button press interrupt
#endif

#ifdef ACCELEROMETER_GONIOMETER_ENABLED
Goniometer g_KneeGoniometer;  // Goniometer can be sampled via interrupt
#endif

//=============================================================================
// Main Function -- Firmware execution starts here!
//=============================================================================
int main(void)
{
    //==========================================================================
    // Startup/Initialization Code
    //==========================================================================
    CyGlobalIntEnable; /* Enable global interrupts. */

    //-------------------------------------------------------------------------
    // Component/"Hardware" Setup (always run before constructors)

    /* Major SeatPM Functionality 1: User Interface */
    Screen_Setup();
    Buttons_Setup();
    CPM_Runtime_Setup();

    /* Major SeatPM Functionality 2: Goniometer */
    #ifdef ACCELEROMETER_GONIOMETER_ENABLED
    Goniometer_Setup();
    #else
    Potentiometer_Setup();
    #endif
    
    /* Major SeatPM Functionality 3: Motor */
    MotorHardware_Setup();

    /* Non-essential Functionality: Debug Setup */
    PuTTY_Start();

    //-------------------------------------------------------------------------
    // Global Variable Initialization (constructor functions and whatnot)

    UserInterface_Constructor(&g_UserInterface);

    #ifdef DISPATCH_IN_MAIN
    g_SignalToDispatch = INVALID_SIGNAL;
    #endif

    #ifdef ACCELEROMETER_GONIOMETER
    Goniometer_Constructor(&g_KneeGoniometer);
    #endif

    //-------------------------------------------------------------------------
    // Non-Global Variables
    double LastKneeAngle = INVALID_ANGLE;
    long int LastTotalSeconds = 0;

    //=========================================================================
    // Infinite Loop
    //=========================================================================
    for (;;)
    {
        /* Sample the Goniometer*/
        double KneeAngle;  // Intended to greatly improve readabiltiy of code
        #ifdef ACCELEROMETER_GONIOMETER
        KneeAngle = Goniometer_Sample(&g_KneeGoniometer);
        #else
        KneeAngle = Potentiometer_Sample();
        #endif

        // Update Raw Knee Angle (required for early states of the UI)
        g_UserInterface.KneeAngle_Raw = KneeAngle;

        // Update Knee Angle Parameter (required for later statges of UI)
        bool IsKneeAngleValid =
            Parameter_SetValue(&g_UserInterface.KneeAngle, KneeAngle);

        /* For user safety, always check emeregency stop immediately after
           sampling the goniometer. */
        UserInterface_HandleEmergencyStopCondition(&g_UserInterface,
                                                   IsKneeAngleValid, KneeAngle);

        /* Tell UI that a button was pressed (if flag is set to do so) */
        #ifdef DISPATCH_IN_MAIN
        Buttons_Dispatch(g_SignalToDispatch);
        g_SignalToDispatch = INVALID_SIGNAL;  // Reset signal
        #endif

        /* Update User Interface Display */
        if (UserInterface_ShallUpdateAngleReadingMessage(
                &g_UserInterface, KneeAngle, LastKneeAngle))
        {
            UserInterface_UpdateAngleReadingMessage(&g_UserInterface,
                                                    KneeAngle);
            LastKneeAngle = KneeAngle;
        }
        else if(UserInterface_ShallUpdateCPMRuntimeMessage( 
            &g_UserInterface, KneeAngle, LastKneeAngle, LastTotalSeconds))
        {
            UserInterface_UpdateCPMRuntimeMessage(&g_UserInterface, KneeAngle);
            LastKneeAngle = KneeAngle;
            LastTotalSeconds = 
                Runtime_GetTotalSeconds(&g_UserInterface.CPM_Runtime);
        }
        #ifdef AUSTIN_DEBUG
        CyDelay(10);  // Necessary for debug output over serial to print
        #endif
    }  // End infinite loop
}  // End main()
/* [] END OF FILE */
