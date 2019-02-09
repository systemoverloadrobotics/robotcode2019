#pragma once
#include <stdint.h>
#include "CANAPITypes.h"
#include "hal/Types.h"


HAL_CANHandle HAL_InitializeCAN(HAL_CANManufacturer 1, int32_t 0, HAL_CANDeviceType 1);

void HAL_CleanCan(Hal_CANHandle TalonSRX);

void RepeatedRead(){

while (HAL_ReadCANPacketTimeout() = error){

void HAL_ReadCANPacketNew(HAL_CANHandle HAL_m_Encoder1Handle, int32_t 0, uint8_t* 8, 
int32_t* 1, uint64_t* recievedTimestamp, int32_t* status)

}

else {
    
void HAL_ReadCANPacketTimeout(HAL_CANHandle HAL_m_Encoder1Handle, int32_t 0, 
uint8_t* 8, int32_t* 1, uint64_t* recievedTimestamp, int32_t 1000, int32_t* status);

}

}








