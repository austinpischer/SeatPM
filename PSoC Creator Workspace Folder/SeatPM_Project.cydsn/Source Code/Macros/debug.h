/*=============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: debug.h
Author: Austin Pischer
File Description:
This header file is a collection of macros for enabling and disabling
certain parts of the code for debugging purposes.
=============================================================================*/

// Start of multiple inclusion protection
#ifndef AUSTIN_DEBUG_H
#define AUSTIN_DEBUG_H

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"

//=============================================================================
// Boolean Type
//=============================================================================
typedef int bool;
#define TRUE 1
#define FALSE 0

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Comment out "#define AUSTIN_DEBUG" to disable debugging output"
Uncomment "#define AUSTIN_DEBUG" to enable debugging output"
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define AUSTIN_DEBUG                // Associated with DEBUG_PRINT()
#define AUSTIN_ACCELEROMETER_DEBUG  // Associated with ACCELEROMETER_DEBUG()

// ============================================================================
// DEBUG_PRINT
// ============================================================================
/* Pseudocode for debug print:
 * 1) If AUSTIN_DEBUG is defined...
 * 2) ...Set the DEBUG_PRINT() macro function to print to the LCD.
 * 3) If AUSTIN_DEBUG is NOT defined...
 * 4) ...Set the DEBUG_PRINT macro function to do nothing.
 */
#ifdef AUSTIN_DEBUG  // START of preprocessor if/else statement.
#define DEBUG_PRINT(string)      \
    {                            \
        PuTTY_PutString(string); \
    }
#else

// {} is included to specify empty statement,
// otherwise compiler throws error
#define DEBUG_PRINT(string) \
    {                       \
    }

#endif  // END of preprocessor if/else statement.

// ============================================================================
// DEBUG_PRINT
// ============================================================================
#ifdef AUSTIN_ACCELEROMETER_DEBUG
#define ACCELEROMETER_DEBUG(string) \
    {                               \
        PuTTY_PutString(string);    \
        CyDelay(100);               \
    }
#else
#define ACCELEROMETER_DEBUG(string) \
    {                               \
    }
#endif

#endif  // End of multiple inclusion protection
/* [] END OF FILE */
