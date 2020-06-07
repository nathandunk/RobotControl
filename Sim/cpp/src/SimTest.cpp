#include <RobotModel.hpp>
#include <Mahi/Util.hpp>
#include <thread>
#include <atomic>
#include <mutex>

using namespace mahi::util;

RobotModel rob;
std::atomic_bool stop_;
double t_last;
double t;
std::thread sim_thread;

void stop(){
    {
        std::mutex lock;
        stop_ = true;
    }
    sim_thread.join();
}

void get_Q(double* Q){
    std::mutex lock;
    for (size_t i = 0; i < 3; i++)
    {
        Q[i] = rob.m_s.Q[i];
    } 
}

void set_Tau(double* Tau){
    std::mutex lock;
    for (size_t i = 0; i < 3; i++)
    {
        rob.m_s.Tau[i] = Tau[i];
    } 
}

void sim(){
    Timer sim_loop(1_ms);
    {
        while(!stop_){
            {
                std::mutex lock;
                double tau[] = {0.0,0.0,0.0};
                set_Tau(tau);
                rob.update(0.001);
            }
            std::cout << rob.m_s.Q[0] << ", " << rob.m_s.Q[1] << ", " << rob.m_s.Q[2] << std::endl;
            t_last = t;
            t = sim_loop.wait().as_seconds();
        }
    }
}

void start(){
    {
        std::mutex lock;
        rob.zero();
        stop_ = false;
    }
    sim_thread = std::thread(sim);
}

int main(){
    start();
    std::cout << "Press enter to exit" << std::endl;
    std::cin.get();
    stop();
    return 0;
}