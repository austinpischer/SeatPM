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
 *      accelerometer_driver.c
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

#include "accelerometer_driver.h"

/******************************************************************************
 *
 */
void Accelerometer_Constructor(Accelerometer *me)
{
    unsigned int Index;
    for(Index = 0; Index < FILTER_DATA_SET_SIZE; Index++)
    {
        AccelerationVector_Constructor(&(me->FilterData[Index]));
    }
    
    AccelerationVector_Constructor(&(me->CurrentAcceleration));
    AccelerationVector_Constructor(&(me->FilteredAcceleration));
    
    me->MovingAverageFilter_OldestIndex = 0;
   
}

void Accelerometer_UpdateFilterData_MovingAverageFilter(Accelerometer *me)
{
    me->FilterData[me->MovingAverageFilter_OldestIndex] = me->CurrentAcceleration;
    if(me->MovingAverageFilter_OldestIndex == FILTER_DATA_SET_SIZE-1)
    {
        me->MovingAverageFilter_OldestIndex = 0;
    }
    else
    {
        me->MovingAverageFilter_OldestIndex++;
    }
}

void Accelerometer_CalculateFilteredAcceleration(Accelerometer *me)
{
    //Moving Average Filter
    unsigned int  Index;
    
    Component xSum, ySum, zSum;
    xSum = ySum = zSum = 0;
    
    unsigned int xCount, yCount, zCount;
    xCount = yCount = zCount = 0;
    
    // Sum x components, y components, and z components independently
    for(Index = 0; Index < FILTER_DATA_SET_SIZE; Index++)
    {
        if(me->FilterData[Index].x != UNDEFINED_COMPONENT_MAGNITUDE)
        {
            xSum += me->FilterData[Index].x;
            xCount++;
        }
        if(me->FilterData[Index].y != UNDEFINED_COMPONENT_MAGNITUDE)
        {
            ySum += me->FilterData[Index].y;
            yCount++;
        }
        if(me->FilterData[Index].y != UNDEFINED_COMPONENT_MAGNITUDE)
        {
            zSum += me->FilterData[Index].z;
            zCount++;
        }
    }
    
    // Take the average of each sum
    me->FilteredAcceleration.x = xSum/xCount;
    me->FilteredAcceleration.y = ySum/yCount;
    me->FilteredAcceleration.z = zSum/zCount;
}
/* [] END OF FILE */