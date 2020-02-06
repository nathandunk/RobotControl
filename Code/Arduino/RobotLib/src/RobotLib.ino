#include "Arduino.h"
#include "RobotLib/Robot/Actuator.hpp"
#include "RobotLib/Robot/Robot.hpp"
#include "RobotLib/Control/PD_Controller.hpp"
#include "RobotLib/Control/Filter.hpp"
#include "RobotLib/Utility/Timer.hpp"

const int n_joints = 2;

// // Actuator variables
// // Actuator *actuators[n_joints];
unsigned char actuator_ens[]    = {5, 4};
unsigned char current_pins[]    = {A0, A1};
unsigned char fault_pins[]      = {6, 12};
unsigned char dir_pins[]        = {7, 8};
float         motor_kts[]       = {0.6/2.1, 0.6/2.1};
float         max_torques[]     = {1.0, 1.0};
float         v_a_ratio[]       = {1.0, 1.0};
unsigned char analog_out_pins[] = {9, 10};
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
float p_vals[]      = {0.01,  0.01};
float d_vals[]      = {0.001, 0.001};
float pd_flip_dir[] = {false, false};

float ref[n_joints]             = {0.0, 0.0};
float command_torques[n_joints] = {0.0, 0.0};

Timer timer(0.002);

float current_time = 0.0;

bool stop = false;

// // Robot* robot;
// Robot robot;

Actuator actuators[] = {Actuator(actuator_ens[0], current_pins[0],fault_pins[0],dir_pins[0],motor_kts[0],max_torques[0],v_a_ratio[0],analog_out_pins[0],fault_levels[0],flip_dirs[0],Serial),Actuator(actuator_ens[1], current_pins[1],fault_pins[1],dir_pins[1],motor_kts[1],max_torques[1],v_a_ratio[1],analog_out_pins[1],fault_levels[1],flip_dirs[1],Serial)};

PositionSensor positionsensors[] = {PositionSensor(encoder_pins[0],encoder_cprs[0]),PositionSensor(encoder_pins[1],encoder_cprs[1])};

Joint joints[] = {Joint(positionsensors[0],actuators[0],Serial),Joint(positionsensors[1],actuators[1],Serial)};

PD_Controller pd_controllers[] = {PD_Controller(p_vals[0],d_vals[0],pd_flip_dir[0]),PD_Controller(p_vals[1],d_vals[1],pd_flip_dir[1])};

Robot robot(joints, n_joints, Serial);

void setup(){

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

    // robot.enable();
    // robot.set_torques(command_torques);
    // actuators[0].set_torque(0.0);

    // timer.start();

    // pinMode(5, OUTPUT);
    // pinMode(4, OUTPUT);
    // pinMode(7, OUTPUT);
    // pinMode(9, OUTPUT);
    // pinMode(6, INPUT_PULLUP);
    // pinMode(A0, INPUT);
    // pinMode(7, OUTPUT);
    // pinMode(10, OUTPUT);
    // pinMode(12, INPUT_PULLUP);
    // pinMode(A1, INPUT);

    // digitalWrite(5,HIGH);
    // digitalWrite(4,HIGH);
    joints[0].enable();
    joints[1].enable();
}

void loop(){
    // while(!stop){
        // robot.update_joints();
        // // Serial.println(robot.get_position(0));

        // ref[0] = 50*sin(0.5*2*PI*current_time/1000000.0);
        // ref[1] = 50*cos(0.5*2*PI*current_time/1000000.0);

        // for (size_t i = 0; i < n_joints; i++){
        //     command_torques[i] = pd_controllers[i].CalcTorque(robot.get_position(i),robot.get_velocity(i),ref[i],0.0);
        // }
        // command_torques[0] = 0.0;
        // command_torques[1] = 0.0;
        // // robot.set_torques(command_torques);

        // if(robot.get_faults()){
            // if (Serial){
                // Serial.println("There was a fault, closing program");
            // }
            // stop = true;
        // }

        // current_time = timer.wait();
        
    // }
    // while(true){
    //     if(Serial){
    //         Serial.println("Code has ended");
    //     }
    // }
    actuators[0].set_torque(0.1);
    actuators[1].set_torque(0.1);
    // analogWrite(9,50);
    // analogWrite(10,50);
}

// #include <Encoder.h>
// #include "RobotLib/Control/PD_Controller.hpp"
// // #include <PD_Controller.h>
// #include <Filter.hpp>
// #include <DualTB9051FTGMotorShield.h>

// Encoder myEnc(2, 3);
// float position1 = 0.0;
// float velocity1 = 0.0;
// float pos_last = 0.0;
// float torque1   = 0.0;
// PD_Controller pd(8, 0.01, -1);
// float ref1 = 0.0;

// FilterBuLp2 filter;

// unsigned char M1EN   = 5;
// unsigned char M1DIR  = 7;
// unsigned char M1PWM  = 9;
// unsigned char M1DIAG = 6;
// unsigned char M1OCM  = A0;
// unsigned char M2EN   = 4;
// unsigned char M2DIR  = 8;
// unsigned char M2PWM  = 10;
// unsigned char M2DIAG = 12;
// unsigned char M2OCM  = A1;

// DualTB9051FTGMotorShield driver(M1EN, M1DIR, M1PWM, M1DIAG, M1OCM, M2EN, M2DIR, M2PWM, M2DIAG, M2OCM);

// unsigned long last_us = 0L;
// unsigned long last_move_time = 0L;
// int period = 2000; // microseconds

// bool plotting = true;

// void stopIfFault() {
//   if (driver.getM1Fault())
//   {
//     Serial.println("M1 fault");
//     driver.disableDrivers();
//     while (1);
//   }
//   if (driver.getM2Fault())
//   {
//     Serial.println("M2 fault");
//     driver.disableDrivers();
//     while (1);
//   }
// }

// void setup() {
//    Serial.begin(9600);
//    driver.init();
//    driver.enableDrivers();
//    delay(1);
// }

// void loop() {
//   position1 = myEnc.read()/2248.86*360;
//   if (micros () - last_us > period){
//     velocity1 = (position1-pos_last)/float(micros()-last_us)*1000000.0;
    
//     velocity1 = filter.step(velocity1);
    
//     ref1 = 50*sin(0.5*2*PI*last_us/1000000.0);
//     torque1 = pd.CalcTorque(position1, velocity1, ref1, 0.0);
//     torque1 = constrain(torque1,-100.0,100.0);
//     if(abs(torque1) < 10 && abs(velocity1) < 5){
//       driver.setM2Speed(0);      
//     }
//     else{
//     //   driver.setM2Speed(-1*int(torque1)); 
//         if(torque1 < 0){
//             digitalWrite(M2DIR, HIGH);
//             torque1 = torque1*-1.0;
//         }
//         else{
//             digitalWrite(M2DIR,LOW);
//         }
//         analogWrite(M2PWM,int(torque1));
//     }
    
//     stopIfFault();
    
//     pos_last  = position1;
//     last_us = micros();
//   }
//   else{
//     if(!plotting){
//       Serial.println(micros () - last_us);
//     }
//   }
//   if(plotting){
//     Serial.print(position1);
//     Serial.print(" ");
//     Serial.print(velocity1);
//     Serial.print(" ");
//     Serial.print(torque1);
//     Serial.print(" ");
//     Serial.println(ref1);
//   }
// }