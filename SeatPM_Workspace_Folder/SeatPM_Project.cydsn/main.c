/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//====================================Includes and Defines=====================
#include "project.h"
#include "adxl345_registers.h"
#include "austin_debug.h"
#include "adxl345_driver.h"
#include "goniometer_driver.h"
#include "moving_average_filter.h"
#include "user_interface_fsm.h"
#include "user_interface_buttons.h"
#include <stdio.h>

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

//===============================Global Variables==============================
UserInterface_FSM g_UI_FSM;
char g_Debug[64];

//============================= Helper Function Prototypes ====================
void PrintAcceleration(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, AccelerationVector CurrentAcceleration);
void PrintGoniometerAngle(bool SetTrueToPrintCurrent_SetFalseToPrintFiltered, double GoniometerAngle);

//===============================Main Function=================================
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Screen_Start();
    PuTTY_Start();
    I2C_Start();
    
    // Finite state machine should be constructed/initialized before button interrupts are enabled
    // such that we don't send button signals to a state that is null.
    UserInterface_FSM_Constructor(&g_UI_FSM);
    Enable_UI_Button_Interrupts();
    
    /* Declare variables */
    Goniometer KneeGoniometer; 
    Goniometer_Constructor(&KneeGoniometer);    
      
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        /* Place your application code here. */
        
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
    }
}

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
