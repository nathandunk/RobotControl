#include "Robot/Actuator.hpp"
#include "Arduino.h"

Actuator::Actuator(int actuator_en_, int fault_pin_, float motor_kt_, float max_torque_, float v_a_ratio_, int analog_out_pin_, int fault_level_, bool flip_dir_):
    motor_kt(motor_kt_),
    max_torque(max_torque_),
    v_a_ratio(v_a_ratio_),
    analog_out_pin(analog_out_pin_),
    torque(0.0),
    fault_pin(fault_pin_),
    fault_level(fault_level_),
    flip_dir(flip_dir_)
    {

    }

Actuator::~Actuator(){
    set_torque(0.0);
    enabled = false;
    disable();
}

void Actuator::enable(){
    digitalWrite(actuator_en, HIGH);
}

void Actuator::disable(){
    digitalWrite(actuator_en, LOW);
}

float Actuator::get_torque(){
    return torque;
}

void Actuator::set_torque(float torque_){
    if (enabled){
        if(flip_dir){
            torque = torque * -1.0;
        }
        torque = constrain(torque_,-1.0*max_torque,max_torque);
        float amps_out = torque/motor_kt; // Nm/(Nm/A) = A
        float volts_out = amps_out/v_a_ratio; // A/(V/A) = V
        int pwm_out = int(volts_out/5.0*255.0);
        analogWrite(analog_out_pin, pwm_out);
    }
    else{
        if(Serial){
            Serial.println("Joint is not enabled.");
        }
    }
}

bool Actuator::get_fault(){
    return (digitalRead(fault_pin) == fault_level);
}