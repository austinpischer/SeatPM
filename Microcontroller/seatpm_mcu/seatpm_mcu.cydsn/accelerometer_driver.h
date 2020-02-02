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
 *      accelerometer_driver.h
 * File Description:
 *      
 * ============================================================================
*/

#ifndef ACCELEROMETER_DRIVER_H
#define ACCELEROMETER_DRIVER_H

#include "project.h"
#include "adxl345_registers.h"

/* Low Level */
bool Accel_MasterRead(CySCB_Type *hw,
                      cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                      cy_stc_scb_i2c_context_t *i2cContext,
                      uint32_t byteCount);

bool Accel_MasterWrite(CySCB_Type *hw,
                       cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                       cy_stc_scb_i2c_context_t *i2cContext,
                       uint32_t byteCount);

/* Mid Level */
void Accel_ReadDataRegisters(CySCB_Type *hw,
                             cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                             cy_stc_scb_i2c_context_t *i2cContext);

void Accel_WriteConfigRegister(const uint8 RegisterAddress, 
                                uint8 value, 
                                CySCB_Type *hw,
                                cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                                cy_stc_scb_i2c_context_t *i2cContext);

void SetUpAccelerometer(CySCB_Type *hw,
                        cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                        cy_stc_scb_i2c_context_t *i2cContext);

#endif

/* [] END OF FILE */