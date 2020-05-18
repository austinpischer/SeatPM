/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: adxl345_registers.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * The ADXL345 accelerometer chip has a number of pieces of memory.
 * These memory slices are registers.
 * 
 * To access the data in these registers, 
 * we need to have the addresses of the locations in memory.
 * 
 * These addresses are 1 byte or 8 bit values,
 * which can be represented by a two digit hexidecimal number.
 * 
 * This file uses #define statements to give names to each of these numbers
 * so that the code utilizing the registers is more readable and meaningful.
 *============================================================================*/

// Start of multiple inclusion protection
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
    
#endif // End of multiple inclusion protection. 
/* [] END OF FILE */
