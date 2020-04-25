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
char DebugString[64];
char CSV_String[64];

void printaccelerometerreadouts(AccelerationVector myvector);
//===============================Main Function=================================
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Screen_Start();
    PuTTY_Start();
    I2C_Start();
    
    /* Enable Button Interrupts */
    Button_Confirm_ISR_StartEx(Button_Confirm_ISR_Handler_Austin);
    Button_Back_ISR_StartEx(Button_Back_ISR_Handler_Austin);
    Button_Increment_ISR_StartEx(Button_Increment_ISR_Handler_Austin);
    Button_Decrement_ISR_StartEx(Button_Decrement_ISR_Handler_Austin);
    
    Goniometer KneeGoniometer; 
    Goniometer_Constructor(&KneeGoniometer);
    
    MovingAverageFilter Accelerometer_A_Filter, Accelerometer_B_Filter;
    MovingAverageFilter_Constructor(&Accelerometer_A_Filter);
    MovingAverageFilter_Constructor(&Accelerometer_B_Filter);
    
    
    int16 ax,ay,az,bx,by,bz;
    
      
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        /* Place your application code here. */
        
        /* Current Acceleromter A Measurement */ 
        ADXL345_UpdateFilteredAcceleration(&(KneeGoniometer.Accelerometer_A));
        ax = KneeGoniometer.Accelerometer_A.CurrentAcceleration.x;
        ay = KneeGoniometer.Accelerometer_A.CurrentAcceleration.x;
        az = KneeGoniometer.Accelerometer_A.CurrentAcceleration.x;
        sprintf(DebugString, "Current Acceleration:\tax = %d, ay = %d, az = %d\r\n", ax,ay,az);
        ACCELEROMETER_DEBUG(DebugString);
        sprintf(CSV_String, "%d,%d,%d\r\n",ax,ay,az);
        CSV_PRINT(CSV_String);
        
        /* Filtered Acceleromter A Measurement */ 
        ax = KneeGoniometer.Accelerometer_A.Filter.Average.x;
        ay = KneeGoniometer.Accelerometer_A.Filter.Average.y;
        az = KneeGoniometer.Accelerometer_A.Filter.Average.z;
        sprintf(DebugString, "Filtered Acceleration:\tax = %d, ay = %d, az = %d\r\n", ax,ay,az);
        ACCELEROMETER_DEBUG(DebugString);
        sprintf(CSV_String, "%d,%d,%d\r\n",ax,ay,az);
        CSV_PRINT(CSV_String);
        
        /* Current Acceleromter B Measurement */ 
        ADXL345_UpdateFilteredAcceleration(&(KneeGoniometer.Accelerometer_B));
        bx = KneeGoniometer.Accelerometer_B.CurrentAcceleration.x;
        by = KneeGoniometer.Accelerometer_B.CurrentAcceleration.y;
        bz = KneeGoniometer.Accelerometer_B.CurrentAcceleration.z;
        sprintf(DebugString, "Current Acceleration:\tbx = %d, by = %d, bz = %d\r\n", bx,by,bz);
        ACCELEROMETER_DEBUG(DebugString);
          sprintf(CSV_String, "%d,%d,%d\r\n",ax,ay,az);
        CSV_PRINT(CSV_String);
        
        /* Filtered Acceleromter B Measurement */ 
        bx = KneeGoniometer.Accelerometer_B.Filter.Average.x;
        by = KneeGoniometer.Accelerometer_B.Filter.Average.y;
        bz = KneeGoniometer.Accelerometer_B.Filter.Average.z;
        sprintf(DebugString, "Filtered Acceleration:\tbx = %d, by = %d, bz = %d\r\n", bx,by,bz);
        ACCELEROMETER_DEBUG(DebugString);
        sprintf(CSV_String, "%d,%d,%d\r\n",bx,by,bz);
        CSV_PRINT(CSV_String);
        
        /* Current Goniometer Angle */ 
        Goniometer_CalculateAngle(&KneeGoniometer,
                                  KneeGoniometer.Accelerometer_A.CurrentAcceleration,
                                  KneeGoniometer.Accelerometer_B.CurrentAcceleration);
        sprintf(DebugString, "Current Angle:\t%lf degrees\r\n", KneeGoniometer.Angle);
        GONIOMETER_DEBUG(DebugString);
        sprintf(CSV_String, "%lf\r\n", KneeGoniometer.Angle);
        CSV_PRINT(CSV_String);
        
        
        /* Filtered Goniometer Angle */ 
        Goniometer_CalculateAngle(&KneeGoniometer,  
                                  KneeGoniometer.Accelerometer_A.Filter.Average,
                                  KneeGoniometer.Accelerometer_B.Filter.Average);
        sprintf(DebugString, "Filtered Angle:\t%lf degrees\r\n", KneeGoniometer.FilteredAngle);
        GONIOMETER_DEBUG(DebugString);
        sprintf(CSV_String, "%lf\r\n", KneeGoniometer.FilteredAngle);
        CSV_PRINT(CSV_String);

        /* End of cycle */
        //DEBUG_PRINT("\r\n");    // print a new line
        Screen_ClearDisplay();
    }
}

/* [] END OF FILE */
