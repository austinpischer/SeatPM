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
#include "austin_parameter.h" // for declaring global parameter instances

#ifdef ACCELEROMETER_GONIOMETER_ENABLED
    #include "goniometer_driver.h"
#endif

#include <stdio.h>


//=============================================================================
// Definitions
//=============================================================================
#define ABSOLUTE_MINIMUM_KNEE_ANGLE 90
#define ABSOLUTE_MAXIMUM_KNEE_ANGLE 180

//=============================================================================
// Global Variables
//=============================================================================
UI_FSM g_UserInterface; // UI must be accessed by button press interrupts

Parameter g_MinimumAngle, 
          g_MaximumAngle, 
          g_CurrentAngle, 
          g_CableReleasedPercent, 
          g_CPM_Speed;

long long int g_CPM_Runtime_Seconds; // Updated by timer interrupt for use in user interface

char g_Debug[64];

double g_KneeAngle;

#ifdef FLAG_DISPATCH_ENABLED
bool g_Dispatch_ConfirmButton, 
     g_Dispatch_BackButton, 
     g_Dispatch_IncrementButton, 
     g_Dispatch_DecrementButton;
#endif

//=============================================================================
// Function Prototypes
//=============================================================================
void InitializeParamters();
CY_ISR_PROTO(CPM_Runtime_Timer_Interrupt_Handle);



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
    
    // CPM Runtime startup 
    g_CPM_Runtime_Seconds = 0;
    CPM_Runtime_Timer_Interrupt_ClearPending();
    CPM_Runtime_Timer_Interrupt_StartEx(CPM_Runtime_Timer_Interrupt_Handle);
    CPM_Runtime_Timer_Start();
    
    //Potentiometer startup
    Potentiometer_ADC_Start();
    Potentiometer_ADC_StartConvert();
    
    //-------------------------------------------------------------------------
    // Global Variable Initialization
    //-------------------------------------------------------------------------
    #ifdef FLAG_DISPATCH
    g_Dispatch_ConfirmButton = FALSE;
    g_Dispatch_BackButton = FALSE;
    g_Dispatch_IncrementButton = FALSE;
    g_Dispatch_DecrementButton = FALSE;
    #endif
  
    
    //-------------------------------------------------------------------------
    // Non-Global Variables
    //-------------------------------------------------------------------------
    double LastKneeAngle = INVALID_ANGLE;    
    // Runtime vars
    int RunTime_Hours, RunTime_Minutes, RunTime_Seconds;
    RunTime_Hours = RunTime_Minutes = RunTime_Seconds = 0;
    long long int Last_CPM_Runtime_InSeconds = 0;

    
    //-------------------------------------------------------------------------
    // Infinite Loop
    //-------------------------------------------------------------------------
    for(;;)
    {
        // Get angle reading
        #ifdef POTENTIOMETER_GONIOMETER
            int16 Counts = Potentiometer_ADC_GetResult16(0);
            float32 Voltage = Potentiometer_ADC_CountsTo_Volts(0,Counts);
            double Percent = (double)((Voltage/5));
            double Degrees = 90+(100*Percent);
        #else // Accelerometer Goniometer
            
         
        #endif
        
        
        Parameter_SetMinimumValue(&g_CurrentAngle, Parameter_GetValue(&g_MinimumAngle));
        Parameter_SetMaximumValue(&g_CurrentAngle, Parameter_GetValue(&g_MaximumAngle));
        bool IsCurrentKneeAngleValid = Parameter_SetValue(&g_CurrentAngle, Degrees);
        if( IsCurrentKneeAngleValid == FALSE && 
            g_UserInterface.HasUserSeenAttachAnkleStrapMessage == TRUE)
        {
            Motor_PWM_Stop(); // Stop motor
            sprintf(&g_UserInterface.Message[0][0], "    EMERGENCY   ");
            sprintf(&g_UserInterface.Message[1][0], "      STOP      ");
            UI_FSM_PrintMessage(g_UserInterface.Message);
            for(;;)
            {
                // Do nothing (aka stop device)
            };
        }
        g_KneeAngle = Parameter_GetValue(&g_CurrentAngle);
        
        #ifdef FLAG_DISPATCH
        if(g_Dispatch_ConfirmButton == TRUE)
        {
            g_Dispatch_ConfirmButton = FALSE;
            UI_Button_Dispatch(CONFIRM_BUTTON_PRESSED);
        }
        if(g_Dispatch_BackButton == TRUE)
        {
            g_Dispatch_BackButton = FALSE;
            UI_Button_Dispatch(BACK_BUTTON_PRESSED);
        }
        if(g_Dispatch_IncrementButton == TRUE)
        {
            g_Dispatch_IncrementButton = FALSE;
            UI_Button_Dispatch(INCREMENT_BUTTON_PRESSED);
        }
        if(g_Dispatch_DecrementButton == TRUE)
        {
            g_Dispatch_DecrementButton = FALSE; 
            UI_Button_Dispatch(DECREMENT_BUTTON_PRESSED);
        }
        #endif
       
        // User interface flags
        if(g_UserInterface.ShallMainLoopUpdateAngleReading == TRUE
           && g_KneeAngle != LastKneeAngle)
        {
            sprintf(&g_UserInterface.Message[0][0],
                    "Current=%4.1lfdeg",
                    g_KneeAngle);
            
            Screen_Position(0,0); // Position invisible cursor to overwrite first line 
            Screen_PrintString(&g_UserInterface.Message[0][0]);
            
            LastKneeAngle = g_KneeAngle;
        }
        // User interface flags
        else if(g_UserInterface.ShallMainLoopHandleCPMMessage == TRUE)
        {
            long long int TotalSeconds = g_CPM_Runtime_Seconds;
            if(TotalSeconds > Last_CPM_Runtime_InSeconds)
            {
                Last_CPM_Runtime_InSeconds = g_CPM_Runtime_Seconds;
                
                // Get copy of seconds so it doesnt change while calculating runttime
                
                // Seconds to hms algorithm
                RunTime_Hours = (int)(TotalSeconds/(60*60));
                long long int Remainder = TotalSeconds -(RunTime_Hours*60*60);
                RunTime_Minutes = (int)(Remainder/60);
                Remainder = Remainder - (RunTime_Minutes*60);
                RunTime_Seconds = (int)(Remainder);
            }
            
            // Print message
            sprintf(&g_UserInterface.Message[0][0],
                    "RT: %2dh %2dm %2ds",
                    RunTime_Hours,
                    RunTime_Minutes,
                    RunTime_Seconds);
            sprintf(&g_UserInterface.Message[1][0],
                    "Angle = %4.1lfdeg",
                    g_KneeAngle);
            UI_FSM_PrintMessage(g_UserInterface.Message);
        }

        
        // MaxValue of MinAngle should be Value of MaxAngle
        Parameter_SetMaximumValue(&g_MinimumAngle, Parameter_GetValue(&g_MaximumAngle));
        // MinValue of MaxAngle should be Value of MinAngle
        Parameter_SetMinimumValue(&g_MaximumAngle, Parameter_GetValue(&g_MinimumAngle));
        
        CyDelay(10);// used for putty printing properly?
    } // End infinite loop
    
} // End main()

//=============================================================================
// Function Implementations
//=============================================================================
#ifndef GONIOMETER_TEST
void InitializeParamters()
{
    
    // Handle button dispatches
        // The minimum angle can be between the absolute minmum and the maximum angle
    // Since maximum angle value isn't set yet, just use maximum possible angle
    double MinValue = ABSOLUTE_MINIMUM_KNEE_ANGLE;
    double MaxValue = ABSOLUTE_MAXIMUM_KNEE_ANGLE;
    double Value = ABSOLUTE_MINIMUM_KNEE_ANGLE;

    bool IsValidConstructor;
    IsValidConstructor = 
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
#endif

CY_ISR(CPM_Runtime_Timer_Interrupt_Handle)
{
    g_CPM_Runtime_Seconds++;
}
/* [] END OF FILE */
