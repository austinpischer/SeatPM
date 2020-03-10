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
    DEBUG_PRINT("Goniometer constructor called\r\n");
    me->Angle = INVALID_ANGLE;
    ADXL345_Constructor(&(me->Accelerometer_A));
    ADXL345_Constructor(&(me->Accelerometer_B));
}

void Goniometer_CalculateAngle(Goniometer *me)
{    
    // Vector Components
    double ax, ay, az;
    double bx, by, bz;
    
    // Intermediate Steps
    double DotProduct;
    double MagnitudeA, MagnitudeB;
    
    // Getting Vector Components
    ax = (double) me->Accelerometer_A.currentX;
    ay = (double) me->Accelerometer_A.currentY;
    az = (double) me->Accelerometer_A.currentZ;
    
    bx = (double) me->Accelerometer_B.currentX;
    by = (double) me->Accelerometer_B.currentY;
    bz = (double) me->Accelerometer_B.currentZ;
    
    // Algorithm Starts HERE
    DotProduct = (ax*bx)+(ay*by)+(az*bz);       // Dot product is sum of products
    MagnitudeA = sqrt((ax*ax)+(ay*ay)+(az*az)); // Magnitude is square root of sum of squares
    MagnitudeB = sqrt((bx*bx)+(by*by)+(bz*bz)); 
    
    me->Angle = acos(DotProduct/(MagnitudeA*MagnitudeB)); // Angle between two vectors
}

/* [] END OF FILE */
