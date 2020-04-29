// TODO: File Header
#ifndef ACCELERATION_VECTOR
#define ACCELERATION_VECTOR

    
// ============= Inclusions =============
#include "project.h"
      
// ============= Definitions =============
#define INVALID_COMPONENT_VALUE -32768
    
typedef int16 Component; 
    // Set as int16 because ADXL345 accelerometer gives
    // two 8 bit registers of data combined to 16 bit integer.
    
// =============  Data Members =============
typedef struct AccelerationVector AccelerationVector;
struct AccelerationVector 
{
    Component x,y,z;
};

// ============= Method Prototypes =============
void AccelerationVector_Constructor(AccelerationVector *me);

#endif
/* [] END OF FILE */
