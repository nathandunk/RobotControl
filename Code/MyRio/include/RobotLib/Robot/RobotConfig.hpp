#ifndef RobotConfig_h
#define RobotConfig_h

#include <array>

std::array<unsigned char,2>  actuator_ens    = {4, 5};
std::array<unsigned char,2>  current_pins    = {A0, A1};
std::array<unsigned char,2>  fault_pins      = {12, 6};
std::array<unsigned char,2>  dir_pins        = {8, 7};
std::array<float,2>          motor_kts       = {0.6/2.1, 0.6/2.1};
std::array<float,2>          max_torques     = {1.0, 1.0};
std::array<float,2>          v_a_ratio       = {1.0, 1.0};
std::array<unsigned char,2>  analog_out_pins = {10, 9};
std::array<int,2>            fault_levels    = {0, 0};
std::array<bool,2>           flip_dirs       = {false, false};

// // PositionSensor variables
// // PositionSensor *positionsensors[n_joints];
unsigned char encoder_pins[n_joints][2] = {{2, 3},{18, 19}};
float         encoder_cprs[n_joints]    = {2248.8576, 2248.8576};

#endif