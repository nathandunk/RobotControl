#include "Utility/Timer.hpp"
#include "arduino.h"

Timer::Timer(float period_):
    period(period_),
    last_time_micros(0),
    current_time_micros(0),
    start_time_micros(0)
{
    period_micros = period*1000000.0;
}

Timer::~Timer()
{
}

void Timer::start(){
    start_time_micros = micros();
    last_time_micros = start_time_micros;
}

float Timer::wait(){
    current_time_micros = micros();
    bool waiting = true;
    while(waiting){
        if ((current_time_micros - last_time_micros) > period_micros){
            waiting = false;
            last_time_micros = current_time_micros;
        }
    }
    return current_time_micros / 1000000.0;
}