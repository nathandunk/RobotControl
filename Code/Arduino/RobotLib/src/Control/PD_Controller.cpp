#include "Control/PD_Controller.hpp"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

PD_Controller::PD_Controller(float kp_, float kd_, bool flip_dir_):
  kp(kp_),
  kd(kd_),
  flip_dir(flip_dir_)
  {
  }

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

float PD_Controller::CalcTorque(float pos, float vel, float pos_d, float vel_d)
{
  float pos_error = pos-pos_d;
  float vel_error = vel-vel_d;
  if (flip_dir){
    return -1.0 * (kp*pos_error + kd*vel_error);
  }
  return (kp*pos_error + kd*vel_error);
}