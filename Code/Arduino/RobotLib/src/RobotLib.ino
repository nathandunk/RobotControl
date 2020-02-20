#include "Arduino.h"
#include "RobotLib/Robot/Actuator.hpp"
#include "RobotLib/Robot/Robot.hpp"
#include "RobotLib/Control/PD_Controller.hpp"
#include "RobotLib/Control/Filter.hpp"
#include "RobotLib/Utility/Timer.hpp"
// #include "Plotter.h"

float angles[2];
char buff[sizeof(angles)];

float positions[2] = {0.0, 0.0};

const int n_joints = 2;

// // Actuator variables
// // Actuator *actuators[n_joints];
unsigned char actuator_ens[]    = {4, 5};
unsigned char current_pins[]    = {A1, A0};
unsigned char fault_pins[]      = {12, 6};
unsigned char dir_pins[]        = {8, 7};
float         motor_kts[]       = {0.6/2.1, 0.6/2.1};
float         max_torques[]     = {1.0, 1.0};
float         v_a_ratio[]       = {1.0, 1.0};
unsigned char analog_out_pins[] = {10, 9};
int           fault_levels[]    = {0, 0};
bool          flip_dirs[]       = {false, false};

// // PositionSensor variables
// // PositionSensor *positionsensors[n_joints];
unsigned char encoder_pins[n_joints][2] = {{2, 3},{18, 19}};
float         encoder_cprs[n_joints]    = {2248.8576, 2248.8576};

// // Joint variables
// // Joint *joints[n_joints];

// // PD Controller Variables
// // PD_Controller *pd_controllers[n_joints];
float p_vals[]      = {0.01, 0.01};
float d_vals[]      = {0.002, 0.002};
float pd_flip_dir[] = {true, true};

float ref[n_joints]             = {0.0, 0.0};
float command_torques[n_joints] = {0.0, 0.0};

Timer timer(0.005, Serial);

float current_time = 0.0;

bool stop = false;

// // Robot* robot;
// Robot robot;

Actuator actuators[] = {Actuator(actuator_ens[0], current_pins[0],fault_pins[0],dir_pins[0],motor_kts[0],max_torques[0],v_a_ratio[0],analog_out_pins[0],fault_levels[0],flip_dirs[0],Serial),Actuator(actuator_ens[1], current_pins[1],fault_pins[1],dir_pins[1],motor_kts[1],max_torques[1],v_a_ratio[1],analog_out_pins[1],fault_levels[1],flip_dirs[1],Serial)};

PositionSensor positionsensors[] = {PositionSensor(encoder_pins[0],encoder_cprs[0],Serial),PositionSensor(encoder_pins[1],encoder_cprs[1],Serial)};

Joint joints[] = {Joint(positionsensors[0],actuators[0],Serial),Joint(positionsensors[1],actuators[1],Serial)};

PD_Controller pd_controllers[] = {PD_Controller(p_vals[0],d_vals[0],pd_flip_dir[0]),PD_Controller(p_vals[1],d_vals[1],pd_flip_dir[1])};

Robot robot(joints, n_joints, Serial);

double pos;
// Plotter p;

void setup(){

    // p.Begin();
    // p.AddTimeGraph( "Position vs time", 500, "position", pos );

    // for (size_t i = 0; i < n_joints; i++){
    //     actuators[i] = new Actuator(actuator_ens[i], 
    //                                 current_pins[i],
    //                                 fault_pins[i],
    //                                 dir_pins[i],
    //                                 motor_kts[i],
    //                                 max_torques[i],
    //                                 v_a_ratio[i],
    //                                 analog_out_pins[i],
    //                                 fault_levels[i],
    //                                 flip_dirs[i]);
    // }

    // for (size_t i = 0; i < n_joints; i++){
    //     positionsensors[i] = new PositionSensor(encoder_pins[i], 
    //                                             encoder_cprs[i]);
    // }

    // for (size_t i = 0; i < n_joints; i++){
    //     joints[i] = new Joint(positionsensors[i], 
    //                           actuators[i]);
    // }

    // for (size_t i = 0; i < n_joints; i++){
    //     pd_controllers[i] = new PD_Controller(p_vals[i],
    //                                           d_vals[i],
    //                                           pd_flip_dir[i]);
    // }

    Serial.begin(9600);
    Serial.println("Serial open");

    robot.enable();

    timer.start();
}

void loop(){
    while(!stop){
        if(Serial.available() != 0){
            Serial.readBytes(buff,sizeof(angles)); // read the input
            memcpy(&angles[0],&buff[0],sizeof(angles));
            ref[0] = angles[0];
            ref[1] = angles[1];
            
            positions[0] = robot.get_position(0);
            positions[1] = robot.get_position(1);
            Serial.write((char *)&positions[0],sizeof(positions));
        }

        robot.update_joints();

        for (size_t i = 0; i < n_joints; i++){
            command_torques[i] = 1.0*pd_controllers[i].CalcTorque(robot.get_position(i),robot.get_velocity(i),ref[i],0.0);
        }

        robot.set_torques(command_torques);

        current_time = timer.wait();      
    }
    while(true){
        if(Serial){
            Serial.println("Code has ended");
        }
    }
}