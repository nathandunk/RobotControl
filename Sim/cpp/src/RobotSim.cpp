#include <RobotModel.hpp>
#include <Mahi/Util.hpp>
#include <thread>
#include <atomic>
#include <mutex>

#define DLL_EXPORT extern "C" __declspec(dllexport)

using namespace mahi::util;

RobotModel rob;
std::atomic_bool stop_;
double t;
double t_last;
Vector3d Qref(0,0,0);
Vector3d Kp(0.1,0.1,0.1);
Vector3d Kd(0.001,0.001,0.001);
std::thread sim_thread;

void sim(){
    Timer sim_loop(1_ms);
    {
        while(!stop_){
            {
                std::mutex lock;
                rob.m_s.Tau = Kp.asDiagonal()*(Qref-rob.m_s.Q)-Kd.asDiagonal()*rob.m_s.Qd;
                rob.update(0.001);
            }
            t_last = t;
            t = sim_loop.wait().as_seconds();
        }
    }
}

DLL_EXPORT void start(){
    {
        std::mutex lock;
        rob.zero();
        stop_ = false;
    }
    sim_thread = std::thread(sim);
}

DLL_EXPORT void stop(){
    {
        std::mutex lock;
        stop_ = true;
    }
    sim_thread.join();
}

DLL_EXPORT void get_Q(double* Q){
    std::mutex lock;
    for (size_t i = 0; i < 3; i++)
    {
        Q[i] = rob.m_s.Q[i];
    } 
}

DLL_EXPORT void set_Tau(double* Tau){
    std::mutex lock;
    for (size_t i = 0; i < 3; i++)
    {
        rob.m_s.Tau[i] = Tau[i];
    } 
}

DLL_EXPORT void set_Qref(double* Qref_){
    std::mutex lock;
    for (size_t i = 0; i < 3; i++)
    {
        Qref[i] = Qref_[i];
    } 
}