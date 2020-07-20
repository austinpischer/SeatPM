/* 
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
*/

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "austin_debug.h"
#include "feature_branches.h"

#include "user_interface_fsm.h"
#include "user_interface_buttons.h"
#include "cpm_runtime.h"
#include "emergency_stop.h"

#include "austin_parameter.h" // for declaring global parameter instances

#ifdef ACCELEROMETER_GONIOMETER_ENABLED
    #include "goniometer_driver.h"
#endif

#include <stdio.h> // for printf


//=============================================================================
// Definitions
//=============================================================================
#define ABSOLUTE_MINIMUM_KNEE_ANGLE 90
#define ABSOLUTE_MAXIMUM_KNEE_ANGLE 180

//=============================================================================
// Global Variables
//=============================================================================
UI_FSM g_UserInterface; // UI must be accessed by button press interrupts

// Parameters
Parameter g_MinimumAngle, 
          g_MaximumAngle, 
          g_CurrentAngle, 
          g_CableReleasedPercent, 
          g_CPM_Speed;

#ifdef DISPATCH_IN_MAIN
// Flags for dispatching button-press signals to the user interface data struct
bool g_Dispatch_ConfirmButton, 
     g_Dispatch_BackButton, 
     g_Dispatch_IncrementButton, 
     g_Dispatch_DecrementButton;
#endif

#ifdef ACCELEROMETER_GONIOMETER_ENABLED
Goniometer g_KneeGoniometer;
#endif

Runtime g_CPM_Runtime;

//=============================================================================
// Function Prototypes
//=============================================================================
void InitializeParamters();
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
    InitializeParamters();
    UI_FSM_Constructor(&g_UserInterface);
    
    // Motor startup
    Motor_PWM_Start();
    Motor_PWM_WriteCompare(0); // Motor starts with 0 speed

    
    CPM_Runtime_Startup();

    #ifdef POTENTIOMETER_GONIOMETER_ENABLED
    //Potentiometer startup
    Potentiometer_ADC_Start();
    Potentiometer_ADC_StartConvert();
    #else // Accelerometer Goniometer Enabled
    Goniometer_Constructor(&g_KneeGoniometer);
    #endif
    //-------------------------------------------------------------------------
    // Global Variable Initialization
    //-------------------------------------------------------------------------
    #ifdef DISPATCH_IN_MAIN
    enum UI_FSM_Signals g_SignalToDispatch;
    #endif
  
    
    //-------------------------------------------------------------------------
    // Non-Global Variables
    //-------------------------------------------------------------------------
    double LastKneeAngle = INVALID_ANGLE;    
    // Runtime vars
    int RunTime_Hours, RunTime_Minutes, RunTime_Seconds;
    RunTime_Hours = RunTime_Minutes = RunTime_Seconds = 0;
    
    //-------------------------------------------------------------------------
    // Infinite Loop
    //-------------------------------------------------------------------------
    for(;;)
    {
        /* Update Parameters */
        // MaxValue of MinAngle should be Value of MaxAngle
        Parameter_SetMaximumValue(&g_MinimumAngle, Parameter_GetValue(&g_MaximumAngle));
        // MinValue of MaxAngle should be Value of MinAngle
        Parameter_SetMinimumValue(&g_MaximumAngle, Parameter_GetValue(&g_MinimumAngle));
        
        // Update Min and Max Value of the Current Angle
        Parameter_SetMinimumValue(&g_CurrentAngle, Parameter_GetValue(&g_MinimumAngle));
        Parameter_SetMaximumValue(&g_CurrentAngle, Parameter_GetValue(&g_MaximumAngle));
         
        // Sample the goniometer to get the knee angle
        bool IsCurrentKneeAngleValid = 
            Parameter_SetValue(&g_CurrentAngle, GetKneeAngle());
        
        /* IMMEDIATELY AFTER SAMPLING, Handle Emergency Stop Condition */
        if( IsCurrentKneeAngleValid == FALSE && 
            g_UserInterface.HasUserSeenAttachAnkleStrapMessage == TRUE)
        {
            EmergencyStop();
        }
        
        //=====================================================================
        // Tell UI which button was pressed 
        //=====================================================================
        #ifdef DISPATCH_IN_MAIN
        if(g_Dispatch_ConfirmButton == TRUE)
        {
            g_Dispatch_ConfirmButton = FALSE;
            UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
        }
        else if(g_Dispatch_BackButton == TRUE)
        {
            g_Dispatch_BackButton = FALSE;
            UI_Button_Dispatch(BACK_BUTTON_PRESSED);
        }
        else if(g_Dispatch_IncrementButton == TRUE)
        {
            g_Dispatch_IncrementButton = FALSE;
            UI_Button_Dispatch(INCREMENT_BUTTON_PRESSED);
        }
        else if(g_Dispatch_DecrementButton == TRUE)
        {
            g_Dispatch_DecrementButton = FALSE; 
            UI_Button_Dispatch(DECREMENT_BUTTON_PRESSED);
        }
        else
        {
            // No (valid) button press signal to dispatch to UI
        }
        #endif
       
        //=====================================================================
        // Update the display if the user interface has set flags to do so
        //=====================================================================

        double CurrenKneeAngle = Parameter_GetValue(g_CurrentAngle);

        /* Update the Angle Reading */
        if(g_UserInterface.ShallMainLoopUpdateAngleReading == TRUE
           && CurrentKneeAngle != LastKneeAngle)
        {
            sprintf(&g_UserInterface.Message[0][0],
                    "Current=%4.1lfdeg",
                    CurrentKneeAngle);
            
            Screen_Position(0,0); // Position invisible cursor to overwrite first line 
            Screen_PrintString(&g_UserInterface.Message[0][0]);
            
            LastKneeAngle = CurrentKneeAngle;
        }
        /* Update the CPM runtime */
        else if(g_UserInterface.ShallMainLoopHandleCPMMessage == TRUE)
        {            
            // Print message
            sprintf(&g_UserInterface.Message[0][0],
                    "RT: %2dh %2dm %2ds",
                    RunTime_Hours,
                    RunTime_Minutes,
                    RunTime_Seconds);
            sprintf(&g_UserInterface.Message[1][0],
                    "Angle = %4.1lfdeg",
                    CurrentKneeAngle);
            UI_FSM_PrintMessage(g_UserInterface.Message);
        }
        /* No diplay updates from UI */
        else
        {
            // Do nothing because there are no flags set to update display
        }
        
        CyDelay(10);// used for putty printing properly? not sure why though.
    } // End infinite loop
} // End main()

