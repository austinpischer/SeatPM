/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-02-18
 *
 * File Name: 
 *      acceleration_vector.c
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

#include "acceleration_vector.h"

void AccelerationVector_Constructor(AccelerationVector *me)
{
    DEBUG_PRINT("Acceleration Vector constructor called...\r\n");
    me->x = UNDEFINED_COMPONENT_MAGNITUDE;
    me->y = UNDEFINED_COMPONENT_MAGNITUDE;
    me->z = UNDEFINED_COMPONENT_MAGNITUDE;
}

/* [] END OF FILE */
