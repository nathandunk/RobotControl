#include "RobotLib/Robot/Actuator.hpp"
#include "Arduino.h"

Actuator::Actuator(unsigned char actuator_en_, unsigned char current_pin_, unsigned char fault_pin_, unsigned char dir_pin_, float motor_kt_, float max_torque_, float v_a_ratio_, int analog_out_pin_, int fault_level_, bool flip_dir_, Print &printer_):
    motor_kt(motor_kt_),
    max_torque(max_torque_),
    v_a_ratio(v_a_ratio_),
    analog_out_pin(analog_out_pin_),
    torque(0.0),
    fault_pin(fault_pin_),
    fault_level(fault_level_),
    flip_dir(flip_dir_),
    dir_pin(dir_pin_),
    current_pin(current_pin_),
    actuator_en(actuator_en_),
    printer(&printer_)
    {
        pinMode(dir_pin,OUTPUT);
        pinMode(actuator_en, OUTPUT);
        pinMode(fault_pin, INPUT_PULLUP);
        pinMode(analog_out_pin, OUTPUT);
        pinMode(current_pin, INPUT);
        printer->println("HERE");
    }

Actuator::~Actuator(){
    enabled = false;
    disable();
}

void Actuator::enable(){
    digitalWrite(actuator_en, HIGH);
    enabled = true;
    set_torque(0.0);
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
            torque_ = torque_ * -1.0;
        }
        if (torque_ < 0){
            torque_ = -1.0 * torque_;
            digitalWrite(dir_pin, HIGH);
        }
        else{
            digitalWrite(dir_pin, LOW);
        }

        torque = constrain(torque_,-1.0*max_torque,max_torque);
        float amps_out = torque/motor_kt; // Nm/(Nm/A) = A
        float volts_out = amps_out/v_a_ratio; // A/(V/A) = V
        int pwm_out = int(volts_out/5.0*255.0);
        printer->println(pwm_out);
        analogWrite(analog_out_pin, abs(pwm_out));
    }
    else{
        if(Serial){
            printer->println("Joint is not enabled.");
        }
    }
}

bool Actuator::get_fault(){
    return (digitalRead(fault_pin) == fault_level);
}