/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-02-18
 *
 * File Name: 
 *      adxl345_driver.h
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

/* Multiple inclusion protection. See: austin_debug.h */
#ifndef ADXL_345_DRIVER_H
#define ADXL_345_DRIVER_H

#include "project.h"               // For type definitions, etc.
#include "adxl345_registers.h"     // Datasheet macros
#include "adxl345_i2c_addresses.h" // Datasheet macros
#include "accelerometer_driver.h"  // ADXL345 *is an* accelerometer
#include <stdio.h>                 // For sprintf

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

#define SHANK_ACCELEROMETER_ADDRESS DEFAULT_ADDRESS
#define THIGH_ACCELEROMETER_ADDRESS ALTERNATE_ADDRESS

//==================== ADXL345_VirtualFunctionTable Structure =================
typedef void (*Read)(ADXL345 Base);
typedef void (*Write)(ADXL345 Base);
// Define the type "struct <tag>" as type "<tag>"
typedef struct ADXL345_VirtualFunctionTable ADXL345_VirtualFunctionTable;
struct ADXL345_VirtualFunctionTable
{
    Read Read_FunctionPointer;
    Write Write_FunctionPointer;
};

//========================= ADXL345 Structure =================================
// Define the type "struct <tag>" as type "<tag>"
typedef struct ADXL345 ADXL345;
struct ADXL345
{
    ADXL345_VirtualFunctionTable VirtualFunctionTable;
    Accelerometer Base;
    uint8 I2C_Address;
    uint8 ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
    uint8 WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];
};

void ADXL345_Constructor(ADXL345 *me);

void ADXL345_ReadDataRegisters(ADXL345 *me);
void ADXL345_WriteConfigRegister(ADXL345 *me, const uint8 ConfigRegisterAddress, uint8 ByteToWrite);
void ADXL345_InitializeConfigRegisters(ADXL345 *me);
void ADXL345_CalculateCurrentAcceleration(ADXL345 *me);
int16 ADXL345_CalculateComponentMagnitude(uint8 DataRegister0, uint8 DataRegister1);

#endif
/* [] END OF FILE */
