/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-01-31
 *
 * File Name: 
 *      goniometer_driver.h
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

/* Multiple inclusion protection. See: austin_debug.h */
#ifndef GONIOMETER_DRIVER_H
#define GONIOMETER_DRIVER_H

#include "project.h"        // For type definitions, etc.
#include "adxl345_driver.h" // Our Goniometer *is composed of* 2 ADXL345 accelerometers
#include <math.h>           // For calculating knee angle
#include "austin_debug.h"

#define INVALID_ANGLE 0



//========================= Goniometer Structure =================================
// Define the type "struct <tag>" as type "<tag>"
typedef struct Goniometer Goniometer;
struct Goniometer
{
    ADXL345 Accelerometer_A;
    ADXL345 Accelerometer_B;
    double Angle;
};

//========================= Goniometer Method Prototypes =================================
void Goniometer_Constructor(Goniometer *me);
void Goniometer_CalculateAngle(Goniometer *me,
                               AccelerationVector VectorA,
                               AccelerationVector VectorB);
#endif

/* [] END OF FILE */
