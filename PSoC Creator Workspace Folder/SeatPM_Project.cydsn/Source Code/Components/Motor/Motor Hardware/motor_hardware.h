#ifndef MOTOR_HARDWARE_H
#define MOTOR_HARDWARE_H

#include "project.h"
#include "debug.h" // for bool 

void Motor_Setup();
void MotorHardware_SetSpeed(double Speed);
void MotorHardware_SetDirection(bool RetractFALSE_ReleaseTRUE);

#endif