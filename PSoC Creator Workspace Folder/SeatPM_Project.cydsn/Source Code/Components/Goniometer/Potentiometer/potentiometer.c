/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: potentiometer.c
Author: Austin Pischer
File Description: This file contains definitions (implementations) for the
functions declared (prototyped) in the associated header file, "potentiometer.h"
==============================================================================*/

//==============================================================================
// Associated Header File 
//==============================================================================
#include "potentiometer.h" // Associated header file

//==============================================================================
// Potentiometer Setup 
//==============================================================================
void Potentiometer_Setup()
{
    Potentiometer_ADC_Start();
}

//=============================================================================
// Potentiometer Sample
//=============================================================================
double Potentiometer_Sample()
{
    // Sample Potentiometer
    Potentiometer_ADC_StartConvert();
    Potentiometer_ADC_IsEndConversion(Potentiometer_ADC_WAIT_FOR_RESULT);
    double Input = (double)Potentiometer_ADC_GetResult16(0);

    // Define Normalization Constants
    const double MaxInput = 2047;  // 11 bits + signed bit
    const double MinInput = 0;
    const double MaxOutput = 180;  // max angle
    const double MinOutput = 90;   // min angle

    // Normalizing function (note: range means max-min)
    return (((Input - MinInput)          // Scale from Zero to Input Range
             / (MaxInput - MinInput)     // Scale from Zero to One
             * (MaxOutput - MinOutput))  // Scale from Zero to Output Range
            + MinOutput);  // Scale from Min to Max Output (normalized)
}

/* [] END OF FILE */
