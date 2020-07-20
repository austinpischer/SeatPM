/* 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: austin_debug.h
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
*/

#ifndef FEATURE_BRANCHES_H
#define FEATURE_BRANCHES_H

    
// TODO description
#define DISPATCH_IN_MAIN
#ifndef DISPATCH_IN_MAIN
    #define DISPATCH_IN_INTERRUPT
#endif


// TODO description
//#define POTENTIOMETER_GONIOMETER_ENABLED

#ifndef POTENTIOMETER_GONIOMETER_ENABLED
    #define ACCELEROMETER_GONIOMETER_ENABLED
#endif

// TODO  Loop vs interrupt goniometer sample

    
    
#endif

/* [] END OF FILE */
