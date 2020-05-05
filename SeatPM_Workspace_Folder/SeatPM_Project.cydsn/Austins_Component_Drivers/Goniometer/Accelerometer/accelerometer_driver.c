#include "accelerometer_driver.h"


void Accelerometer_Constructor(Accelerometer *me, 
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration_Pointer)
{
    AccelerationVector_Constructor(&(me->CurrentAcceleration));
    MovingAverageFilter_Constructor(&(me->Filter));
    
    // Set the virtual function as the base class function by default
    if(Accelerometer_UpdateCurrentAcceleration_Pointer != &Virtual_Accelerometer_UpdateCurrentAcceleration)
    {
            me->Accelerometer_UpdateCurrentAcceleration
                            = Accelerometer_UpdateCurrentAcceleration_Pointer;
    }
    else
    {
        me->Accelerometer_UpdateCurrentAcceleration = &Virtual_Accelerometer_UpdateCurrentAcceleration; 
    }
}

void Virtual_Accelerometer_UpdateCurrentAcceleration(Accelerometer *me)
{
    // Do nothing, as this is the base virtual function
    // with no physical accelerometer implementation to gather actual data
}

void Accelerometer_UpdateFilteredAcceleration(Accelerometer *me)
{
    // Doesn't need to be implemented in
    me-> Accelerometer_UpdateCurrentAcceleration(me);
    me->FilteredAcceleration = MovingAverageFilter_GetAverage(&(me->Filter));
}

    