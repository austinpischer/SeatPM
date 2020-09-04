/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: moving_average_filter.h
Author: Austin Pischer

File Explanation:
The Moving Average Filter Class is intended to reduce noise in the
accelerometer readings. We achieve this by averaging the last *n* readings
that fed into the filter, updating the average every time that we are fed a
new reading.
==============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

//==============================================================================
// Inclusions
//==============================================================================
#include "acceleration_vector.h"

//==============================================================================
// Definitions
//==============================================================================
#define DATA_SET_SIZE 5

//==============================================================================
// Type Definitions
//==============================================================================
typedef struct MovingAverageFilter MovingAverageFilter;
    
//==============================================================================
// Data Members - Moving Average Filter Class
//==============================================================================
struct MovingAverageFilter
{
    AccelerationVector DataSet[DATA_SET_SIZE];
    unsigned int DataSet_IndexOfOldestData;
};

//==============================================================================
// Method Members - Moving Average Filter Class
//==============================================================================

/* Function Name: MovingAverageFilter_Constructor
Requirements: Reference to MovingAverageFilter instance
Results: ReferencedMovingAverageFilter instance has initialized data members
*/
void MovingAverageFilter_Constructor(MovingAverageFilter *me);

/* Function Name: MovingAverageFilter_UpdateDataSet
Requirements: - Reference to MovingAverageFilter instance
              - New acceleration vector to insert in data set
Results: Dataset of instance has oldest acceleration vector replaced with the
passed in acceleration vector.
*/
void MovingAverageFilter_UpdateDataSet(MovingAverageFilter *me, AccelerationVector NewData);

/* Function Name: MovingAverageFilter_GetAverage
Requirements: Reference to MovingAverageFilter instance
Results: Acceleration Vector whose components are the average of the components
currently present in the instance data set.
*/
AccelerationVector MovingAverageFilter_GetAverage(MovingAverageFilter *me);

#endif // End of multiple inclusion protection
/* [] END OF FILE */
