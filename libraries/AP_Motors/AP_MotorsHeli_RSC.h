// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_MOTORS_HELI_RSC_H__
#define __AP_MOTORS_HELI_RSC_H__

#include <AP_Common/AP_Common.h>
#include <AP_Math/AP_Math.h>            // ArduPilot Mega Vector/Matrix math Library
#include <RC_Channel/RC_Channel.h>      // RC Channel Library
#include <AC_PID/AC_PID.h>

// rotor controller states
enum RotorControlState {
    ROTOR_CONTROL_STOP = 0,
    ROTOR_CONTROL_IDLE,
    ROTOR_CONTROL_ACTIVE
};

// rotor control modes
enum RotorControlMode {
    ROTOR_CONTROL_MODE_DISABLED = 0,
    ROTOR_CONTROL_MODE_SPEED_PASSTHROUGH,
    ROTOR_CONTROL_MODE_SPEED_SETPOINT,
    ROTOR_CONTROL_MODE_OPEN_LOOP_POWER_OUTPUT,
    ROTOR_CONTROL_MODE_CLOSED_LOOP_POWER_OUTPUT
};

class AP_MotorsHeli_RSC {
public:
        AP_MotorsHeli_RSC(RC_Channel&   servo_output,
                          int8_t        servo_output_channel,
                          uint16_t      loop_rate,
                          AC_PID        *gov_pid = NULL):
        _servo_output(servo_output),
        _servo_output_channel(servo_output_channel),
        _loop_rate(loop_rate)
    {
        _gov_pid = gov_pid;
    };

    // init - initialization on start-up
    void        init();

    // set_control_mode - sets control mode
    void        set_control_mode(RotorControlMode mode) { _control_mode = mode; }

    // set_critical_speed
    void        set_critical_speed(int16_t critical_speed) { _critical_speed = critical_speed; }
    
    // get_critical_speed
    int16_t     get_critical_speed() const { return _critical_speed; }

    // set_idle_output
    void        set_idle_output(int16_t idle_output) { _idle_output = idle_output; }

    // get_desired_speed
    int16_t     get_desired_speed() const { return _desired_speed; }

    // set_desired_speed
    void        set_desired_speed(int16_t desired_speed) { _desired_speed = desired_speed; }

    // get_control_speed
    int16_t     get_control_output() const { return _control_output; }

    // get_rotor_speed - return estimated or measured rotor speed
    int16_t     get_rotor_speed() const;

    // is_runup_complete
    bool        is_runup_complete() const { return _runup_complete; }

    // set_ramp_time
    void        set_ramp_time(int8_t ramp_time) { _ramp_time = ramp_time; }

    // set_runup_time
    void        set_runup_time(int8_t runup_time) { _runup_time = runup_time; }

    // set_power_output_range
    void        set_power_output_range(uint16_t power_low, uint16_t power_high);

    // set_motor_load
    void        set_motor_load(float load) { _load_feedforward = load; }

    // set_gov_enable
    void        set_gov_enable(bool enabled, int16_t rpm, float rpm_feedback);

    // recalc_scalers
    void        recalc_scalers();

    // output - update value to send to ESC/Servo
    void        output(RotorControlState state);

private:

    // external variables
    RC_Channel&     _servo_output;
    int8_t          _servo_output_channel;      // output channel to rotor esc
    float           _loop_rate;                 // main loop rate
    AC_PID         *_gov_pid;                   // optional pointer to external PID object for speed governor

    // internal variables
    RotorControlMode _control_mode = ROTOR_CONTROL_MODE_DISABLED;   // motor control mode, Passthrough or Setpoint
    bool            _gov_enabled = false;       // status of speed governor
    int16_t         _critical_speed = 0;        // rotor speed below which flight is not possible
    int16_t         _idle_output = 0;           // motor output idle speed
    int16_t         _max_speed = 1000;          // rotor maximum speed. Placeholder value until we have measured speed input (ToDo)
    int16_t         _desired_speed = 0;         // latest desired rotor speed from pilot
    int16_t         _control_output = 0;        // latest logic controlled output
    int16_t         _governor_rpm_setpoint = 0; // governor rpm setpoint when rotor is engaged
    float           _rpm_feedback = 0;          // latest speed feedback from external tachometer sensor
    float           _rotor_ramp_output = 0;     // scalar used to ramp rotor speed between _rsc_idle_output and full speed (0.0-1.0f)
    float           _rotor_runup_output = 0;    // scalar used to store status of rotor run-up time (0.0-1.0f)
    float           _ramp_increment = 0;        // the amount to increase/decrease the rotor ramp scalar during each iteration
    int8_t          _ramp_time = 0;             // time in seconds for the output to the main rotor's ESC to reach full speed
    int8_t          _runup_time = 0;            // time in seconds for the main rotor to reach full speed.  Must be longer than _rsc_ramp_time
    float           _runup_increment = 0;       // the amount to increase/decrease the rotor run-up scalar during each iteration
    bool            _runup_complete = false;    // flag for determining if runup is complete
    uint16_t        _power_output_low = 0;      // setpoint for power output at minimum rotor power
    uint16_t        _power_output_high = 0;     // setpoint for power output at maximum rotor power
    uint16_t        _power_output_range = 0;    // maximum range of output power
    float           _load_feedforward = 0;      // estimate of motor load, range 0-1.0f

    // update_rotor_ramp - slews rotor output scalar between 0 and 1, outputs float scalar to _rotor_ramp_output
    void            update_rotor_ramp(float rotor_ramp_input);

    // update_rotor_runup - function to slew rotor runup scalar, outputs float scalar to _rotor_runup_ouptut
    void            update_rotor_runup();

    // write_rsc - outputs pwm onto output rsc channel. servo_out parameter is of the range 0 ~ 1000
    void            write_rsc(int16_t servo_out);

    // calc_open_loop_power_control_output - calculates control output for use in open loop mode, or as feedforward for closed loop mode
    int16_t         calc_open_loop_power_control_output();

    // calc_closed_loop_power_control_output - calculates control output for closed loop mode
    int16_t         calc_closed_loop_power_control_output();
};

#endif // AP_MOTORS_HELI_RSC_H
