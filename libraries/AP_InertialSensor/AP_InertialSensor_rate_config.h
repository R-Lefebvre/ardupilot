#pragma once

#include <AP_HAL/AP_HAL_Boards.h>
#include <AP_InertialSensor/AP_InertialSensor_config.h>

// Enable fast rate loop support when harmonic notch is enabled
// This can be disabled by defining AP_INERTIALSENSOR_FAST_SAMPLE_WINDOW_ENABLED 0 in APM_Config.h
#ifndef AP_INERTIALSENSOR_FAST_SAMPLE_WINDOW_ENABLED
#if AP_INERTIALSENSOR_ENABLED && AP_INERTIALSENSOR_HARMONICNOTCH_ENABLED
#define AP_INERTIALSENSOR_FAST_SAMPLE_WINDOW_ENABLED 1
#else
#define AP_INERTIALSENSOR_FAST_SAMPLE_WINDOW_ENABLED 0
#endif
#endif
