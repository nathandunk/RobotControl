#include "Robot/PositionSensor.hpp"
#include "Encoder.h"

PositionSensor::PositionSensor(int encoder_pins[], float encoder_cpr_):
    encoder_a(encoder_pins[0]),
    encoder_b(encoder_pins[1]),
    encoder_cpr(encoder_cpr_),
    position(0.0),
    last_position(0.0),
    velocity(0.0),
    last_time(0.0),
    encoder(encoder_a,encoder_b),
    filter()
    {
        
    }

void PositionSensor::update(){
    update_position();
    update_velocity();
}

void PositionSensor::update_position(){
    encoder.read()/encoder_cpr*360;
}

void PositionSensor::update_velocity(){
    int current_time = micros();
    velocity = (position-last_position)/float(current_time-last_time)*1000000.0;
    velocity = filter.step(velocity);
    last_time = current_time;
}

float PositionSensor::get_position(){
    return position;
}

float PositionSensor::get_velocity(){
    return velocity;
}