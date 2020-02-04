#include "Encoder.h"
#include "DualTB9051FTGMotorShield.h"
#include "Control/PD_Controller.hpp"
#include "Robot/Joint.hpp"
#include "Control/Filter.hpp"
#include "Robot/Actuator.hpp"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Joint::Joint(PositionSensor* position_sensor_, Actuator* actuator_):
  // initialize variables
  position_sensor(position_sensor_),
  position(0.0),
  velocity(0.0),
  actuator(actuator_)
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