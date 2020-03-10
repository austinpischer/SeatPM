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
#include <stdio.h>

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

//==============================Function Prototypes==================================
int16 convert(uint8 upper, uint8 lower);
void StartExecutionTimer();
uint32 StopExecutionTimer();

//===============================Global Variables=====================================

char DebugString[64];
int main(void)
{
    DEBUG_PRINT("Start\r\n");
    Screen_Start();
    PuTTY_Start();
    I2C_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    DEBUG_PRINT("\r\n");
    
    ADXL345 AccelerometerA, AccelerometerB;
    AccelerometerA.I2C_Address = DEFAULT_ADDRESS;
    AccelerometerB.I2C_Address = ALTERNATE_ADDRESS;
    ADXL345_InitializeConfigRegisters(&AccelerometerA);
    ADXL345_InitializeConfigRegisters(&AccelerometerB);
    int16 ax,ay,az,bx,by,bz;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   DEBUG_PRINT("Start\r\n");
    for(;;)
    {
        DEBUG_PRINT("Cycle\r\n");
        /* Place your application code here. */
        ADXL345_ReadDataRegisters(&AccelerometerA);
        ax = convert(AccelerometerA.ReadBuffer[1], AccelerometerA.ReadBuffer[0]);
        ay = convert(AccelerometerA.ReadBuffer[3], AccelerometerA.ReadBuffer[2]);
        az = convert(AccelerometerA.ReadBuffer[5], AccelerometerA.ReadBuffer[4]);
        
        sprintf(DebugString, "ax%2d ay%2d az%2d", ax,ay,az);
        Screen_PrintString(DebugString);
        Screen_Position(1,0); 
        strcat(DebugString, "\r\n"); 
        DEBUG_PRINT(DebugString);
        
        ADXL345_ReadDataRegisters(&AccelerometerB);
        bx = convert(AccelerometerB.ReadBuffer[1], AccelerometerB.ReadBuffer[0]);
        by = convert(AccelerometerB.ReadBuffer[3], AccelerometerB.ReadBuffer[2]);
        bz = convert(AccelerometerB.ReadBuffer[5], AccelerometerB.ReadBuffer[4]);
        
        sprintf(DebugString, "bx%2d by%2d bz%2d", bx,by,bz);
        Screen_PrintString(DebugString);
        Screen_Position(0,0);
        strcat(DebugString, "\r\n");
        DEBUG_PRINT(DebugString);
        
        CyDelay(500);
        Screen_ClearDisplay();
    }
}

int16 convert(uint8 upper, uint8 lower)
{
    int16 temp;
    temp = 0;
    temp = upper << 8;
    temp = temp | lower;
    return(temp);
}
/* [] END OF FILE */
