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

//=============================================================================
// Global Variables
//=============================================================================
// All global variables should be named with a preceding "g_"

// Accelerometer RX/TX buffers
// The SeatPM has 2 goniometers with 2 accelerometers each.
// Each accelerometer needs a read buffer and a write buffer.
//      Thus, a/b refers to the goniometer
//      and 0/1 refers to each accelerometer in the goniometer 

uint8 g_a0_Buffer[BUFFER_SIZE];
uint8 g_a1_Buffer[BUFFER_SIZE];
uint8 g_b0_Buffer[BUFFER_SIZE];
uint8 g_b1_Buffer[BUFFER_SIZE];

struct GoniometerTransferConfigs {
    cy_stc_scb_i2c_master_xfer_config_t a0, a1, b0, b1;
};

void InitializeGoniometerTranferConfigs(struct GoniometerTransferConfigs myConfigs);

bool Accel_MasterRead(CySCB_Type base,
                      cy_stc_scb_i2c_master_xfer_config_t xferConfig,
                      cy_stc_scb_i2c_context_t i2cContext,
                      uint32_t byteCount);

bool Accel_MasterWrite(CySCB_Type base,
                       cy_stc_scb_i2c_master_xfer_config_t xferConfig,
                       cy_stc_scb_i2c_context_t i2cContext,
                       uint32_t byteCount);

#endif    
    
/* [] END OF FILE */
