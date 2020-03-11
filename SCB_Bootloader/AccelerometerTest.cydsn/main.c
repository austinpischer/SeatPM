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
//====================================Includes and Defines=========================================
#include "project.h"
#include "adxl345_registers.h"
#include "austin_debug.h"
#include "adxl345_driver.h"
#include "goniometer_driver.h"
#include "moving_average_filter.h"
#include <stdio.h>

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

//===============================Global Variables=====================================
char DebugString[64];
//===============================Main Function=====================================
int main(void)
{
    Screen_Start();
    PuTTY_Start();
    I2C_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    
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
        ADXL345_UpdateCurrentAcceleration(&(KneeGoniometer.Accelerometer_A));
        ax = KneeGoniometer.Accelerometer_A.CurrentAcceleration.x;
        ay = KneeGoniometer.Accelerometer_A.CurrentAcceleration.y;
        az = KneeGoniometer.Accelerometer_A.CurrentAcceleration.z;
        
        sprintf(DebugString, "Current Data:ax%2d ay%2d az%2d", ax,ay,az);
        Screen_PrintString(DebugString);
        Screen_Position(1,0); 
        strcat(DebugString, "\r\n"); 
        DEBUG_PRINT(DebugString);
        
        MovingAverageFilter_UpdateAverage(&Accelerometer_A_Filter, KneeGoniometer.Accelerometer_A.CurrentAcceleration);
        sprintf(DebugString, "Filtered Data: ax%2d ay%2d az%2d\r\n", Accelerometer_A_Filter.Average.x, Accelerometer_A_Filter.Average.y, Accelerometer_A_Filter.Average.z);
        DEBUG_PRINT(DebugString);
        
        ADXL345_UpdateCurrentAcceleration(&(KneeGoniometer.Accelerometer_B));
        bx = KneeGoniometer.Accelerometer_B.CurrentAcceleration.x;
        by = KneeGoniometer.Accelerometer_B.CurrentAcceleration.y;
        bz = KneeGoniometer.Accelerometer_B.CurrentAcceleration.z;
        
        sprintf(DebugString, "Current Data: bx%2d by%2d bz%2d", bx,by,bz);
        Screen_PrintString(DebugString);
        Screen_Position(0,0);
        strcat(DebugString, "\r\n");
        DEBUG_PRINT(DebugString);
        
        MovingAverageFilter_UpdateAverage(&Accelerometer_B_Filter, KneeGoniometer.Accelerometer_B.CurrentAcceleration);
        sprintf(DebugString, "Filtered Data: bx%2d by%2d bz%2d\r\n", Accelerometer_B_Filter.Average.x, Accelerometer_B_Filter.Average.y, Accelerometer_B_Filter.Average.z);
        DEBUG_PRINT(DebugString);
        
        Goniometer_CalculateAngle(&KneeGoniometer, KneeGoniometer.Accelerometer_A.CurrentAcceleration, KneeGoniometer.Accelerometer_B.CurrentAcceleration);
        sprintf(DebugString, "Current Angle = %lf degrees\r\n", KneeGoniometer.Angle);
        DEBUG_PRINT(DebugString);
        
        Goniometer_CalculateAngle(&KneeGoniometer, Accelerometer_A_Filter.Average, Accelerometer_B_Filter.Average);
        sprintf(DebugString, "Filtered Angle = %lf degrees\r\n", KneeGoniometer.Angle);
        DEBUG_PRINT(DebugString);
        
        DEBUG_PRINT("\r\n");
        CyDelay(250);
        Screen_ClearDisplay();
    }
}
/* [] END OF FILE */
