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
    // enabled "use newlib-nano Float formatting" under Project->Build Settings->Linker->General (set to true)
    // also increased heap size from 0x8 to 0x500 under Design Wide Resources->System->Heap Size(bytes) 
    
    // Variables for intermediate steps
    double DotProduct, MagnitudeA, MagnitudeB;
        
    // Algorithm Starts HERE
    DotProduct = (a.x*b.x)+(a.y*b.y)+(a.z*b.z);       // Dot product is sum of products
    MagnitudeA = sqrt((a.x*a.x)+(a.y*a.y)+(a.z*a.z)); // Magnitude is square root of sum of squares
    MagnitudeB = sqrt((b.x*b.x)+(b.y*b.y)+(b.z*b.z)); // Magnitude is square root of sum of squares
    me->FilteredAngle = 57.2958*acos(DotProduct/(MagnitudeA*MagnitudeB)); // Angle between two vectors, with radians->degrees approximation
}
/* [] END OF FILE */
