// TODO: File header

//-----------------------------------------------------------------------------
// Inclusions
#include "project.h"
#include "adxl345_registers.h"
#include "austin_debug.h"
#include "adxl345_driver.h"
#include "goniometer_driver.h"
#include "moving_average_filter.h"
#include "user_interface_fsm.h"
#include "user_interface_buttons.h"
#include <stdio.h>


//=============================================================================
// Inclusions
//=============================================================================
UserInterface_FSM g_UI_FSM;
char g_Debug[64];

//=============================================================================
// Serial Output Function Prototypes
//=============================================================================
void PrintAcceleration(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, AccelerationVector CurrentAcceleration);
void PrintGoniometerAngle(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, double GoniometerAngle);

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
    // User Interface Finite State Machine Startup
    //-------------------------------------------------------------------------
    // Finite state machine should be constructed/initialized before button interrupts are enabled
    // such that we don't send button signals to a state that is null.
    UserInterface_FSM_Constructor(&g_UI_FSM);
    Enable_UI_Button_Interrupts();
    
    //-------------------------------------------------------------------------
    // Non-Global Variables
    //-------------------------------------------------------------------------
    Goniometer KneeGoniometer; 
    Goniometer_Constructor(&KneeGoniometer);    
      
    //-------------------------------------------------------------------------
    // Infinite Loop
    //-------------------------------------------------------------------------
    for(;;)
    {
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


/* [] END OF FILE */
