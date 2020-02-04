#ifndef PositionSensor_h
#define PositionSensor_h

#include "Encoder.h"
#include "Control/Filter.hpp"

class PositionSensor{
    
    public:
        PositionSensor(int encoder_pins[], float encoder_cpr_);

        void update();
        
        void update_position();
        
        void update_velocity();

        float get_position();
        
        float get_velocity();

        bool get_faults();
    private:
        int encoder_a;
        int encoder_b; 
        float encoder_cpr;
        float position;
        float last_position;
        float velocity;
        int last_time;
        Encoder encoder;
        FilterBuLp2 filter;
};

#endif