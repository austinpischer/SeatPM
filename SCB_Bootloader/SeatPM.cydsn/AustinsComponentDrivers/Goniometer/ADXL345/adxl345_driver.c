/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-02-18
 *
 * File Name: 
 *      adxl345_driver.c
 * File Description:
 *      This file contains the implementations for each method
 *      in the ADXL345 "class" (object-oriented C).
 *      Further information can be found in the  file "adxl345_driver.h"
 *      
 * ============================================================================
*/
#include "adxl345_driver.h"
#include "austin_debug.h"

void ADXL345_Constructor(ADXL345 *me)
{
    DEBUG_PRINT("ADXL345 constructor called...\r\n");
    ADXL345_InitializeConfigurationRegisters(me);
}

void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead)
{
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterReadBuf(me->I2C_Address,
                         &(me->ReadBuffer[0]), // pointer to start of buffer
                         NumberOfBytesToRead,
                         I2C_I2C_MODE_COMPLETE_XFER);
    
    //Wait until write is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
}

void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToWrite)
{

    I2C_I2CMasterClearStatus(); 
    I2C_I2CMasterWriteBuf(me->I2C_Address,
                          &(me->WriteBuffer[0]), // pointer to start of buffer
                          NumberOfBytesToWrite,
                          I2C_I2C_MODE_COMPLETE_XFER);
    // Wait until read is complete
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
}

void ADXL345_ReadDataRegisters(ADXL345 *me)
{
    // First, write first ADXL345 Register Number you want to read
    me->WriteBuffer[0] = DATAX0;
    ADXL345_Write(me, 1); // Write 1 byte

    // Then, read as many bytes of data as needed:
    // (address increments automatically, as data registers are subsequent)
    // DATAX0 through DATAZ1, 6 total bytes to read
    ADXL345_Read(me, 6);
}

void ADXL345_WriteConfigRegister(ADXL345 *me,
                                 const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite)
{
    me->WriteBuffer[0] = ConfigRegisterAddress;
    me->WriteBuffer[1] = ByteToWrite;
    ADXL345_Write(me, 2); // Write 2 bytes
}

void ADXL345_InitializeConfigurationRegisters(ADXL345 *me)
{
    DEBUG_PRINT("ADXL345 initializing configuration registers...\r\n");
    /* A setting of 0 in the measure bit places the part into standby mode,
     * and a setting of 1 places the part into measurement mode. The
     * ADXL345 powers up in standby mode with minimum power consumption.
     */
    const uint8 MeasurementMode = 0b00001000;
    ADXL345_WriteConfigRegister(me, POWER_CTL, MeasurementMode);
    DEBUG_PRINT("ADXL345 measurement mode register set...\r\n");
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
    uint8 DataRange = 0b00000011;
    ADXL345_WriteConfigRegister(me, DATA_FORMAT, DataRange);
    DEBUG_PRINT("ADXL345 data format register set.\r\n");
}

int16 ADXL345_CalculateComponentMagnitude(uint8 DataRegister0,
                                          uint8 DataRegister1)
{
    // "The output data is twos complement,
    //      with DATAx0 as the least significant byte
    //      and DATAx1 as the most significant byte,
    //      where x represent X, Y, or Z."
    // Thus, left shift upper byte and OR in the lower.
    return ((int16)((DataRegister1 << 8) | DataRegister0));
}


void ADXL345_CalculateCurrentAcceleration(ADXL345 *me)
{
    uint8 x0, x1, y0, y1, z0, z1;

    x0 = me->ReadBuffer[0];
    x1 = me->ReadBuffer[1];

    y0 = me->ReadBuffer[2];
    y1 = me->ReadBuffer[3];

    z0 = me->ReadBuffer[4];
    z1 = me->ReadBuffer[5];

    me->currentX = ADXL345_CalculateComponentMagnitude(x0, x1);
    me->currentY = ADXL345_CalculateComponentMagnitude(y0, y1);
    me->currentZ = ADXL345_CalculateComponentMagnitude(z0, z1);
}

/* [] END OF FILE */
