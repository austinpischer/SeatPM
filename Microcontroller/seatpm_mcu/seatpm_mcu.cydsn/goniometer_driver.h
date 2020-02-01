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
    
#define BUFFER_SIZE 10
#define A0_ADDR DEFAULT_ADDRESS
#define A1_ADDR ALTERNATE_ADDRESS
#define B0_ADDR DEFAULT_ADDRESS
#define B1_ADDR ALTERNATE_ADDRESS
    
typedef cy_stc_scb_i2c_master_xfer_config_t transfer_config;

struct GoniometerTransferConfigs {
    transfer_config a0, a1, b0, b1;
};

void InitializeGoniometerTranferConfigs(struct GoniometerTransferConfigs myConfigs);

#endif    
    
/* [] END OF FILE */
