// ArduCopter Lightweight FPV Configuration
// Optimized for simple FPV quadcopter flying only
//
// IMPORTANT: Hardware feature gates (HAL_*_ENABLED, AP_*_ENABLED)
// are defined in hwdef.dat, NOT here. See:
//   libraries/AP_HAL_ChibiOS/hwdef/ARK_FPV/hwdef.dat
//
// This file contains ONLY application-level flight mode disables.

// ============================================================================
// FLIGHT MODES - Disable unnecessary modes
// Keep enabled: Stabilize, AltHold, Loiter, RTL, Auto, Land, Brake, Guided
// ============================================================================
#define MODE_POSHOLD_ENABLED          0
#define MODE_SPORT_ENABLED            0
#define MODE_DRIFT_ENABLED            0
#define MODE_FLIP_ENABLED             0
#define MODE_ZIGZAG_ENABLED           0
#define MODE_FLOWHOLD_ENABLED         0
#define MODE_SYSTEMID_ENABLED         0
#define MODE_TURTLE_ENABLED           0
#define MODE_CIRCLE_ENABLED           0
#define MODE_FOLLOW_ENABLED           0
#define MODE_AVOID_ADSB_ENABLED       0
#define MODE_ACRO_HELI_ENABLED        0
#define MODE_AUTOROTATE_ENABLED       0
#define MODE_AUTOTUNE_ENABLED         0
#define MODE_GUIDED_CUSTOM_ENABLED    0
#define MODE_GUIDED_NOGPS_ENABLED     0
#define MODE_SMART_RTL_ENABLED        0
#define MODE_STABILIZE_HELI_ENABLED   0
#define TOY_MODE_ENABLED              0

// Circle mode is required by Auto mode, so we must keep it enabled
#undef MODE_CIRCLE_ENABLED
#define MODE_CIRCLE_ENABLED           1

// ============================================================================
// Safety overrides for camera, external AHRS, notifications, OA (compile gates)
// These are handled in hwdef.dat for proper include ordering
// See: libraries/AP_HAL_ChibiOS/hwdef/ARK_FPV/hwdef.dat
