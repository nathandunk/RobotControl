#ifndef Robot_h
#define Robot_h

#include "Arduino.h"
#include "RobotLib/Robot/Joint.hpp"

class Robot
{
    public:
        Robot(Joint joints_[], int num_joints_, Print &printer_);
        ~Robot();

        void update_joints();

        float* get_positions();
        
        float* get_velocities();

        float* get_torques();

        bool get_faults();

        float get_position(int joint_ind_);

        float get_velocity(int joint_ind_);

        void set_torques(float command_torques_[]);

        void enable();

        void disable();
    private:
        Joint joints[];
        int num_joints;
        float positions[];
        float velocities[];
        float torques[];
        Print *printer;
};

#endif