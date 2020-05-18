/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: moving_average_filter.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * The Moving Average Filter Class is intended to reduce noise in the
 * accelerometer readings. We acheive this by averaging the last *n* readings
 * that fed into the filter, updating the average every time
 * that we are fed a new reading.
 *============================================================================*/
#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include "acceleration_vector.h"

#define DATA_SET_SIZE 5
    
typedef struct MovingAverageFilter MovingAverageFilter;
struct MovingAverageFilter
{
    AccelerationVector DataSet[DATA_SET_SIZE];
    unsigned int DataSet_IndexOfOldestData;
};

void MovingAverageFilter_Constructor(MovingAverageFilter *me);
void MovingAverageFilter_UpdateDataSet(MovingAverageFilter *me, AccelerationVector NewData);
AccelerationVector MovingAverageFilter_GetAverage(MovingAverageFilter *me);
#endif

/* [] END OF FILE */
