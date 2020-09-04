/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: adxl345_driver.c
Author: Austin Pischer

File Explanation:
This file implements the functions declared in "adxl345.h"
==============================================================================*/

//==============================================================================
// Associated Header File Inclusion
//==============================================================================
#include "adxl345.h"

//==============================================================================
// Inclusions
//==============================================================================
#include "adxl345_registers.h"
#include "debug.h"

//==============================================================================
// Private Function Declarations
//==============================================================================
int16 ADXL345_ConvertDataToComponent(uint8 ComponentDataRegister1, 
                                     uint8 ComponentDataRegister0);
void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToWrite);
void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead);
void ADXL345_ReadDataRegisters(ADXL345 *me);
void ADXL345_WriteConfigRegister(ADXL345 *me,
                                 const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite);
void ADXL345_InitializeConfigRegisters(ADXL345 *me);
//==============================================================================
// Constructor
//==============================================================================
void ADXL345_Constructor(ADXL345 *me, uint8 My_I2C_Address)
{
    me->I2C_Address = My_I2C_Address;
    ACCELEROMETER_DEBUG("Initialize Config Registers\r\n");
    ADXL345_InitializeConfigRegisters(me);
    ACCELEROMETER_DEBUG("Accelerometer Constructor\r\n");
    Accelerometer_Constructor(&me->Parent, 
    (Accelerometer_VirtualFunctionPointer)(&ADXL345_UpdateCurrentAcceleration));
}

//==============================================================================
// Write
//==============================================================================
void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToWrite)
{
    ACCELEROMETER_DEBUG("I2CM Clear Status\r\n");
    I2C_I2CMasterClearStatus(); 
    ACCELEROMETER_DEBUG("I2CM Write Buffer\r\n");
    I2C_I2CMasterWriteBuf(me->I2C_Address, 
                          me->WriteBuffer,
                          NumberOfBytesToWrite,
                          I2C_I2C_MODE_COMPLETE_XFER);
    // Wait until write is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
}

//==============================================================================
// Read
//==============================================================================
void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead)
{
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterReadBuf(me->I2C_Address,
                         me->ReadBuffer,
                         NumberOfBytesToRead,
                         I2C_I2C_MODE_COMPLETE_XFER);
    //Wait until read is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
}

//==============================================================================
// Read Data Registers
//==============================================================================
void ADXL345_ReadDataRegisters(ADXL345 *me)
{
    // First, write first ADXL345 Register Number you want to read
    me->WriteBuffer[0] = DATAX0;
    ADXL345_Write(me, 1); // Write 1 byte
    
    // Then, read as many bytes of data as needed:
    // (address increments automatically, as data registers are subsequent)
    // DATAX0 through DATAZ1, 6 total bytes to read
    ADXL345_Read(me, 6);
    // Accel data is now in ReadBuffer[0], … , ReadBuffer[5]
}

//==============================================================================
// Write Configuration Register
//==============================================================================
void ADXL345_WriteConfigRegister(ADXL345 *me,
                                 const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite)
{
    me->WriteBuffer[0] = ConfigRegisterAddress;
    me->WriteBuffer[1] = ByteToWrite;
    ACCELEROMETER_DEBUG("Writing config reg...\r\n");
    ADXL345_Write(me, 2); // Write 2 bytes
}

//==============================================================================
// Initialize Configuration Registers
//==============================================================================
void ADXL345_InitializeConfigRegisters(ADXL345 *me)
{
    /* A setting of 0 in the measure bit places the part into standby mode,
     * and a setting of 1 places the part into measurement mode. The
     * ADXL345 powers up in standby mode with minimum power consumption.
     */
    ACCELEROMETER_DEBUG("Write Measurement Mode\r\n");
    const uint8 MeasurementMode = 0b00001000;
    ADXL345_WriteConfigRegister(me, POWER_CTL, MeasurementMode);
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
    ACCELEROMETER_DEBUG("Write Data Range\r\n");
    uint8 DataRange = 0b00000010;
    ADXL345_WriteConfigRegister(me, DATA_FORMAT, DataRange);
}

//==============================================================================
// Convert Data To Component
//==============================================================================
int16 ADXL345_ConvertDataToComponent(uint8 ComponentDataRegister1,
                                     uint8 ComponentDataRegister0)
{
    return((ComponentDataRegister1<<8)|ComponentDataRegister0);
}

//==============================================================================
// Update Current Acceleration (Virtual Function Implementation from base class)
//==============================================================================
void ADXL345_UpdateCurrentAcceleration(ADXL345 *me)
{
    ADXL345_ReadDataRegisters(me);
    me->Parent.CurrentAcceleration.x = 
        ADXL345_ConvertDataToComponent(me->ReadBuffer[1], me->ReadBuffer[0]);
    me->Parent.CurrentAcceleration.y = 
        ADXL345_ConvertDataToComponent(me->ReadBuffer[3], me->ReadBuffer[2]);
    me->Parent.CurrentAcceleration.z = 
        ADXL345_ConvertDataToComponent(me->ReadBuffer[5], me->ReadBuffer[4]);
}
/* [] END OF FILE */