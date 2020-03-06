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
 *      goniometer_driver.c
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

#include "goniometer_driver.h"

void Goniometer_Constructor(Goniometer *me)
{
    me->CurrentAngle = INVALID_ANGLE;
    ADXL345_Constructor(&(me->Accelerometer_A));
    ADXL345_Constructor(&(me->Accelerometer_B));
}

void Goniometer_CalculateCurrentAngle(Goniometer *me)
{    
    // Vector Components
    double ax, ay, az;
    double bx, by, bz;
    
    // Intermediate Steps
    double dotProduct;
    double aMagnitude, bMagnitude;
    
    // Getting Vector Components
    ax = (double) me->Accelerometer_A.Base.CurrentAcceleration.x;
    ay = (double) me->Accelerometer_A.Base.CurrentAcceleration.y;
    az = (double) me->Accelerometer_A.Base.CurrentAcceleration.z;
    
    bx = (double) me->Accelerometer_B.Base.CurrentAcceleration.x;
    by = (double) me->Accelerometer_B.Base.CurrentAcceleration.y;
    bz = (double) me->Accelerometer_B.Base.CurrentAcceleration.z;
    
    // Algorithm Starts HERE
    dotProduct = (ax*bx)+(ay*by)+(az*bz);
    aMagnitude = sqrt((ax*ax)+(ay*ay)+(az*az));
    bMagnitude = sqrt((bx*bx)+(by*by)+(bz*bz));
    
    me->CurrentAngle = acos(dotProduct/(aMagnitude*bMagnitude));
}

void Goniometer_CalculateCurrentAngle(Goniometer *me)
{    
    // Vector Components
    double ax, ay, az;
    double bx, by, bz;
    
    // Intermediate Steps
    double dotProduct;
    double aMagnitude, bMagnitude;
    
    // Getting Vector Components
    ax = (double) me->Accelerometer_A.Base.FilteredAcceleration.x;
    ay = (double) me->Accelerometer_A.Base.FilteredAcceleration.y;
    az = (double) me->Accelerometer_A.Base.FilteredAcceleration.z;
    
    bx = (double) me->Accelerometer_B.Base.FilteredAcceleration.x;
    by = (double) me->Accelerometer_B.Base.FilteredAcceleration.y;
    bz = (double) me->Accelerometer_B.Base.FilteredAcceleration.z;
    
    // Algorithm Starts HERE
    dotProduct = (ax*bx)+(ay*by)+(az*bz);
    aMagnitude = sqrt((ax*ax)+(ay*ay)+(az*az));
    bMagnitude = sqrt((bx*bx)+(by*by)+(bz*bz));
    
    me->CurrentAngle = acos(dotProduct/(aMagnitude*bMagnitude));
}

/* [] END OF FILE */
