/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-01-31
 *
 * File Name: 
 *      goniometer_driver.c
 * File Description:
 *      
 * ============================================================================
*/

#include "goniometer_driver.h"

/******************************************************************************
 *
 */
void InitializeGoniConfigs(struct goni_configs *myConfigs,
                           uint8 *thigh_accel_buffer, 
                           uint8 *shank_accel_buffer)
{    
    /* buffer */
    myConfigs->thigh_accel.buffer = thigh_accel_buffer;
    myConfigs->shank_accel.buffer = shank_accel_buffer;
    
    /* bufferSize */ 
    myConfigs->thigh_accel.bufferSize = BUFFER_SIZE;
    myConfigs->shank_accel.bufferSize = BUFFER_SIZE;
    
    /* Address */
    myConfigs->thigh_accel.slaveAddress = THIGH_ACCEL_ADDRESS;
    myConfigs->shank_accel.slaveAddress = SHANK_ACCEL_ADDRESS;
    
    /* Tranfer Pending */
    myConfigs->thigh_accel.xferPending = false;
    myConfigs->shank_accel.xferPending = false;
}

/******************************************************************************
 *
 */
void InitializeGoniAccels(struct goni_configs *myConfigs)
{
    /* Initialize Thigh Accelerometer */
    InitializeAccelerometer(goni_a_HW,
                            &myConfigs->thigh_accel,
                            &goni_a_context);
    /* Initialize Shank Accelerometer */
    InitializeAccelerometer(goni_a_HW,
                            &myConfigs->shank_accel,
                            &goni_a_context);
}

/******************************************************************************
 *
 */
void Goniometer_ReadDataRegisters(struct goni_configs myConfigs)
{
    Accel_ReadDataRegisters(goni_a_HW, &myConfigs.thigh_accel, &goni_a_context);
    Accel_ReadDataRegisters(goni_a_HW, &myConfigs.shank_accel, &goni_a_context);
}

/******************************************************************************
 *
 */
uint16 CalculateKneeAngle(struct accel_vector thigh_vector,
                          struct accel_vector shank_vector)
{
    double kneeAngle;
    double dotProduct;
    double aMagnitude, bMagnitude;
    double ax, ay, az;
    double bx, by, bz;
    
    ax = (double) thigh_vector.x;
    ay = (double) thigh_vector.y;
    az = (double) thigh_vector.z;
    
    bx = (double) shank_vector.x;
    by = (double) shank_vector.y;
    bz = (double) shank_vector.z;

    dotProduct = (ax*bx)+(ay*by)+(az*bz); 
    
    aMagnitude = sqrt((ax*ax)+(ay*ay)+(az*az));
    bMagnitude = sqrt((bx*bx)+(by*by)+(bz*bz));
    
    kneeAngle = acos(dotProduct/(aMagnitude*bMagnitude));
    
    return(kneeAngle);
}
/* [] END OF FILE */
