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
#include "math.h"           // For calculating knee angle
    
#define UNDEFINED_ANGLE 0;

typedef struct Goniometer Goniometer;
struct Goniometer
{
    char* Name; 
    ADXL345 Accelerometer_A;
    ADXL345 Accelerometer_B;
    double CurrentAngle;
};

void Goniometer_Intitialize(Goniometer *me);
void Goniometer_CalculateKneeAngle(Goniometer *me);

#endif    
    
/* [] END OF FILE */
