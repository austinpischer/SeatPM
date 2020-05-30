// TODO: File header

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "austin_debug.h"
#include "goniometer_driver.h"


#ifndef GONIOMETER_TEST
#include "user_interface_fsm.h"
#include "user_interface_buttons.h"
#include "austin_parameter.h" // For Parameter Class
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
#ifndef GONIOMETER_TEST
UI_FSM g_UserInterface;
Parameter g_MinimumAngle, g_MaximumAngle, g_CPM_Speed, g_CableReleasedPercent;
#endif

char g_Debug[64];
double g_KneeAngle;

//=============================================================================
// Function Prototypes
//=============================================================================
#ifdef GONIOMETER_TEST
void PrintAcceleration(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered,
                       AccelerationVector CurrentAcceleration);
void PrintGoniometerAngle(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, 
                          double GoniometerAngle);
#endif

#ifndef GONIOMETER_TEST
void InitializeParamters();
#endif

CY_ISR_PROTO(Reset_Interrupt_Handle);
void Setup_Reset();

//=============================================================================
// Main Function
//=============================================================================
int main(void)
{
    CyDelay(1000);
    //-------------------------------------------------------------------------
    // Startup/Initialization Code
    //-------------------------------------------------------------------------
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //-------------------------------------------------------------------------
    // Hardware Startup
    //-------------------------------------------------------------------------
    #ifndef GONIOMETER_TEST
    Screen_Start();
    #endif
    
    // Debug startup 
    PuTTY_Start();
    Setup_Reset();
    
    // Goniometer startup
    //I2C_Start();
    
    // UI Startup
    #ifndef GONIOMETER_TEST
    Screen_Start();
    UI_FSM_Constructor(&g_UserInterface);
    Enable_UI_Button_Interrupts();
    #endif

    //-------------------------------------------------------------------------
    // Global Parameter Constructors
    //-------------------------------------------------------------------------
    #ifndef GONIOMETER_TEST
    InitializeParamters();
    #endif

    //-------------------------------------------------------------------------
    // User Interface Finite State Machine Startup
    //-------------------------------------------------------------------------
    
    //-------------------------------------------------------------------------
    // Non-Global Variables
    //-------------------------------------------------------------------------
    //Goniometer KneeGoniometer; 
    //GONIOMETER_DEBUG("Goniometer Constructor\n\r");
    //Goniometer_Constructor(&KneeGoniometer);
    
    #ifndef GONIOMETER_TEST
    double LastKneeAngle = INVALID_ANGLE; 
    int RunTime_Hours, RunTime_Minutes, RunTime_Seconds;
    RunTime_Hours = RunTime_Minutes = RunTime_Seconds = 0;
    #endif
    
    //-------------------------------------------------------------------------
    // Infinite Loop
    //-------------------------------------------------------------------------
    for(;;)
    {
        #ifndef GONIOMETER_TEST
        // User interface flags
        if(g_UserInterface.ShallMainLoopUpdateAngleReading == TRUE
           && g_KneeAngle != LastKneeAngle)
        {
            sprintf(&g_UserInterface.Message[0][0],
                    "Current %4.1lf deg",
                    g_KneeAngle);
            Screen_PrintString(&g_UserInterface.Message[0][0]);
            LastKneeAngle = g_KneeAngle;
        }
        // User interface flags
        else if(g_UserInterface.ShallMainLoopHandleCPMMessage == TRUE)
        {
            // TODO Implement time updates
            sprintf(&g_UserInterface.Message[0][0],
                    "RT: %2dh %2dm %2ds",
                    RunTime_Hours,
                    RunTime_Minutes,
                    RunTime_Seconds);
            sprintf(&g_UserInterface.Message[0][1],
                    "Angle = %4.1lfdeg",
                    g_KneeAngle);
            UI_FSM_PrintMessage(g_UserInterface.Message);
        }
        #endif
        
        #ifdef GONIOMETER_TEST
        GONIOMETER_DEBUG("Sampling Goniometer...\r\n");
        Goniometer_Sample(&KneeGoniometer);
         
        bool PrintCurrent = TRUE;
        bool PrintFiltered = FALSE;
        
        PrintAcceleration(PrintCurrent, KneeGoniometer.Accelerometer_A.Parent.CurrentAcceleration);
        PrintAcceleration(PrintCurrent, KneeGoniometer.Accelerometer_B.Parent.CurrentAcceleration);
        
        PrintAcceleration(PrintFiltered, KneeGoniometer.Accelerometer_A.Parent.FilteredAcceleration);
        PrintAcceleration(PrintFiltered, KneeGoniometer.Accelerometer_B.Parent.FilteredAcceleration);
        
        PrintGoniometerAngle(PrintCurrent, KneeGoniometer.CurrentAngle);
        PrintGoniometerAngle(PrintFiltered, KneeGoniometer.FilteredAngle);
        #endif 
        
        
        CyDelay(10);// used for putty printing properly?
    } // End infinite loop
    
} // End main()

