/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: goniometer_driver.c
Author: Austin Pischer
File Description:
This file contains all of the function implementations for the method
members prototyped in the associated file header "goniometer.h"
=============================================================================*/

//==============================================================================
// Associated Header File
//==============================================================================
#include "goniometer.h"

//==============================================================================
// Inclusions
//==============================================================================
double CalculateAngle(AccelerationVector a, AccelerationVector b);
void Goniometer_CalculateFilteredAngle(Goniometer *me);
void Goniometer_CalculateCurrentAngle(Goniometer *me);


//==============================================================================
// Goniometer Setup(hardware)
//==============================================================================
void Goniometer_Setup()
{
    I2C_Start();
}

//==============================================================================
// Constructor
//==============================================================================
void Goniometer_Constructor(Goniometer *me)
{
    me->CurrentAngle = INVALID_ANGLE;
    me->FilteredAngle = INVALID_ANGLE;
    ACCELEROMETER_DEBUG("ADXL345 Constructor B\r\n");
    ADXL345_Constructor(&(me->Accelerometer_B), ALTERNATE_ADDRESS); 
    ACCELEROMETER_DEBUG("ADXL345 Constructor A\r\n");
    ADXL345_Constructor(&(me->Accelerometer_A), DEFAULT_ADDRESS);
}


//==============================================================================
// Calculate Angle (Helper Function)
//==============================================================================
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

//==============================================================================
// Calculate Filtered Angle
//==============================================================================
void Goniometer_CalculateFilteredAngle(Goniometer *me)
{
    me->FilteredAngle = 
        CalculateAngle(me->Accelerometer_A.Parent.FilteredAcceleration, me->Accelerometer_B.Parent.FilteredAcceleration);
}

//==============================================================================
// Calculate Curerent Angle
//==============================================================================
void Goniometer_CalculateCurrentAngle(Goniometer *me)
{
    me->CurrentAngle = 
        CalculateAngle(me->Accelerometer_A.Parent.CurrentAcceleration, me->Accelerometer_B.Parent.CurrentAcceleration);
}


//==============================================================================
// Sample
//==============================================================================
void Goniometer_Sample(Goniometer *me)
{
    Accelerometer_UpdateFilteredAcceleration(&(me->Accelerometer_A.Parent));
    Accelerometer_UpdateFilteredAcceleration(&(me->Accelerometer_B.Parent));
    Goniometer_CalculateFilteredAngle(me);
    Goniometer_CalculateCurrentAngle(me);
}

//==============================================================================
// Get Current Angle
//==============================================================================
double Goniometer_GetCurrentAngle(Goniometer *me)
{
    return(me->CurrentAngle);
}

//==============================================================================
// Get Filtered Angle
//==============================================================================
double Goniometer_GetFilteredAngle(Goniometer *me)
{
    return(me->FilteredAngle);
}
/* [] END OF FILE */
