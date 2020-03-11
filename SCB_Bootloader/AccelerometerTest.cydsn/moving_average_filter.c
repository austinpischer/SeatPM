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
    me->Average.x = INVALID_COMPONENT_VALUE;
    me->Average.y = INVALID_COMPONENT_VALUE;
    me->Average.z = INVALID_COMPONENT_VALUE;
    
    unsigned int DataSetIndex;
    for(DataSetIndex = 0; DataSetIndex < DATA_SET_SIZE; DataSetIndex++)
    {
        me->DataSet[DataSetIndex].x = INVALID_COMPONENT_VALUE;
        me->DataSet[DataSetIndex].y = INVALID_COMPONENT_VALUE;
        me->DataSet[DataSetIndex].z = INVALID_COMPONENT_VALUE;
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
    
    // Get sum of each valid component
    Component Sum_X, Sum_Y, Sum_Z;
    Sum_X = Sum_Y = Sum_Z = 0;
    
    unsigned int SampleSize_X, SampleSize_Y, SampleSize_Z;
    SampleSize_X = SampleSize_Y = SampleSize_Z = 0; 
    
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
        me->Average.x = Sum_X / SampleSize_X;
    }
    else
    {
        me->Average.x = INVALID_COMPONENT_VALUE;
    }
    
    if(SampleSize_Y > 0)
    {
        me->Average.y = Sum_Y / SampleSize_Y;
    }
    else
    {
        me->Average.y = INVALID_COMPONENT_VALUE;
    }
    
    if(SampleSize_Z > 0)
    {
        me->Average.z = Sum_Z / SampleSize_Z;
    }
    else
    {
        me->Average.z = INVALID_COMPONENT_VALUE;
    }
    // Average components calculated, thus average vector calculated.
}
/* [] END OF FILE */
