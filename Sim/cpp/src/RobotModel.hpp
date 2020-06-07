#include <Mahi/Robo.hpp>
#include <Mahi/Util.hpp>
#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Matrix3d;

class RobotModel{
public:
    // stores the state of the robot
    struct State{
        Vector3d Q;   // current position of the robot
        Vector3d Qd;  // current velocities of the robot
        Vector3d Qdd; // current accelerations of the robot
        Vector3d Tau; // current torque outputs of the robot
    };

    State m_s{Vector3d(0,0,0), Vector3d(0,0,0), Vector3d(0,0,0), Vector3d(0,0,0)}; // stores robot state

    /// Constructor
    RobotModel();
    /// sets the zero conditions of the robot
    void zero();
    /// runs one iteration of the update rule, integrating forward in time
    void update(double dt);
    /// integrates the state of the robot according to the latest dt
    void integrate_state(Vector3d Qdd, double dt);
private:
    /// returns the mass matrix for the robot given the robot state
    Matrix3d M();
    /// returns the vector of centrifugal and coriolis terms given the robot state
    Vector3d V();
    /// returns the vector of gravity terms given the robot state
    Vector3d G();
    /// returns the vector of damping terms given the robot state
    Vector3d B();
    /// returns the vector of friction terms given the robot state
    Vector3d Fk();
};