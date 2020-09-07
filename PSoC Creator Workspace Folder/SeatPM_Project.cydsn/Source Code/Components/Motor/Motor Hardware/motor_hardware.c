#include "motor_hardware.h"

void Motor_Setup()
{
    Motor_Clock_Start();
    Motor_PWM_Start(); // Start motor pulse width modulation function generator
    MotorHardware_SetSpeed(0); // Stop motor
}

void MotorHardware_SetSpeed(double Speed)
{
    Motor_PWM_WriteCompare(Speed);
}

void MotorHardware_SetDirection(bool RetractFALSE_ReleaseTRUE)
{
    Motor_Direction_Write(RetractFALSE_ReleaseTRUE);
}