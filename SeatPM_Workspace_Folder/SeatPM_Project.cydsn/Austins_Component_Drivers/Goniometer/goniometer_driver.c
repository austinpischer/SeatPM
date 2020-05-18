// TODO: File header
#include "project.h"
#include "goniometer_driver.h"
#include "adxl345_registers.h"
#include "austin_debug.h"
#include <math.h>
#include <stdio.h>

void Goniometer_Constructor(Goniometer *me)
{
    me->CurrentAngle = INVALID_ANGLE;
    me->FilteredAngle = INVALID_ANGLE;
    ADXL345_Constructor(&(me->Accelerometer_A), DEFAULT_ADDRESS);
    ADXL345_Constructor(&(me->Accelerometer_B), ALTERNATE_ADDRESS); 
}

// Helper Function
double CalculateAngle(AccelerationVector a, AccelerationVector b)
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
    return( 57.2958*acos(DotProduct/(MagnitudeA*MagnitudeB)) ); // Angle between two vectors, with radians->degrees approximation
}

void Goniometer_CalculateFilteredAngle(Goniometer *me)
{
    me->FilteredAngle = 
        CalculateAngle(me->Accelerometer_A.Parent.FilteredAcceleration, me->Accelerometer_B.Parent.FilteredAcceleration);
}

void Goniometer_CalculateCurrentAngle(Goniometer *me)
{
    me->CurrentAngle = 
        CalculateAngle(me->Accelerometer_A.Parent.CurrentAcceleration, me->Accelerometer_B.Parent.CurrentAcceleration);
}

void Goniometer_Sample(Goniometer *me)
{
    Accelerometer_UpdateFilteredAcceleration(&(me->Accelerometer_A.Parent));
    Accelerometer_UpdateFilteredAcceleration(&(me->Accelerometer_B.Parent));
    Goniometer_CalculateFilteredAngle(me);
    Goniometer_CalculateCurrentAngle(me);
}
/* [] END OF FILE */
