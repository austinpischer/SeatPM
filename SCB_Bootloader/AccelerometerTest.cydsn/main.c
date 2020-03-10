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
#include <stdio.h>

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

//==============================Function Prototypes==================================
void ADXL345_Write(uint8 NumberOfBytesToWrite, uint8 I2C_Address, uint8 *WriteBuffer);
void ADXL345_Read(uint8 NumberOfBytesToRead, uint8 I2C_Address, uint8 *ReadBuffer);
void ADXL345_ReadDataRegisters(uint8 *WriteBuffer,uint8 *ReadBuffer, uint8 I2C_Address);
void ADXL345_WriteConfigRegister(const uint8 ConfigRegisterAddress, uint8 ByteToWrite, uint8 I2C_Address, uint8 *WriteBuffer);
void ADXL345_Initialize();
int16 convert(uint8 upper, uint8 lower);
void StartExecutionTimer();
uint32 StopExecutionTimer();

//===============================Global Variables=====================================
uint8 g_A_ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
uint8 g_A_WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];
uint8 g_B_ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
uint8 g_B_WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];
char DebugString[64];
int main(void)
{
    DEBUG_PRINT("Start\r\n");
    Screen_Start();
    PuTTY_Start();
    I2C_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    DEBUG_PRINT("\r\n");
    ADXL345_Initialize();
    int16 ax,ay,az,bx,by,bz;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   DEBUG_PRINT("Start\r\n");
    for(;;)
    {
        DEBUG_PRINT("Cycle\r\n");
        /* Place your application code here. */
        ADXL345_ReadDataRegisters(g_A_WriteBuffer, g_A_ReadBuffer, DEFAULT_ADDRESS);
        ax = convert(g_A_ReadBuffer[1], g_A_ReadBuffer[0]);
        ay = convert(g_A_ReadBuffer[3], g_A_ReadBuffer[2]);
        az = convert(g_A_ReadBuffer[5], g_A_ReadBuffer[4]);
        
        sprintf(DebugString, "ax%2d ay%2d az%2d", ax,ay,az);
        Screen_PrintString(DebugString);
        Screen_Position(1,0); 
        strcat(DebugString, "\r\n"); 
        DEBUG_PRINT(DebugString);
        
        ADXL345_ReadDataRegisters(g_B_WriteBuffer, g_B_ReadBuffer, ALTERNATE_ADDRESS);
        bx = convert(g_B_ReadBuffer[1], g_B_ReadBuffer[0]);
        by = convert(g_B_ReadBuffer[3], g_B_ReadBuffer[2]);
        bz = convert(g_B_ReadBuffer[5], g_B_ReadBuffer[4]);
        
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

void ADXL345_Write(uint8 NumberOfBytesToWrite, uint8 I2C_Address, uint8 *WriteBuffer)
{
    DEBUG_PRINT(DebugString);
    
    I2C_I2CMasterClearStatus(); 
    I2C_I2CMasterWriteBuf(I2C_Address, 
                          WriteBuffer,
                          NumberOfBytesToWrite,
                          I2C_I2C_MODE_COMPLETE_XFER);
    // Wait until read is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    DEBUG_PRINT(DebugString);
}

void ADXL345_Read(uint8 NumberOfBytesToRead, uint8 I2C_Address, uint8 *ReadBuffer)
{
    DEBUG_PRINT(DebugString);
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterReadBuf(I2C_Address,
                         ReadBuffer,
                         NumberOfBytesToRead,
                         I2C_I2C_MODE_COMPLETE_XFER);
    //Wait until write is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
}

void ADXL345_ReadDataRegisters(uint8 *WriteBuffer,uint8 *ReadBuffer, uint8 I2C_Address)
{
    // First, write first ADXL345 Register Number you want to read
    WriteBuffer[0] = DATAX0;
    ADXL345_Write(1, I2C_Address, WriteBuffer); // Write 1 byte
    
    // Then, read as many bytes of data as needed:
    // (address increments automatically, as data registers are subsequent)
    // DATAX0 through DATAZ1, 6 total bytes to read
    ADXL345_Read(6, I2C_Address, ReadBuffer);
    // Accel data is now in ReadBuffer[0], … , ReadBuffer[5]
}

void ADXL345_WriteConfigRegister(const uint8 ConfigRegisterAddress, uint8 ByteToWrite, uint8 I2C_Address, uint8 *WriteBuffer)
{
    WriteBuffer[0] = ConfigRegisterAddress;
    WriteBuffer[1] = ByteToWrite;
    ADXL345_Write(2, I2C_Address, WriteBuffer); // Write 2 bytes
}

void ADXL345_Initialize()
{
    /* A setting of 0 in the measure bit places the part into standby mode,
     * and a setting of 1 places the part into measurement mode. The
     * ADXL345 powers up in standby mode with minimum power consumption.
     */
    const uint8 MeasurementMode = 0b00001000;
    ADXL345_WriteConfigRegister(POWER_CTL, MeasurementMode, DEFAULT_ADDRESS, g_A_WriteBuffer);
    ADXL345_WriteConfigRegister(POWER_CTL, MeasurementMode, ALTERNATE_ADDRESS, g_B_WriteBuffer);
    /*  
     *  Setting
     *  D1  D0  g Range
     *  0   0   +- 2g
     *  0   1   +- 4g
     *  1   0   +- 8g
     *  1   1   +- 16g 
     * 
     * Defines the range of measurement
     * In 2g mode,
     *  +511 means 2g,
     *  -511 means -2g
     * In 16g mode,
     *  +511 means 16g,
     *  -511 means -16g
     * 
     * In 2g mode, 1g = 255
     * In 4g mode, 1g = 217
     * In 8g mode, 1g = 63
     * In 16g mode, 1g = 31
     * 
     * We get the least noise on every axis in 16g mode, so lets use that.
     * 
     */
    uint8 DataRange = 0b00000010;
    ADXL345_WriteConfigRegister(DATA_FORMAT, DataRange, DEFAULT_ADDRESS, g_A_WriteBuffer);
    ADXL345_WriteConfigRegister(DATA_FORMAT, DataRange, ALTERNATE_ADDRESS, g_B_WriteBuffer);
}
/* [] END OF FILE */
