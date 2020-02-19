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

//#define AUSTIN_DEBUG

#ifdef AUSTIN_DEBUG
#define DEBUG_PRINT(string) (Screen_PrintString(string))
#else
#define DEBUG_PRINT(string) ()
#endif

/* [] END OF FILE */
