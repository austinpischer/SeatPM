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

/* Note - Multiple inclusion protection:
 * In C, the preprocessor directive '#include "<file_name>" ' tells the compiler
 * to replace that line with all of the code from <file_name>. 
 * If we include a file multiple times, undesired behavior may occur.
 *
 * Therefore, any header file in this project should, at least, contain the following:
 * 1. "#ifndef <FILE_NAME>" 
 *          (ifndef = if not #define-ed)
 * 2. "#define <FILE_NAME>"
 * 3. All desired header code
 * 4. "#endif" 
 *          (endif = end if, required for every preprocessor "#if___" statement)
 *
 * Explanation: After the first inclusion of a file, 
 *              subsequent instances of the #ifndef statement will return false
 *              because <FILE_NAME> is #define-ed after the first instance.
 *              When #ifndef returns false, none of the header code is compiled,
 *              and the effect is that the header code is only compiled once.
 */
#ifndef AUSTIN_DEBUG_H // 1
#define AUSTIN_DEBUG_H // 2
//3:
    
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

#endif // 4
/* [] END OF FILE */
