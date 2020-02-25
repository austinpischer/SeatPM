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
 *      acceleration_vector.h
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

/* Multiple inclusion protection. See: austin_debug.h */
#ifndef ACCELERATION_VECTOR_H
#define ACCELERATION_VECTOR_H

#include "project.h"
#include "austin_debug.h"
    
#define UNDEFINED_COMPONENT_MAGNITUDE -32769 // Just outside of int16 range
    
typedef double Component;
    
// Define the type "struct <tag>" as type "<tag>"
typedef struct AccelerationVector AccelerationVector;
struct AccelerationVector 
{
    Component x,y,z;
};

void AccelerationVector_Constructor(AccelerationVector *me);
#endif
/* [] END OF FILE */
