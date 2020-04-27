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

#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include "acceleration_vector.h"

#define DATA_SET_SIZE 5
    
typedef struct MovingAverageFilter MovingAverageFilter;
struct MovingAverageFilter
{
    AccelerationVector DataSet[DATA_SET_SIZE];
    AccelerationVector Average;
    unsigned int DataSet_IndexOfOldestData;
};

void MovingAverageFilter_Constructor(MovingAverageFilter *me);
void MovingAverageFilter_UpdateAverage(MovingAverageFilter *me, AccelerationVector NewData);
#endif

/* [] END OF FILE */