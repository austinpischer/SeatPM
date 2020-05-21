// TODO: File header

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "adxl345_registers.h"
#include "austin_debug.h"
#include "adxl345_driver.h"
#include "goniometer_driver.h"
#include "moving_average_filter.h"
#include "user_interface_fsm.h"
#include "user_interface_buttons.h"
#include "austin_parameter.h" // For Parameter Class
#include <stdio.h>


//=============================================================================
// Definitions
//=============================================================================
#define ABSOLUTE_MINIMUM_KNEE_ANGLE 90
#define ABSOLUTE_MAXIMUM_KNEE_ANGLE 180

//=============================================================================
// Global Variables
//=============================================================================
UI_FSM g_UserInterface;
char g_Debug[64];
Parameter g_MinimumAngle, g_MaximumAngle, g_CPM_Speed, g_CableReleasedPercent;
double g_KneeAngle;

//=============================================================================
// Serial Output Function Prototypes
//=============================================================================
void PrintAcceleration(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered,
                       AccelerationVector CurrentAcceleration);
void PrintGoniometerAngle(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, 
                          double GoniometerAngle);

//=============================================================================
// Initialization Function Prototypes
//=============================================================================
void InitializeParamters();

//=============================================================================
// Main Function
//=============================================================================
int main(void)
{
    //-------------------------------------------------------------------------
    // Startup/Initialization Code
    //-------------------------------------------------------------------------
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //-------------------------------------------------------------------------
    // Hardware Startup
    //-------------------------------------------------------------------------
    Screen_Start();
    PuTTY_Start();
    I2C_Start();

    //-------------------------------------------------------------------------
    // Global Parameter Constructors
    //-------------------------------------------------------------------------
    InitializeParamters();

    //-------------------------------------------------------------------------
    // User Interface Finite State Machine Startup
    //-------------------------------------------------------------------------
    // Finite state machine should be constructed/initialized before button interrupts are enabled
    // such that we don't send button signals to a state that is null.
    UI_FSM_Constructor(&g_UserInterface);
    Enable_UI_Button_Interrupts();
    
    //-------------------------------------------------------------------------
    // Non-Global Variables
    //-------------------------------------------------------------------------
    Goniometer KneeGoniometer; 
    Goniometer_Constructor(&KneeGoniometer);   
    double LastKneeAngle = INVALID_ANGLE; 
      
    //-------------------------------------------------------------------------
    // Infinite Loop
    //-------------------------------------------------------------------------
    for(;;)
    {
        if(g_UserInterface.ShallMainLoopUpdateAngleReading == TRUE
           && g_KneeAngle != LastKneeAngle)
        {
            sprintf(&g_UserInterface.Message[0][0],
                    "Current %4.1lf deg",
                    g_KneeAngle);
            Screen_PrintString(&g_UserInterface.Message[0][0]);
            LastKneeAngle = g_KneeAngle;
        }
        /*
        Goniometer_Sample(&KneeGoniometer);
         
        bool PrintCurrent = TRUE;
        bool PrintFiltered = FALSE;
        
        PrintAcceleration(PrintCurrent, KneeGoniometer.Accelerometer_A.Parent.CurrentAcceleration);
        PrintAcceleration(PrintCurrent, KneeGoniometer.Accelerometer_B.Parent.CurrentAcceleration);
        
        PrintAcceleration(PrintFiltered, KneeGoniometer.Accelerometer_A.Parent.FilteredAcceleration);
        PrintAcceleration(PrintFiltered, KneeGoniometer.Accelerometer_B.Parent.FilteredAcceleration);
        
        PrintGoniometerAngle(PrintCurrent, KneeGoniometer.CurrentAngle);
        PrintGoniometerAngle(PrintFiltered, KneeGoniometer.FilteredAngle);
        */
        
        //DEBUG_PRINT("\r\n");    // print a new line
        //Screen_ClearDisplay();
    } // End infinite loop
    
} // End main()

//=============================================================================
// Serial Output Function Implementations
//=============================================================================
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

void InitializeParamters()
{
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


/* [] END OF FILE */
