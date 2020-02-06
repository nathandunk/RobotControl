#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"

class Actuator
{
private:

    float motor_kt;
    float max_torque;
    float v_a_ratio;
    unsigned char analog_out_pin;
    float torque;
    unsigned char fault_pin;
    int fault_level;
    bool flip_dir;
    unsigned char dir_pin;
    unsigned char current_pin;
    int actuator_en;
    bool enabled;
    Print *printer;
    
public:
    Actuator(unsigned char actuator_en_, unsigned char current_pin_, unsigned char fault_pin_, unsigned char dir_pin_, float motor_kt_, float max_torque_, float v_a_ratio_, int analog_out_pin_, int fault_level_, bool flip_dir_, Print &printer_);

    ~Actuator();

    void set_torque(float torque_);

    void enable();

    void disable();

    float get_torque();

    bool get_fault();
    
};

#endif