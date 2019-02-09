#pragma once
#include <stdint.h>
#define HAL_kInvalidHandle 0

typedef int32_t HAL_Handle;
typedef HAL_Handle HAL_TalonSRXHandle;
typedef HAL_Handle HAL_VictorSPXHandle;
typedef HAL_Handle HAL_m_Encoder1Handle;
typedef HAL_Handle HAL_m_Encoder2Handle;
typedef HAL_Handle HAL_AnalogInputHandle;
typedef HAL_Handle HAL_CANHandle;
typedef int32_t HAL_Bool;


#ifdef __cplusplus
#define HAL_ENUM(name) enum name : int32_t
#else
#define HAL_ENUM(name)  
    typedef int32_t name; 
    enum name
    #endif