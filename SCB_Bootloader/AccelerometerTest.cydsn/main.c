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
#include <stdio.h>

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

#define DEFAULT_ADDRESS 0x1D
#define ALTERNATE_ADDRESS 0x53
#define TEST_ADDRESS DEFAULT_ADDRESS


/* Device ID Registers */
#define DEVID 0x00 // R, Device ID.

/* Tap Registers */ 
#define THRESH_TAP 0x1D // R/W, Tap threshold.
#define DUR 0x21 // R/W, Tap duration.
#define LATENT 0x22 // R/W, Tap latency.
#define WINDOW 0x23 // R/W, Tap window.
#define TAP_AXES 0x2A // R/W, Axis control for tap/double tap.
#define ACT_TAP_STATUS 0x2B // R, Source of tap/double tap.

/* Offset Registers */
#define OFSX 0x1E // R/W, X-axis offset.
#define OFSY 0x1F // R/W, Y-axis offset.
#define OFSZ 0x20 // R/W, Z-axis offset.

/* Activity Registers */
#define THRESH_ACT 0x24 // R/W, Activity threshold.
#define THRESH_INACT 0x25 // R/W, Inactivity threshold.
#define TIME_INACT 0x26 // R/W, Inactivity time.
#define ACT_INACT_CTL 0x27 // R/W, Axis enable control for activity and inactivity detection.

/* Free Fall Registers */
#define THRESH_FF 0x28 // R/W, Free-fall threshold.
#define TIME_FF 0x29 // R/W, Free-fall time.

/* Power Registers */ 
#define BW_RATE 0x2C // R/W, Data rate and power mode control.
#define POWER_CTL 0x2D // R/W, Power-saving features control.

/* Interrupt Registers */
#define INT_ENABLE 0x2E // R/W, Interrupt enable control.
#define INT_MAP 0x2F // R/W, Interrupt mapping control.
#define INT_SOURCE 0x30 // R, Source of interrupts.

/* Data Registers */ 
#define DATA_FORMAT 0x31 // R/W, Data format control.
#define DATAX0 0x32 // R, X-Axis Data 0.
#define DATAX1 0x33 // R, X-Axis Data 1.
#define DATAY0 0x34 // R, Y-Axis Data 0.
#define DATAY1 0x35 // R, Y-Axis Data 1.
#define DATAZ0 0x36 // R, Z-Axis Data 0.
#define DATAZ1 0x37 // R, Z-Axis Data 1.

/* FIFO Registers */
#define FIFO_CTL 0x38 // R/W, FIFO control.
#define FIFO_STATUS 0x39 // R, FIFO


//===================================DEBUG PRINT==========================================
// Comment out "#define AUSTIN_DEBUG" to disable debugging output"
// Uncomment "#define AUSTIN_DEBUG" to enable debugging output"  
#define AUSTIN_DEBUG

/* Pseudocode for debug print:
 * 1) If AUSTIN_DEBUG is defined...
 * 2) ...Set the DEBUG_PRINT() macro function to print to the LCD.
 * 3) If AUSTIN_DEBUG is NOT defined...
 * 4) ...Set the DEBUG_PRINT macro function to do nothing. 
 */
#ifdef AUSTIN_DEBUG // START of preprocessor if/else statement.
#define DEBUG_PRINT(string) (PuTTY_UartPutString(string))
#else 
#define DEBUG_PRINT(string) ()
#endif // END of preprocessor if/else statement.

//==============================Function Prototypes==================================
void ADXL345_Write(uint8 NumberOfBytesToWrite);
void ADXL345_Read(uint8 NumberOfBytesToRead);
void ADXL345_WriteConfigRegister(const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite);
void ADXL345_Initialize();
void ADXL345_ReadDataRegisters();
int16 convert(uint8 upper, uint8 lower);
void StartExecutionTimer();
uint32 StopExecutionTimer();

//===============================Global Variables=====================================
uint8 g_ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
uint8 g_WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];

