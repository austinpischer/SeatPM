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
#ifndef GONIOMETER_DRIVER_H
#define GONIOMETER_DRIVER_H
    
#include "project.h"
#include "adxl345_driver.h"   
#include "acceleration_vector.h"
    
#define INVALID_ANGLE -999
    
typedef struct Goniometer Goniometer;
struct Goniometer 
{
    ADXL345 Accelerometer_A, Accelerometer_B;
    double CurrentAngle;
    double FilteredAngle;
};

void Goniometer_Constructor(Goniometer *me);
double CalculateAngle(AccelerationVector a, AccelerationVector b);
void Goniometer_CalculateFilteredAngle(Goniometer *me);
void Goniometer_CalculateCurrentAngle(Goniometer *me);
void Goniometer_Sample(Goniometer *me);
#endif
/* [] END OF FILE */
