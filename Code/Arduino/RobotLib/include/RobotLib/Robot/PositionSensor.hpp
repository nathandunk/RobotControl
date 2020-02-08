#ifndef PositionSensor_h
#define PositionSensor_h

#include "Encoder.h"
#include "RobotLib/Control/Filter.hpp"

class PositionSensor{
    
    public:
        PositionSensor(unsigned char encoder_pins[], float encoder_cpr_, Print &printer_);

        void update();
        
        void update_position();
        
        void update_velocity();

        float get_position();
        
        float get_velocity();

        bool get_faults();
    private:
        unsigned char encoder_a;
        unsigned char encoder_b; 
        float encoder_cpr;
        float position;
        float last_position;
        float velocity;
        unsigned long int last_time;
        Encoder encoder;
        FilterBuLp2 filter;
        Print *printer;
};

#endif