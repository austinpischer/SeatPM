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

#ifndef ACCELEROMETER_DRIVER_H
#define ACCELEROMETER_DRIVER_H

#include "project.h"
#include "acceleration_vector.h"
    
#define FILTER_DATA_SET_SIZE 5
    
typedef unsigned int uint;
    
typedef struct Accelerometer Accelerometer;
struct Accelerometer
{
    char* Name;
    AccelerationVector CurrentAcceleration;
    AccelerationVector FilterData[FILTER_DATA_SET_SIZE]; 
    AccelerationVector FilteredAcceleration;
    uint MovingAverageFilter_OldestIndex;
};

void Accelerometer_Initialize(Accelerometer *me);
void Accelerometer_UpdateFilterData_MovingAverageFilter(Accelerometer *me);
void Accelerometer_CalculateFilteredAcceleration(Accelerometer *me);

#endif

/* [] END OF FILE */
