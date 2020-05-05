
#include "project.h"
#include "acceleration_vector.h"
#include "moving_average_filter.h"

typedef struct Accelerometer Accelerometer;

// https://dmitryfrank.com/articles/oop_in_c
typedef void (*Accelerometer_VirtualFunctionPointer)(Accelerometer *me);

struct Accelerometer
{
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration;  
        /* NOTE: Normally, we would want only one virtual method table
                 for both the base class and for each derived class.
                 However, the simplicity of one function pointer for each
                 instance of the class outweighs the memory cost
                 since we only have 2 instances of the dervied class (ADXL345)
                 In the form of the 2 acceleormeters for the goniometer.
        */
    AccelerationVector CurrentAcceleration;
    AccelerationVector FilteredAcceleration;
    MovingAverageFilter Filter;
};

void Accelerometer_Constructor(Accelerometer *me, 
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration_Pointer);
void Virtual_Accelerometer_UpdateCurrentAcceleration(Accelerometer *me);
void Accelerometer_UpdateFilteredAcceleration(Accelerometer *me);