int main(void)
{
    Screen_Start();
    PuTTY_Start();
    I2C_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADXL345_Initialize();
    char TestString[17];
    int16 x,y,z;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   //DEBUG_PRINT("Start\r\n");
    for(;;)
    {
        //DEBUG_PRINT("Test\r\n");
        /* Place your application code here. */
        ADXL345_ReadDataRegisters();
        x = convert(g_ReadBuffer[1], g_ReadBuffer[0]);
        y = convert(g_ReadBuffer[3], g_ReadBuffer[2]);
        z = convert(g_ReadBuffer[5], g_ReadBuffer[4]);
        sprintf(TestString, "x%3d y%3d z%3d\r\n", x,y,z);
        Screen_PrintString(TestString);
        DEBUG_PRINT(TestString);
        CyDelay(250);
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

void ADXL345_Write(uint8 NumberOfBytesToWrite)
{
    /*
    uint32 executiontime = 0;
    char executiontimestring[32];
    //TODO: DEBUG_WRITE_PRINT
    DEBUG_PRINT("Writing...\r\n");
    */
    StartExecutionTimer();
    I2C_I2CMasterClearStatus(); 
    I2C_I2CMasterWriteBuf(TEST_ADDRESS, // ======================= Point of interest
                          &(g_WriteBuffer[0]), // pointer to start of buffer
                          NumberOfBytesToWrite,
                          I2C_I2C_MODE_COMPLETE_XFER);
    // Wait until read is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    
    /*
    executiontime = StopExecutionTimer();
    DEBUG_PRINT("Write Complete.\r\n");
    sprintf(executiontimestring, "Execution time: %lu\r\n", executiontime);
    DEBUG_PRINT(executiontimestring);
    */
}

void ADXL345_Read(uint8 NumberOfBytesToRead)
{
    /*
    uint32 executiontime = 0;
    char executiontimestring[32];
    DEBUG_PRINT("Reading...\r\n");
    StartExecutionTimer();
    //TODO: DEBUG_READ_PRINT
    */
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterReadBuf(TEST_ADDRESS,  // ======================= Point of interest
                         &(g_ReadBuffer[0]), // pointer to start of buffer
                         NumberOfBytesToRead,
                         I2C_I2C_MODE_COMPLETE_XFER);
    
    //Wait until write is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
    /*
    executiontime = StopExecutionTimer();
    DEBUG_PRINT("Read Complete.\r\n");
    sprintf(executiontimestring, "Execution time: %lu\r\n", executiontime);
    DEBUG_PRINT(executiontimestring);
    */
}

void ADXL345_ReadDataRegisters()
{
    // First, write first ADXL345 Register Number you want to read
    g_WriteBuffer[0] = DATAX0;
    ADXL345_Write(1); // Write 1 byte
    
    // Then, read as many bytes of data as needed:
    // (address increments automatically, as data registers are subsequent)
    // DATAX0 through DATAZ1, 6 total bytes to read
    ADXL345_Read(6);
    // Accel data is now in ReadBuffer[0], … , ReadBuffer[5]
}

void ADXL345_WriteConfigRegister(const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite)
{
    g_WriteBuffer[0] = ConfigRegisterAddress;
    g_WriteBuffer[1] = ByteToWrite;
    ADXL345_Write(2); // Write 2 bytes
}

void ADXL345_Initialize()
{
    /* A setting of 0 in the measure bit places the part into standby mode,
     * and a setting of 1 places the part into measurement mode. The
     * ADXL345 powers up in standby mode with minimum power consumption.
     */
    const uint8 MeasurementMode = 0b00001000;
    ADXL345_WriteConfigRegister(POWER_CTL, MeasurementMode);
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
    ADXL345_WriteConfigRegister(DATA_FORMAT, DataRange);
}

void StartExecutionTimer()
{
    ExecutionTimer_WriteCounter(0);
    ExecutionTimer_Start();
}
uint32 StopExecutionTimer()
{
    ExecutionTimer_Stop();
    return(ExecutionTimer_ReadCounter());  
}
/* [] END OF FILE */
