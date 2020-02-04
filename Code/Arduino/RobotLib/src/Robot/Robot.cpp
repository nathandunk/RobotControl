#include "Robot/Robot.hpp"
#include "Robot/Joint.hpp"

Robot::Robot(Joint* joints_[], int num_joints_):
    num_joints(num_joints_)
    {
        for (size_t i = 0; i < num_joints; i++){
            joints[i] = joints_[i];
            positions[i] = 0.0;
            velocities[i] = 0.0;
            torques[i] = 0.0;
        }
    }

Robot::~Robot()
{
}

void Robot::update_joints(){
    for (size_t i = 0; i < num_joints; i++){
        joints[i]->update_pos_vel();
        positions[i]=joints[i]->get_position();
        velocities[i]=joints[i]->get_velocity();
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
        return joints[joint_ind_]->get_position();
    }
    else{
        if(Serial){
            Serial.println("joint index out of bounds, providing 0 position");
        }
        return 0.0;
    }
}

float Robot::get_velocity(int joint_ind_){
    if (joint_ind_ < num_joints){
        return joints[joint_ind_]->get_velocity();
    }
    else{
        if(Serial){
            Serial.println("joint index out of bounds, providing 0 velocity");
        }
        return 0.0;
    }
}

float* Robot::get_torques(){
    return torques;
}

void Robot::set_torques(float command_torques_[]){
    for (size_t i = 0; i < num_joints; i++){
        torques[i] = command_torques_[i];
        joints[i]->set_torque(torques[i]);
    }
}

void Robot::disable(){
    for (size_t i = 0; i < num_joints; i++){
        joints[i]->disable();
    }
}

bool Robot::get_faults(){
    for (size_t i = 0; i < num_joints; i++){
        if (joints[i]->get_fault()){
            disable();
            return true;
        }
    }
    return false;
}