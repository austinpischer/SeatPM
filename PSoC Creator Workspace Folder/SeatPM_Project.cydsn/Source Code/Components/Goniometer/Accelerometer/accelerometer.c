/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: accelerometer_driver.c
 * Author: Austin Pischer
 * 
 * File Explanation:
 * This file implements the functions declared in "accelerometer.h"
 *============================================================================*/

//==============================================================================
// Associated Header File Inclusion
//==============================================================================
#include "accelerometer.h"

//==============================================================================
// Constructor
//==============================================================================
void Accelerometer_Constructor(Accelerometer *me, 
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration_Pointer)
{
    ACCELEROMETER_DEBUG("Acceleration Vector Constructor\r\n");
    AccelerationVector_Constructor(&(me->CurrentAcceleration));
    ACCELEROMETER_DEBUG("Moving Average Filter Constructor\r\n");
    MovingAverageFilter_Constructor(&(me->Filter));
    
    // Set the virtual function as the base class function by default
    if(Accelerometer_UpdateCurrentAcceleration_Pointer 
        != &Virtual_Accelerometer_UpdateCurrentAcceleration)
    {
            me->Accelerometer_UpdateCurrentAcceleration
                            = Accelerometer_UpdateCurrentAcceleration_Pointer;
    }
    else
    {
        me->Accelerometer_UpdateCurrentAcceleration 
            = &Virtual_Accelerometer_UpdateCurrentAcceleration; 
    }
}

//==============================================================================
// Update Current Acceleration (Virtual)
//==============================================================================
void Virtual_Accelerometer_UpdateCurrentAcceleration(Accelerometer *me)
{
    // Do nothing, as this is the base virtual function
    // with no physical accelerometer implementation to gather actual data
}

//==============================================================================
// Update Filtered Acceleration
//==============================================================================
void Accelerometer_UpdateFilteredAcceleration(Accelerometer *me)
{
    // Doesn't need to be implemented in
    me-> Accelerometer_UpdateCurrentAcceleration(me);
    me->FilteredAcceleration = MovingAverageFilter_GetAverage(&(me->Filter));
}
/* [] END OF FILE */