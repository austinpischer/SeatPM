#ifndef ADXL345_A_DRIVER_H
#define ADXL345_A_DRIVER_H
#include "project.h"
#include "adxl345_driver.h"


typedef struct ADXL345_A ADXL345_A;
struct ADXL345_A
{
    ADXL345 Base;
};

void ADXL345_A_Read(ADXL345_A *me, uint8 NumberOfBytesToRead);
void ADXL345_A_Write(ADXL345_A *me, uint8 NumberOfBytesToWrite);
#endif