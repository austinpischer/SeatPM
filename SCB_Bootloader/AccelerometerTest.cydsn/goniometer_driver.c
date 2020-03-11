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
#include "project.h"
#include "goniometer_driver.h"
#include "adxl345_registers.h"
#include "austin_debug.h"
#include <math.h>
#include <stdio.h>

void Goniometer_Constructor(Goniometer *me)
{
    me->Angle = INVALID_ANGLE;
    ADXL345_Constructor(&(me->Accelerometer_A), DEFAULT_ADDRESS);
    ADXL345_Constructor(&(me->Accelerometer_B), ALTERNATE_ADDRESS); 
}

void Goniometer_CalculateAngle(Goniometer *me, AccelerationVector a, AccelerationVector b)
{    
    // printing doubles https://community.cypress.com/docs/DOC-9389
    char dbg[64];
    // Variables for intermediate steps
    double DotProduct, MagnitudeA, MagnitudeB;
        
    // Algorithm Starts HERE
    DotProduct = (a.x*b.x)+(a.y*b.y)+(a.z*b.z);       // Dot product is sum of products
    DotProduct = 0;
    sprintf(dbg, "Dot Product = %f\r\n", DotProduct);
    DEBUG_PRINT(dbg);
    
    MagnitudeA = sqrt((a.x*a.x)+(a.y*a.y)+(a.z*a.z)); // Magnitude is square root of sum of squares
    sprintf(dbg, "Magnitude of vector A = %f\r\n", MagnitudeA);
    DEBUG_PRINT(dbg);
    
    MagnitudeB = sqrt((b.x*b.x)+(b.y*b.y)+(b.z*b.z)); 
     sprintf(dbg, "Magnitude of vector B = %f\r\n", MagnitudeB);
    DEBUG_PRINT(dbg);
    
    me->Angle = acos(DotProduct/(MagnitudeA*MagnitudeB)); // Angle between two vectors
}
/* [] END OF FILE */
