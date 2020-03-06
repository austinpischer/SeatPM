#ifndef ADXL345_B_DRIVER_H
#define ADXL345_B_DRIVER_H
#include "project.h"

typedef struct ADXL345_B ADXL345_B;
struct ADXL345_B
{
    Accelerometer Base;
    uint8 I2C_Address; 
    uint8 ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
    uint8 WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];
};

void ADXL345_B_Read(ADXL345_B *me, uint8 NumberOfBytesToRead);
void ADXL345_B_Write(ADXL345_B *me, uint8 NumberOfBytesToWrite);
#endif