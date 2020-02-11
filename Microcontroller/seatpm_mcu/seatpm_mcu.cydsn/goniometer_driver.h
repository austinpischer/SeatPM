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
 *      goniometer_driver.h
 * File Description:
 *      
 * ============================================================================
*/

#ifndef GONIOMETER_DRIVER_H
#define GONIOMETER_DRIVER_H

#include "project.h"
#include "adxl345_registers.h"
#include "accelerometer_driver.h"
 #include "math.h"
    
#define BUFFER_SIZE 10
#define THIGH_ACCEL_ADDRESS DEFAULT_ADDRESS
#define SHANK_ACCEL_ADDRESS DEFAULT_ADDRESS

    
struct goni_configs {
    xfer_config thigh_accel, shank_accel;
};

void InitializeGoniConfigs(struct goni_configs *myConfigs,
                           uint8 *thigh_accel_buffer, 
                           uint8 *shank_accel_buffer);
void InitializeGoniAccels(struct goni_configs *myConfigs);
void Goniometer_ReadDataRegisters(struct goni_configs myConfigs);
uint16 CalculateKneeAngle(struct accel_vector thigh_vector,
                          struct accel_vector shank_vector);
#endif    
    
/* [] END OF FILE */
