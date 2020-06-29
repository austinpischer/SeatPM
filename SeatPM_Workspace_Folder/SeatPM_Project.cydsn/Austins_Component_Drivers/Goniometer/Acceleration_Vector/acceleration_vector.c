/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: acceleration_vector.c
 * Author: Austin Pischer
 * 
 * File Explanation:
 * This file implements the functions declared in "acceleration_vector.h".
 *============================================================================*/

//==============================================================================
// Associated Header
//==============================================================================
#include "acceleration_vector.h"

//==============================================================================
// Constructor - AccelerationVector Class
//==============================================================================
void AccelerationVector_Constructor(AccelerationVector *me)
{
     me->x = me->y = me->z = INVALID_COMPONENT_VALUE;
}
/* [] END OF FILE */
