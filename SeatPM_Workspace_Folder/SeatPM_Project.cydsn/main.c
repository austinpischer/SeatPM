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
#include "project.h" // This is required for all code generated by PSoC Creator
// "Coding" inclusions
#include "austin_debug.h"       // Debug message toggles
#include "feature_branches.h"   // Switching between different opposing features
#include <stdio.h> // for printf
// Hardware inclusions
#include "emergency_stop.h"
#include "motor.h"
#include "user_interface_fsm.h"
#include "user_interface_buttons.h"
#ifdef ACCELEROMETER_GONIOMETER_ENABLED
    #include "goniometer_driver.h"
#endif
// "Data Model" inclusions
#include "cpm_runtime.h"
#include "austin_parameter.h" // for declaring global parameter instances

//=============================================================================
// Definitions
//=============================================================================
// Place definitions here

//=============================================================================
// Global Variables
//=============================================================================
#ifdef DISPATCH_IN_MAIN
UI_FSM_Signal g_SignalToDispatch; // Interrupts update this signal for main()
#endif
#ifdef ACCELEROMETER_GONIOMETER_ENABLED
Goniometer g_KneeGoniometer; // Goniometer can be sampled via interrupt
#endif
UI_FSM g_UserInterface; // UI must be accessed by button press interrupts
Runtime g_CPM_Runtime; // Interrupt updates seconds cout
Motor g_CPM_Motor;

//=============================================================================
// Function Prototypes
//=============================================================================
double GetKneeAngle(); 

//=============================================================================
// Main Function -- Firmware execution starts here!
//=============================================================================
int main(void)
{
    //-------------------------------------------------------------------------
    // Startup/Initialization Code
    //-------------------------------------------------------------------------
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // UI Startup
    Screen_Start();
    Enable_UI_Button_Interrupts(); // Testing UI transitioning unexpectedly, w/o buttons
    UI_FSM_Constructor(&g_UserInterface);    
    CPM_Runtime_Startup(&g_CPM_Runtime);
    #ifdef POTENTIOMETER_GONIOMETER_ENABLED
    //Potentiometer startup
    Potentiometer_ADC_Start();
    Potentiometer_ADC_StartConvert();
    #else // Accelerometer Goniometer Enabled
    Goniometer_Constructor(&g_KneeGoniometer);
    #endif
    PuTTY_Start();
    Motor_Startup(&g_CPM_Motor);
    
    //-------------------------------------------------------------------------
    // Global Variable Initialization
    //-------------------------------------------------------------------------
    #ifdef DISPATCH_IN_MAIN
    g_SignalToDispatch = INVALID_SIGNAL;
    #endif
  
    
    //-------------------------------------------------------------------------
    // Non-Global Variables
    //-------------------------------------------------------------------------
    double LastKneeAngle = INVALID_ANGLE;    
    double LastTotalSeconds = 0;
    
    //=========================================================================
    // Infinite Loop
    //=========================================================================
    for(;;)
    {       
        //---------------------------------------------------------------------
        // Sample the goniometer to get the knee angle
        //---------------------------------------------------------------------
        bool IsCurrentKneeAngleValid = 
            Parameter_SetValue(&g_UserInterface.KneeAngle, GetKneeAngle());
        
        //---------------------------------------------------------------------
        // Handle emergency stop condition
        // Should always occur immediately after sampling the goniometer.
        //---------------------------------------------------------------------
        if(IsCurrentKneeAngleValid == FALSE && 
           g_UserInterface.HasUserSeenAttachAnkleStrapMessage == TRUE)
        {
            EmergencyStop();
        }
        
        //---------------------------------------------------------------------
        // Tell UI which button was pressed 
        //---------------------------------------------------------------------
        #ifdef DISPATCH_IN_MAIN
        switch(g_SignalToDispatch)
        {
            case(CONFIRM_BUTTON_PRESSED):
                UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
                break;
                
            case(BACK_BUTTON_PRESSED):
                UI_Button_Dispatch(BACK_BUTTON_PRESSED);
                break;
                
            case(INCREMENT_BUTTON_PRESSED):
                UI_Button_Dispatch(INCREMENT_BUTTON_PRESSED);
                break;
                
            case(DECREMENT_BUTTON_PRESSED):
                UI_Button_Dispatch(DECREMENT_BUTTON_PRESSED);
                break;
                
            default:
                DEBUG_PRINT("Invalid signal being dispatched to UI!\r\n");
                break;
        }
        g_SignalToDispatch = INVALID_SIGNAL;
        #endif
       
        //---------------------------------------------------------------------
        // Update the display if the user interface has set flags to do so
        //---------------------------------------------------------------------
        
        // Getting a copy of the current knee angle to improve code readability
        double CurrentKneeAngle = Parameter_GetValue(&g_UserInterface.KneeAngle);

        //....................................................................
        // Update the Angle Reading
        if(g_UserInterface.ShallMainLoopUpdateAngleReading == TRUE
           && CurrentKneeAngle != LastKneeAngle)
        {
            sprintf(&g_UserInterface.Message[0][0],
                    "Current=%4.1lfdeg",
                    GetKneeAngle());
            
            // Position the invisible cursor to overwrite first line 
            Screen_Position(0,0);
            Screen_PrintString(&g_UserInterface.Message[0][0]);
            
            LastKneeAngle = CurrentKneeAngle;
        }
        //....................................................................
        // Update the CPM runtime
        else if(g_UserInterface.ShallMainLoopHandleCPMMessage == TRUE
                && CurrentKneeAngle != LastKneeAngle
                && g_CPM_Runtime.TotalSeconds != LastTotalSeconds)
        {      
            // Print message
            sprintf(&g_UserInterface.Message[0][0],
                    "RT: %2dh %2dm %2ds",
                    g_CPM_Runtime.Hours,
                    g_CPM_Runtime.Minutes,
                    g_CPM_Runtime.Seconds);
            sprintf(&g_UserInterface.Message[1][0],
                    "Angle = %4.1lfdeg",
                    CurrentKneeAngle);
            UI_FSM_PrintMessage(g_UserInterface.Message);
        }
        //....................................................................
        // No diplay updates from UI
        else
        {
            // Do nothing because there are no flags set to update display
        }
        
        CyDelay(10);// used for putty printing properly? not sure why though.
    } // End infinite loop
} // End main()

double GetKneeAngle()
{
    #ifdef POTENTIOMETER_GONIOMETER_ENABLED
    
    // Sample Potentiometer
    Potentiometer_ADC_StartConvert();
    Potentiometer_ADC_IsEndConversion(Potentiometer_ADC_WAIT_FOR_RESULT);
    double Input = (double)Potentiometer_ADC_GetResult16(0);
   
    // Define Normalization Cons    tants
    const double MaxInput = 2047; // 11 bits + signed bit 
    const double MinInput = 0; 
    const double MaxOutput = 180; // max angle
    const double MinOutput = 90; // min angle

    // Normalizing function (note: range means max-min)
    return(((Input-MinInput) // Scale from Zero to Input Range
            /(MaxInput-MinInput) // Scale from Zero to One
            *(MaxOutput-MinOutput)) // Scale from Zero to Output Range
            + MinOutput); // Scale from Min to Max Output (normalized)
    #else // Accelerometer Goniometer Enabled
    Goniometer_Sample(&g_KneeGoniometer);
    return(g_KneeGoniometer.CurrentAngle);
    #endif
}

/* [] END OF FILE */
