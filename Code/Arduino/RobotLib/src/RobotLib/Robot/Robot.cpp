#include "RobotLib/Robot/Robot.hpp"
#include "RobotLib/Robot/Joint.hpp"

Robot::Robot(Joint* joints_, int size, Print &printer_):
    num_joints(size),
    printer(&printer_),
    joints(joints_)
    {
        joints = new Joint[size];
        positions = new float[size];
        velocities = new float[size];
        torques = new float[size];

        for (auto i = 0; i < size; i++){
            joints[i] = joints_[i];
            positions[i] = 0.0;
            velocities[i] = 0.0;
            torques[i] = 0.0;
        }
    }

Robot::~Robot()
{
    delete[] joints;
}

void Robot::update_joints(){
    for (auto i = 0; i < num_joints; i++){
        joints[i].update_pos_vel();
        positions[i]=joints[i].get_position();
        velocities[i]=joints[i].get_velocity();
    }
}

float* Robot::get_positions(){
    return positions;
}

float* Robot::get_velocities(){
    return velocities;
}

float Robot::get_position(int joint_ind_){
    if (joint_ind_ < num_joints){
        return joints[joint_ind_].get_position();
    }
    else{
        if(Serial){
            // printer->println("joint index out of bounds, providing 0 position");
        }
        return 0.0;
    }
}

float Robot::get_velocity(int joint_ind_){
    if (joint_ind_ < num_joints){
        return joints[joint_ind_].get_velocity();
    }
    else{
        if(Serial){
            // printer->println("joint index out of bounds, providing 0 velocity");
        }
        return 0.0;
    }
}

float* Robot::get_torques(){
    return torques;
}

void Robot::set_torques(float command_torques_[]){
    for (auto i = 0; i < num_joints; i++){
        torques[i] = command_torques_[i];
        joints[i].set_torque(torques[i]);
    }
}

void Robot::enable(){
    for (auto i = 0; i < num_joints; i++){
        joints[i].enable();
    }
    // if(Serial){
    //     printer->println("Robot enabled");
    // }
}

void Robot::disable(){
    for (auto i = 0; i < num_joints; i++){
        joints[i].disable();
    }
}

bool Robot::get_faults(){
    for (auto i = 0; i < num_joints; i++){
        if (joints[i].get_fault()){
            disable();
            return true;
        }
    }
    return false;
}