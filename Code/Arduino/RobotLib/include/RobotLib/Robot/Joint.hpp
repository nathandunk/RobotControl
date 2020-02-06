// ensure this library description is only included once
#ifndef Joint_h
#define Joint_h

#include "Encoder.h"
#include "DualTB9051FTGMotorShield.h"
#include "RobotLib/Robot/PositionSensor.hpp"
#include "RobotLib/Robot/Actuator.hpp"

// library interface description
class Joint
{
  // user-accessible "public" interface
  public:
    Joint(PositionSensor &position_sensor_, Actuator &actuator_, Print &printer_);

    void enable();

    void disable();

    void set_torque(float torque_);

    float get_position();

    float get_velocity();

    void update_pos_vel();

    bool get_fault();

  // library-accessible "private" interface
  private:
    PositionSensor position_sensor;
    Actuator actuator;
    double position;
    double velocity;
    Print *printer;
};

#endif