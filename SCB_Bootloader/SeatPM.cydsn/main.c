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

// ========================== Includes ========================================
#include "project.h"
#include "austin_debug.h"
#include "goniometer_driver.h"
#include <stdio.h>

// ========================== Global Variables ================================
// g_ prefix means that variable is global: can be accessed from all files
Goniometer g_KneeGoniometer;

// ========================== Function Prototypes =============================
void Debugging_Components_Startup();
void Bootloader_Components_Startup();
void Goniometer_Components_Startup();


// ========================== Main ============================================
int main(void)
{
    DEBUG_PRINT("Start\r\n");
    CyGlobalIntEnable; /* Enable global interrupts. */    
    
    /* Component Startup */
    Debugging_Components_Startup();
    Bootloader_Components_Startup();
    Goniometer_Components_Startup();
    DEBUG_PRINT("Component startup complete\r\n");
    
    /* Goniometer Setup */
    Goniometer_Constructor(&g_KneeGoniometer);
    g_KneeGoniometer.Accelerometer_A.I2C_Address = THIGH_ACCELEROMETER_ADDRESS;
    g_KneeGoniometer.Accelerometer_B.I2C_Address = SHANK_ACCELEROMETER_ADDRESS;
    DEBUG_PRINT("Goniometer setup complete\r\n");
    
    /* Interrupt Startup */
    // Goniometer Sample Interrupt
    //Goniometer_Sample_Interrupt_ClearPending();
    //Goniometer_Sample_Interrupt_StartEx(Goniometer_Sample_ISR_Handle);
    // Reset Interrupt
    //Reset_ISR_ClearPending();
    //Reset_ISR_StartEx(Reset_ISR_Handler);
    
    /* Variables */
    char DebugString[64];
    for(;;)
    {
        /* Place your application code here. */
        
        // 1) Get the accelerometer data for both accelerometers
        ADXL345_ReadDataRegisters(&(g_KneeGoniometer.Accelerometer_A));
        ADXL345_ReadDataRegisters(&(g_KneeGoniometer.Accelerometer_B));
        sprintf(DebugString,
                "ax0=%d, ax1=%d, ay0=%d, ay1=%d, az0=%d, az1=%d\r\n",
                g_KneeGoniometer.Accelerometer_A.ReadBuffer[0],
                g_KneeGoniometer.Accelerometer_A.ReadBuffer[1],
                g_KneeGoniometer.Accelerometer_A.ReadBuffer[2],
                g_KneeGoniometer.Accelerometer_A.ReadBuffer[3],
                g_KneeGoniometer.Accelerometer_A.ReadBuffer[4],
                g_KneeGoniometer.Accelerometer_A.ReadBuffer[5]);
                sprintf(DebugString,
                "bx0=%d, bx1=%d, by0=%d, by1=%d, bz0=%d, bz1=%d\r\n",
                g_KneeGoniometer.Accelerometer_B.ReadBuffer[0],
                g_KneeGoniometer.Accelerometer_B.ReadBuffer[1],
                g_KneeGoniometer.Accelerometer_B.ReadBuffer[2],
                g_KneeGoniometer.Accelerometer_B.ReadBuffer[3],
                g_KneeGoniometer.Accelerometer_B.ReadBuffer[4],
                g_KneeGoniometer.Accelerometer_B.ReadBuffer[5]);
        
        // 2) Calculate the acceleration vectors 
        //      from the data of both accelerometers
        ADXL345_CalculateCurrentAcceleration(&(g_KneeGoniometer.Accelerometer_A));
        ADXL345_CalculateCurrentAcceleration(&(g_KneeGoniometer.Accelerometer_B));
        
        
        // 3) Calculate the knee angle based on the acceleration vectors
        Goniometer_CalculateAngle(&g_KneeGoniometer);
        
    }
}

// ========================== Function Implementations ========================
CY_ISR(Reset_ISR_Handler)
{
    Bootloadable_Load(); /* Force a bootloader restart */
}

void Debugging_Components_Startup()
{
    PuTTY_Start();
}
void UserInterface_Components_Startup()
{
    Screen_Start();
}
void Bootloader_Components_Startup()
{
    Clock_12kHz_Start();
    Reset_Timer_Start();
}
void Goniometer_Components_Startup()
{
    Clock_1kHz_Start();
    Goniometer_Sample_Timer_Start();
    I2C_Start();
    
}
/* [] END OF FILE */
