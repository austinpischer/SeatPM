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
 *      goni_a_driver.h
 * File Description:
 *      
 * ============================================================================
*/

#ifndef GONI_A_DRIVER_H
#define GONI_A_DRIVER_H
    
#include "project.h"
#include "goniometer_driver.h"

void goni_a_ISR();
bool goni_a_isMasterBusy();
bool goni_a_Read(transfer_config config);
bool goni_a_Write(transfer_config config, uint8 numberOfBytes);

#endif

/* [] END OF FILE */
