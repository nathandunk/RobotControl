#include "Arduino.h"
#include "RobotLib/Robot/Actuator.hpp"
#include "RobotLib/Robot/Robot.hpp"
#include "RobotLib/Control/PD_Controller.hpp"
#include "RobotLib/Control/Filter.hpp"
#include "RobotLib/Utility/Timer.hpp"

const int n_joints = 2;

// Actuator variables
Actuator *actuators[n_joints];
int actuator_ens[] = {5, 4};
int fault_pins[] = {6,12};
int fault_levels[] = {0, 0};
float motor_kts[] = {0.6/2.1, 0.6/2.1};
float max_torques[] = {1.0, 1.0};
float v_a_ratio[] = {1.0, 1.0};
int analog_out_pins[] = {9, 10};
bool flip_dirs[] = {false, false};

// PositionSensor variables
PositionSensor *positionsensors[n_joints];
int encoder_pins[n_joints][2] = {{2,3},{18,19}};
float encoder_cprs[n_joints] = {2248.8576, 2248.8576};

// Joint variables
Joint *joints[n_joints];

// PD Controller Variables
PD_Controller *pd_controllers[n_joints];
float p_vals[] = {0.01,  0.01};
float d_vals[] = {0.001, 0.001};
float pd_flip_dir[] = {false, false};

float ref[n_joints] = {0.0, 0.0};
float command_torques[n_joints] = {0.0, 0.0};

Timer timer(0.002);

float current_time = 0.0;

bool stop = false;

Robot* robot;

void setup(){

    for (size_t i = 0; i < n_joints; i++){
        positionsensors[i] = new PositionSensor(encoder_pins[i], 
                                            encoder_cprs[i]);
    }

    for (size_t i = 0; i < n_joints; i++){
        joints[i] = new Joint(positionsensors[i], 
                          actuators[i]);
    }

    for (size_t i = 0; i < n_joints; i++){
        pd_controllers[i] = new PD_Controller(p_vals[i],
                                          d_vals[i],
                                          pd_flip_dir[i]);
    }

    robot = new Robot(joints, n_joints);

    timer.start();

    Serial.begin(115200);
}

void loop(){
    while(!stop){
        robot->update_joints();

        ref[0] = 50*sin(0.5*2*PI*current_time/1000000.0);
        ref[1] = 50*cos(0.5*2*PI*current_time/1000000.0);

        for (size_t i = 0; i < n_joints; i++){
            command_torques[i] = pd_controllers[i]->CalcTorque(robot->get_position(i),robot->get_velocity(i),ref[i],0.0);
        }

        robot->set_torques(command_torques);

        if(robot->get_faults()){
            if (Serial){
                Serial.println("There was a fault, closing program");
            }
            stop = true;
        }

        current_time = timer.wait();
    }
    while(true){
        if(Serial){
            Serial.println("Code has ended");
        }
    }
}