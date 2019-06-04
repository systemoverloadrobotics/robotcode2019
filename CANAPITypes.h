#pragma once
#include <stdint.h>
#include "hal/Types.h"
#include <frc/TimedRobot.h>

class CAN : public frc::TimedRobot {

HAL_ENUM(HAL_DeviceType) {
HAL_CAN_Dev_kTalonSRX = 1;
HAL_CAN_Dev_kVictorSPX = 2;
HAL_CAN_Dev_kEncoder1 = 3;
HAL_CAN_Dev_kEncoder2 = 4;
};


HAL_ENUM(HAL_CANMaunfacturer) {
HAL_CAN_Man_kTeamUse = 1;
};

}