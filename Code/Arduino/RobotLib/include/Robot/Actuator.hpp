#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"

class Actuator
{
public:
    enum LogicLevel{
        low,
        high
    };
    Actuator(int actuator_en_, int fault_pin_, float motor_kt_, float max_torque_, float v_a_ratio_, int analog_out_pin_, int fault_level_, bool flip_dir_);

    ~Actuator();

    void set_torque(float torque_);

    void enable();

    void disable();

    float get_torque();

    bool get_fault();
    
private:

    float motor_kt;
    float v_a_ratio;
    int analog_out_pin;
    float max_torque;
    float torque;
    int actuator_en;
    bool enabled;
    int fault_pin;
    int fault_level;
    bool flip_dir;
};

#endif