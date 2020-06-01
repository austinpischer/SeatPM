// TODO: File Header
#ifndef AUSTIN_DEBUG_H
#define AUSTIN_DEBUG_H
    
//=============================================================================
// Boolean Type
//=============================================================================
typedef int bool;
#define TRUE 1
#define FALSE 0
    
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Comment out "#define AUSTIN_DEBUG" to disable debugging output"
 * Uncomment "#define AUSTIN_DEBUG" to enable debugging output"
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define AUSTIN_DEBUG // Associated with DEBUG_PRINT
#define AUSTIN_CSV
#define AUSTIN_SCREEN_DEBUG
#define AUSTIN_ACCELEROMETER_DEBUG
#define AUSTIN_GONIOMETER_DEBUG
//#define GONIOMETER_TEST
#define BUTTON_TEST
    
// ============================================================================
// DEBUG_PRINT
// ============================================================================
/* Pseudocode for debug print:
 * 1) If AUSTIN_DEBUG is defined...
 * 2) ...Set the DEBUG_PRINT() macro function to print to the LCD.
 * 3) If AUSTIN_DEBUG is NOT defined...
 * 4) ...Set the DEBUG_PRINT macro function to do nothing. 
 */
#ifdef AUSTIN_DEBUG // START of preprocessor if/else statement.
    
    // Note: Macro function replaces left statement with right before compiling
    #define DEBUG_PRINT(string) (PuTTY_UartPutString(string))  
    
#else
    
    // {} is included to specify empty statement,s 
    // otherwise compiler throws error
    #define DEBUG_PRINT(string) ({})                            
    
#endif // END of preprocessor if/else statement.

// ============================================================================
// CSV_PRINT
// ============================================================================
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
    #define ACCELEROMETER_DEBUG(string) {\
                                         PuTTY_UartPutString(string);\
                                         CyDelay(100); \
                                        } 
#else
    #define ACCELEROMETER_DEBUG(string) ({})
#endif

#ifdef AUSTIN_GONIOMETER_DEBUG
    #define GONIOMETER_DEBUG(string) {\
                                      PuTTY_UartPutString(string);\
                                      CyDelay(100); \
                                     } 
#else
    #define GONIOMETER_DEBUG(string) ({})
#endif
    

#endif
/* [] END OF FILE */