//=============================================================================
// Function Implementations
//=============================================================================
void InitializeParamters()
{
    
    // Handle button dispatches
        // The minimum angle can be between the absolute minmum and the maximum angle
    // Since maximum angle value isn't set yet, just use maximum possible angle
    double MinValue = ABSOLUTE_MINIMUM_KNEE_ANGLE;
    double MaxValue = ABSOLUTE_MAXIMUM_KNEE_ANGLE;
    double Value = ABSOLUTE_MINIMUM_KNEE_ANGLE;

    bool IsValidConstructor = 
        Parameter_Constructor(&g_MinimumAngle,
                              MinValue,
                              MaxValue,
                              Value);

    if(IsValidConstructor == FALSE)
    {
        // TODO: Should probably put more detailed error in the parameter code
        DEBUG_PRINT("Invalid Minimum Angle Constructor");
        // Knee angle settings are critical to user safety.
        // Shut off the device to prevent injuring the user.
        // TODO: Turn off device here.
    }
    // Otherwise, constructor called with valid min, max and value
    
    // The maximum angle can be between the absolute maximum and the minimum
    MinValue = Parameter_GetValue(&g_MinimumAngle);
    MaxValue = ABSOLUTE_MAXIMUM_KNEE_ANGLE;
    Value = ABSOLUTE_MAXIMUM_KNEE_ANGLE;

    IsValidConstructor =
     Parameter_Constructor(&g_MaximumAngle,
                            MinValue,
                            MaxValue,
                            Value);

    
    if(IsValidConstructor == FALSE)
    {
        // TODO: Should probably put more detailed error in the parameter code
        DEBUG_PRINT("Invalid Maximum Angle Constructor");
        // Knee angle settings are critical to user safety.
        // Shut off the device to prevent injuring the user.
        // TODO: Turn off device here.
    }
    // Otherwise, constructor called with valid min, max and value

    MinValue = Parameter_GetValue(&g_MinimumAngle);
    MaxValue = Parameter_GetValue(&g_MaximumAngle);
    Value = MinValue; // dummy value
    IsValidConstructor =
        Parameter_Constructor(&g_CurrentAngle,
                              MinValue,
                              MaxValue,
                              Value);
    if(IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid Current Angle Constructor");
    }
    
    // Cable released percent
    MinValue = 0; 
    MaxValue = 100;
    Value = 0;
    IsValidConstructor =
        Parameter_Constructor(&g_CableReleasedPercent,
                              MinValue,
                              MaxValue,
                              Value);

    //Speed
    MinValue = 0;
    MaxValue = 100;
    Value = 0;
    IsValidConstructor = 
        Parameter_Constructor(&g_CPM_Speed,
                              MinValue,
                              MaxValue,
                              Value);

    if(IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid CPM Speed Constructor");
    }
}

double GetKneeAngle()
{
    #ifdef POTENTIOMETER_GONIOMETER_ENABLED
    int16 Counts = Potentiometer_ADC_GetResult16(0);
    float32 Voltage = Potentiometer_ADC_CountsTo_Volts(0,Counts);
    double Percent = (double)((Voltage/5));
    return(90+(100*Percent));
    #else // Accelerometer Goniometer Enabled
    Goniometer_Sample(&g_KneeGoniometer);
    return(g_KneeGoniometer.CurrentAngle);
    #endif
}

double 
/* [] END OF FILE */
