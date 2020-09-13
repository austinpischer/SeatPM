/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: debug.h
Author: Austin Pischer
File Description:
This header file is a collection of macros for switching back and forth 
between opposing feature branches of the project. 

For example, there could be a macro that changes the functionality of
an interrupt service routine 
from:
 - performing a function when the ISR is triggered
to:
 - setting a flag for the same function to be executed in main()

Thus, for each flag, there are (loosely) two implementations 
of the same """feature""".
==============================================================================*/

// Start multiple inclusion protection
#ifndef FEATURE_BRANCHES_H
#define FEATURE_BRANCHES_H

//==============================================================================
// Dispatch user interface signals in interrupts
// OR
// Use interrupts to set which signal to dispatch when
// the infinite loop in main gets around to it.
//==============================================================================
#define DISPATCH_IN_MAIN // Comment out this line to toggle dispatch in interr.
#ifndef DISPATCH_IN_MAIN
    #define DISPATCH_IN_INTERRUPT
#endif


//==============================================================================
// Due to COVID-19 we were not able to get our accelerometer-based
// goniometer (knee angle measurement device) to work, so we
// used a potentiometer to easily change the value of the "knee angle."
// Therefore,
// Enable potentiometer goniometer
// OR
// Enable accelerometer goniometer
//==============================================================================
#define POTENTIOMETER_GONIOMETER_ENABLED // Comment out this line to enable acc.
#ifndef POTENTIOMETER_GONIOMETER_ENABLED
    #define ACCELEROMETER_GONIOMETER_ENABLED
#endif

// End multiple inclusion protection
#endif
/* [] END OF FILE */