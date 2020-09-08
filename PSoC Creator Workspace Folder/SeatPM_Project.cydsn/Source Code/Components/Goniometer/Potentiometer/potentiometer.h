/*=============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: potentiometer.h
Author: Austin Pischer
File Description:
This file declares functions related to the hardware/psoc components that
sample the potentiometer. The potentiometer is knob that is meant to simulate
the angle of the user's knee, for demonstration purposes.
=============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

//==============================================================================
// Inclusions
//==============================================================================
#include "project.h" // For PSoC Components (adc)

//==============================================================================
// Function Declarations 
//==============================================================================

/* Function Name: Potentiometer_Setup
Requirements: - SAR ADC component in TopDesign.cysch named Potentiometer_ADC
Results: Analog to Digital converter that samples potentiometer is enabled
*/
void Potentiometer_Setup();

/* Function Name: Potentiometer_Sample
Requirements: 
Results: 
*/
double Potentiometer_Sample();

#endif // End of  Multiple Inclusion Protection

/* [] END OF FILE */
