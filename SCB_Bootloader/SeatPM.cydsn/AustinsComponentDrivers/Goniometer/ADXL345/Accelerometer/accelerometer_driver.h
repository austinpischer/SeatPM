/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-02-01
 *
 * File Name: 
 *      accelerometer_driver.h
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

/* Multiple inclusion protection. See: austin_debug.h */
#ifndef ACCELEROMETER_DRIVER_H
#define ACCELEROMETER_DRIVER_H

#include "project.h"                // For type definitions, etc.
#include "acceleration_vector.h"    // An accelerometer *has an* acceleration vector
#include "generic_utility.h"
    
#define FILTER_DATA_SET_SIZE 5

// Define the type "struct <tag>" as type "<tag>"
typedef struct Accelerometer Accelerometer;
typedef struct Accelerometer_VirtualMethodTable Accelerometer_VirtualMethodTable;
typedef void (*CalculateCurrentAcceleration_FunctionPointer)(Accelerometer Base);

//==================== Accelerometer_VirtualFunctionTable Structure =================
struct Accelerometer_VirtualMethodTable
{
    CalculateCurrentAcceleration_FunctionPointer CalculateCurrentAcceleration;
};

//==================== Accelerometer Structure =================

struct Accelerometer
{
    Accelerometer_VirtualMethodTable vtable;
    AccelerationVector CurrentAcceleration;
    AccelerationVector FilterData[FILTER_DATA_SET_SIZE]; 
    AccelerationVector FilteredAcceleration;
    uint MovingAverageFilter_OldestIndex;
};

//==================== Accelerometer Method Prototypes =================
void Accelerometer_Constructor(Accelerometer *me);
void Accelerometer_UpdateFilterData_MovingAverageFilter(Accelerometer *me);
void Accelerometer_CalculateFilteredAcceleration(Accelerometer *me);

#endif

/* [] END OF FILE */
