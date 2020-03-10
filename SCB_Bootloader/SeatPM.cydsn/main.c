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
#include "user_interface_fsm.h"
#include <stdio.h>

// ========================== Global Variables ================================
// g_ prefix means that variable is global: can be accessed from all files
Goniometer g_KneeGoniometer;
UserInterface_FSM g_UserInterface;

// ========================== Function Prototypes =============================
CY_ISR_PROTO(Reset_ISR_Handler); 
CY_ISR_PROTO(Goniometer_Sample_ISR_Handle);
void Debugging_Components_Startup();
void UserInterface_Components_Startup();
void Bootloader_Components_Startup();
void Goniometer_Components_Startup();


// ========================== Main ============================================
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */    
    /* Component Startup */
    Debugging_Components_Startup();
    UserInterface_Components_Startup();
    Bootloader_Components_Startup();
    Goniometer_Components_Startup();

    /* Goniometer Setup */
    Goniometer_Constructor(&g_KneeGoniometer);
    g_KneeGoniometer.Accelerometer_A.I2C_Address = THIGH_ACCELEROMETER_ADDRESS;
    g_KneeGoniometer.Accelerometer_B.I2C_Address = SHANK_ACCELEROMETER_ADDRESS;
    
    /* User Interface Setup */
    UserInterface_FSM_Constructor(&g_UserInterface);
    
    /* Interrupt Startup */
    Goniometer_Sample_Interrupt_ClearPending();
    //Goniometer_Sample_Interrupt_StartEx(Goniometer_Sample_ISR_Handle);
    
    Reset_ISR_ClearPending();
    Reset_ISR_StartEx(Reset_ISR_Handler);
    
    //Debug Strings
    char accelstring[16];
    for(;;)
    {
        /* Place your application code here. */
        
        // 1) Get the accelerometer data for both accelerometers
        ADXL345_ReadDataRegisters(&(g_KneeGoniometer.Accelerometer_A));
        //ADXL345_ReadDataRegisters(&(g_KneeGoniometer.Accelerometer_B));
        // 2) Calculate the acceleration vectors 
        //      from the data of both accelerometers
        ADXL345_CalculateCurrentAcceleration(&(g_KneeGoniometer.Accelerometer_A));
        
        sprintf(accelstring,
                "x:%.2lf y:%.2lf z:%.2lf",
                g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration.x,
                g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration.y,
                g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration.z);
        DEBUG_PRINT(accelstring);
        
        ADXL345_CalculateCurrentAcceleration(&(g_KneeGoniometer.Accelerometer_B));
        
        /*
        DEBUG_PRINT("B Accel:");
        sprintf(accelstring,
                "x:%.2lf, y:%.2lf, z:%.2lf",
                g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration.x,
                g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration.y,
                g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration.z);
        DEBUG_PRINT(accelstring);
        */
        
        // 3) Calculate the knee angle based on the acceleration vectors
        //Goniometer_CalculateCurrentAngle(&g_KneeGoniometer);
        
        //UserInterface_FSM_UpdateCurrentKneeAngleString(&g_UserInterface, &g_KneeGoniometer);
        //DEBUG_PRINT(g_UserInterface.KneeAngleString);
    }
}

// ========================== Function Implementations ========================
CY_ISR(Reset_ISR_Handler)
{
    //Bootloadable_Load(); /* Force a bootloader restart */
}

CY_ISR(Goniometer_Sample_ISR_Handle)
{
    /* Pseudocode:
     * 1) Get the accelerometer data for both accelerometers
     * 2) Calculate the acceleration vectors 
     *      from the data of both accelerometers
     * 3) Calculate the knee angle based on the acceleration vectors
     */
    
    // 1) Get the accelerometer data for both accelerometers
    ADXL345_ReadDataRegisters(&(g_KneeGoniometer.Accelerometer_A));
    ADXL345_ReadDataRegisters(&(g_KneeGoniometer.Accelerometer_B));
    // 2) Calculate the acceleration vectors 
    //      from the data of both accelerometers
    ADXL345_CalculateCurrentAcceleration(&(g_KneeGoniometer.Accelerometer_A));
    ADXL345_CalculateCurrentAcceleration(&(g_KneeGoniometer.Accelerometer_B));
    // 3) Calculate the knee angle based on the acceleration vectors
    Goniometer_CalculateAngle(&g_KneeGoniometer, 
                    g_KneeGoniometer.Accelerometer_A.Base.CurrentAcceleration,
                    g_KneeGoniometer.Accelerometer_B.Base.CurrentAcceleration);
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
    
}
/* [] END OF FILE */
