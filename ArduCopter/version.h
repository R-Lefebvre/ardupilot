#pragma once

#include "ap_version.h"

#define THISFIRMWARE "ArduHeli V3.5.7-RL-DEV"
#define FIRMWARE_VERSION 3,5,6,FIRMWARE_VERSION_TYPE_OFFICIAL

#ifndef GIT_VERSION
#define FIRMWARE_STRING THISFIRMWARE
#else
#define FIRMWARE_STRING THISFIRMWARE " (" GIT_VERSION ")"
#endif