//=============================================================================
// Serial Output Function Implementations
//=============================================================================
#ifdef GONIOMETER_TEST
void PrintAcceleration(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, AccelerationVector Acceleration)
{
    char DebugString[64];
    if(SetTrueToPrintCurrent_SetFalseToPrintFiltered == TRUE)
    {
        sprintf(DebugString, 
                "Current Acceleration:\tax = %d, ay = %d, az = %d\r\n", 
                Acceleration.x,
                Acceleration.y,
                Acceleration.z);
    }
    else if (SetTrueToPrintCurrent_SetFalseToPrintFiltered == FALSE)
    {
        sprintf(DebugString, 
                "Filtered Acceleration:\tax = %d, ay = %d, az = %d\r\n", 
                Acceleration.x,
                Acceleration.y,
                Acceleration.z);
    }
    else
    {
        sprintf(DebugString, 
                "Current/Filtered Acceleration Flag Set To Invalid Value: %d", 
                SetTrueToPrintCurrent_SetFalseToPrintFiltered);
        return; // Leave function early to avoid any following printouts
    }
    
    ACCELEROMETER_DEBUG(DebugString);
    
    sprintf(DebugString, 
            "%d,%d,%d\r\n",
            Acceleration.x,
            Acceleration.y,
            Acceleration.z);
    CSV_PRINT(DebugString);
}
#endif

void PrintGoniometerAngle(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, double GoniometerAngle)
{
    char DebugString[64];
    if(SetTrueToPrintCurrent_SetFalseToPrintFiltered == TRUE)
    {
        sprintf(DebugString, 
                "Current Goniometer Angle:\t%lf degrees\r\n",
                GoniometerAngle);
    }
    else if (SetTrueToPrintCurrent_SetFalseToPrintFiltered == FALSE)
    {
        sprintf(DebugString, 
                "Filtered Goniometer Angle:\t%lf degrees\r\n",
                GoniometerAngle);
    }
    else
    {
        sprintf(DebugString, 
                "Current/Filtered Goniometer Angle Flag Set To Invalid Value: %d", 
                SetTrueToPrintCurrent_SetFalseToPrintFiltered);
        return; // Leave function early to avoid any following printouts
    }
    
    ACCELEROMETER_DEBUG(DebugString);
    
    sprintf(DebugString, "%lf\r\n", GoniometerAngle);
    CSV_PRINT(DebugString);
}

//=============================================================================
// Initialization Function Implementations
//=============================================================================
#ifndef GONIOMETER_TEST
void InitializeParamters()
{
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

CY_ISR(Reset_Interrupt_Handle)
{
    Bootloadable_Load();
}

void Setup_Reset()
{
    Reset_Clock_Start();
    Reset_Timer_Start();
    Reset_Interrupt_ClearPending();
    Reset_Interrupt_StartEx(Reset_Interrupt_Handle);
}
/* [] END OF FILE */
