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
#include "moving_average_filter.h"
void MovingAverageFilter_Constructor(MovingAverageFilter *me)
{
    unsigned int DataSetIndex;
    for(DataSetIndex = 0; DataSetIndex < DATA_SET_SIZE; DataSetIndex++)
    {
        AccelerationVector_Constructor(&(me->DataSet[DataSetIndex]));
    }
    
    me->DataSet_IndexOfOldestData = 0;
    
}

void MovingAverageFilter_UpdateAverage(MovingAverageFilter *me, AccelerationVector NewData)
{
    // Replace oldest data with new data
    me->DataSet[me->DataSet_IndexOfOldestData] = NewData;\
    // Update index of oldest data
    me->DataSet_IndexOfOldestData++;
    // Wrap around to zero if index of oldest data exceeds valid index
    if(me->DataSet_IndexOfOldestData == DATA_SET_SIZE)
    {
        me->DataSet_IndexOfOldestData = 0;
    }
}

AccelerationVector MovingAverageFilter_GetAverage(MovingAverageFilter *me)
{
    AccelerationVector Average;
    
    // Get sum of each valid component
    Component Sum_X, Sum_Y, Sum_Z;
    Sum_X = Sum_Y = Sum_Z = 0;
    
    unsigned int SampleSize_X, SampleSize_Y, SampleSize_Z;
    SampleSize_X = SampleSize_Y = SampleSize_Z = 0; 
    
    // Iterate through the data set,
    // Summing up the data values for each acceleration component (x,y,z),
    // and keeping track of the number of component values encountered (sample size)
    // so that at the end we can take the average of each component
    unsigned int DataSetIndex;
    for(DataSetIndex = 0; DataSetIndex < DATA_SET_SIZE; DataSetIndex++)
    {
        if(me->DataSet[DataSetIndex].x != INVALID_COMPONENT_VALUE)
        {
            Sum_X += me->DataSet[DataSetIndex].x;
            SampleSize_X++;
            CYASSERT(SampleSize_X <= DATA_SET_SIZE);
        }
        if(me->DataSet[DataSetIndex].y != INVALID_COMPONENT_VALUE)
        {
            Sum_Y += me->DataSet[DataSetIndex].y;
            SampleSize_Y++;
            CYASSERT(SampleSize_Y <= DATA_SET_SIZE);
        }
        if(me->DataSet[DataSetIndex].z != INVALID_COMPONENT_VALUE)
        {
            Sum_Z += me->DataSet[DataSetIndex].z;
            SampleSize_Z++;
            CYASSERT(SampleSize_Z <= DATA_SET_SIZE);
        }
    }
    
        // Calculate new average
    if(SampleSize_X > 0)
    {
        Average.x = Sum_X / SampleSize_X;
    }
    else
    {
        Average.x = INVALID_COMPONENT_VALUE;
    }
    
    if(SampleSize_Y > 0)
    {
        Average.y = Sum_Y / SampleSize_Y;
    }
    else
    {
        Average.y = INVALID_COMPONENT_VALUE;
    }
    
    if(SampleSize_Z > 0)
    {
        Average.z = Sum_Z / SampleSize_Z;
    }
    else
    {
        Average.z = INVALID_COMPONENT_VALUE;
    }
    // Average components calculated, thus average vector calculated.
    return(Average);
}
/* [] END OF FILE */
