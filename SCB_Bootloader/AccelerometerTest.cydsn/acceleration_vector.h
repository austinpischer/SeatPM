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
#ifndef ACCELERATION_VECTOR
#define ACCELERATION_VECTOR

#include "project.h"
      
#define INVALID_COMPONENT_VALUE -32768
typedef int16 Component;
typedef struct AccelerationVector AccelerationVector;
struct AccelerationVector 
{
    Component x,y,z;
};
#endif
/* [] END OF FILE */
