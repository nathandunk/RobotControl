#include "Encoder.h"
#include "DualTB9051FTGMotorShield.h"
#include "RobotLib/Control/PD_Controller.hpp"
#include "RobotLib/Robot/Joint.hpp"
#include "RobotLib/Control/Filter.hpp"
#include "RobotLib/Robot/Actuator.hpp"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Joint::Joint(PositionSensor &position_sensor_, Actuator &actuator_, Print &printer_):
  // initialize variables
  position_sensor(&position_sensor_),
  actuator(&actuator_),
  position(0.0),
  velocity(0.0),
  printer(&printer_)
  {

  };

  void Joint::enable(){
    actuator->enable();
  }

  void Joint::disable(){
    actuator->disable();
  }

  void Joint::update_pos_vel(){
    position_sensor->update();
    position = position_sensor->get_position();
    velocity = position_sensor->get_velocity();
  }

  float Joint::get_position(){
    return position_sensor->get_position();
  }

  float Joint::get_velocity(){
    return position_sensor->get_velocity();
  }

  void Joint::set_torque(float torque_){
    actuator->set_torque(torque_);
  }

  bool Joint::get_fault(){
    return actuator->get_fault();
  }

  void Joint::print_test(){
    // printer->println("test");
  }