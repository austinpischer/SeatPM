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

#ifndef ADXL345_REGISTERS_H
#define ADXL345_REGISTERS_H

/* I2C Addresses */ 
#define DEFAULT_ADDRESS 0x1D
#define ALTERNATE_ADDRESS 0x53

/* Device ID Registers */
#define DEVID 0x00 // R, Device ID.

/* Offset Registers */
#define OFSX 0x1E // R/W, X-axis offset.
#define OFSY 0x1F // R/W, Y-axis offset.
#define OFSZ 0x20 // R/W, Z-axis offset.

/* Power Registers */ 
#define BW_RATE 0x2C // R/W, Data rate and power mode control.
#define POWER_CTL 0x2D // R/W, Power-saving features control.

/* Data Registers */ 
#define DATA_FORMAT 0x31 // R/W, Data format control.
#define DATAX0 0x32 // R, X-Axis Data 0.
#define DATAX1 0x33 // R, X-Axis Data 1.
#define DATAY0 0x34 // R, Y-Axis Data 0.
#define DATAY1 0x35 // R, Y-Axis Data 1.
#define DATAZ0 0x36 // R, Z-Axis Data 0.
#define DATAZ1 0x37 // R, Z-Axis Data 1.
    
#endif 
/* [] END OF FILE */
