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

// Comment out "#define AUSTIN_DEBUG" to disable debugging output"
// Uncomment "#define AUSTIN_DEBUG" to enable debugging output"  
#define AUSTIN_DEBUG

/* Pseudocode for debug print:
 * 1) If AUSTIN_DEBUG is defined...
 * 2) ...Set the DEBUG_PRINT() macro function to print to the LCD.
 * 3) If AUSTIN_DEBUG is NOT defined...
 * 4) ...Set the DEBUG_PRINT macro function to do nothing. 
 */
#ifdef AUSTIN_DEBUG // START of preprocessor if/else statement.
#define DEBUG_PRINT(string) (PuTTY_UartPutString(string))
#else 
#define DEBUG_PRINT(string) ()
#endif // END of preprocessor if/else statement.

#endif
/* [] END OF FILE */
