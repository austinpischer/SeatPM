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
#ifndef AUSTIN_DEBUG_H
#define AUSTIN_DEBUG_H
    
typedef int bool;
#define TRUE 1
#define FALSE 0
    
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: This project requires that the caller of a macro funtion place a semicolon (;) after calling it in code.
//       As such, any new macro function must not place a semicolon on the last line of the macro function.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Function constants
    
#define SCREEN_DEBUG_DURATION_IN_MILLISECONDS 1000
    
// Comment out "#define AUSTIN_DEBUG" to disable debugging output"
// Uncomment "#define AUSTIN_DEBUG" to enable debugging output" 
#define AUSTIN_DEBUG
//#define AUSTIN_CSV
#define AUSTIN_SCREEN_DEBUG
#define AUSTIN_ACCELEROMETER_DEBUG
#define AUSTIN_GONIOMETER_DEBUG

/* Pseudocode for debug print:
 * 1) If AUSTIN_DEBUG is defined...
 * 2) ...Set the DEBUG_PRINT() macro function to print to the LCD.
 * 3) If AUSTIN_DEBUG is NOT defined...
 * 4) ...Set the DEBUG_PRINT macro function to do nothing. 
 */
#ifdef AUSTIN_DEBUG // START of preprocessor if/else statement.
    #define DEBUG_PRINT(string) (PuTTY_UartPutString(string))   // Macro function replaces left statement with right before compiling
#else
    #define DEBUG_PRINT(string) ({})                            // {} is included to specify empty statement, otherwise compiler throws error
#endif                                                          // END of preprocessor if/else statement.


#ifdef AUSTIN_CSV
#define CSV_PRINT(string) (PuTTY_UartPutString(string))
#else
    #define CSV_PRINT(string) ({})
#endif


#ifdef AUSTIN_SCREEN_DEBUG
   #define SCREEN_DEBUG(string) {\
                                 Screen_ClearDisplay();\
                                 Screen_PrintString(string); \
                                }
#else
    #define SCREEN_DEBUG(string) ({})
#endif


#ifdef AUSTIN_ACCELEROMETER_DEBUG
    #define ACCELEROMETER_DEBUG(string) (PuTTY_UartPutString(string)) 
#else
    #define ACCELEROMETER_DEBUG(string) ({})
#endif

#ifdef AUSTIN_GONIOMETER_DEBUG
    #define GONIOMETER_DEBUG(string) (PuTTY_UartPutString(string)) 
#else
    #define GONIOMETER_DEBUG(string) ({})
#endif
    

#endif
/* [] END OF FILE */
