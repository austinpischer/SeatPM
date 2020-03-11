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
#define GONIOMETER_DRIVER H
    
#include "project.h"
#include "adxl345_driver.h"   
#include "acceleration_vector.h"
    
#define INVALID_ANGLE -999
    
typedef struct Goniometer Goniometer;
struct Goniometer 
{
    ADXL345 Accelerometer_A, Accelerometer_B;
    double Angle;
};

void Goniometer_Constructor(Goniometer *me);
void Goniometer_CalculateAngle(Goniometer *me, AccelerationVector a, AccelerationVector b);
#endif
/* [] END OF FILE */
