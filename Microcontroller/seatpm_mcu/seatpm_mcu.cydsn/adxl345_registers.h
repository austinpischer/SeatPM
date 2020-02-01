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
 *      adxl345_registers.h
 * File Description:
 *      Each ADXL345 accelerometer has a number of registers, each with their
 *      own address. This file creates macros for each register address.
 *      The intent of these macros are to make use of register addresses
 *      more convenient and more human-readable.
 *      These macros were made according to the information on page 14 of the
 *      "ADXL345_Accelerometer_Datasheet.pdf" included in the directory
 *      "SeatPM/Microcontroller"
 *
 * ============================================================================
*/

#ifndef ADXL345_REGISTERS_H
#define ADXL345_REGISTERS_H

/* I2C Addresses */   
#define DEFAULT_ADDRESS 0x1D
#define ALTERNATE_ADDRESS 0x3B

/* Device ID Registers */
#define DEVID 0x00 // R, Device ID.

/* Tap Registers */ 
#define THRESH_TAP 0x1D // R/W, Tap threshold.
#define DUR 0x21 // R/W, Tap duration.
#define LATENT 0x22 // R/W, Tap latency.
#define WINDOW 0x23 // R/W, Tap window.
#define TAP_AXES 0x2A // R/W, Axis control for tap/double tap.
#define ACT_TAP_STATUS 0x2B // R, Source of tap/double tap.

/* Offset Registers */
#define OFSX 0x1E // R/W, X-axis offset.
#define OFSY 0x1F // R/W, Y-axis offset.
#define OFSZ 0x20 // R/W, Z-axis offset.

/* Activity Registers */
#define THRESH_ACT 0x24 // R/W, Activity threshold.
#define THRESH_INACT 0x25 // R/W, Inactivity threshold.
#define TIME_INACT 0x26 // R/W, Inactivity time.
#define ACT_INACT_CTL 0x27 // R/W, Axis enable control for activity and inactivity detection.

/* Free Fall Registers */
#define THRESH_FF 0x28 // R/W, Free-fall threshold.
#define TIME_FF 0x29 // R/W, Free-fall time.

/* Power Registers */ 
#define BW_RATE 0x2C // R/W, Data rate and power mode control.
#define POWER_CTL 0x2D // R/W, Power-saving features control.

/* Interrupt Registers */
#define INT_ENABLE 0x2E // R/W, Interrupt enable control.
#define INT_MAP 0x2F // R/W, Interrupt mapping control.
#define INT_SOURCE 0x30 // R, Source of interrupts.

/* Data Registers */ 
#define DATA_FORMAT 0x31 // R/W, Data format control.
#define DATAX0 0x32 // R, X-Axis Data 0.
#define DATAX1 0x33 // R, X-Axis Data 1.
#define DATAY0 0x34 // R, Y-Axis Data 0.
#define DATAY1 0x35 // R, Y-Axis Data 1.
#define DATAZ0 0x36 // R, Z-Axis Data 0.
#define DATAZ1 0x37 // R, Z-Axis Data 1.

/* FIFO Registers */
#define FIFO_CTL 0x38 // R/W, FIFO control.
#define FIFO_STATUS 0x39 // R, FIFO

#endif
    
/* [] END OF FILE */
