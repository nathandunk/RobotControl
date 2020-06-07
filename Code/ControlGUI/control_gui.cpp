#include <Mahi/Gui.hpp>
#include <Mahi/Util.hpp>
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <codecvt>
#include <locale>

using namespace mahi::gui;
using namespace mahi::util;

class RobotControl : public Application {
public:
    /// Constructor
    RobotControl() : Application() 
    { 
        // ImGui::DisableViewports();
        // ImGui::StyleColorsLight();
        // hideWindow();

        // // Add plotting parameters necessary
        rt_plot.x_axis.minimum = 0;   
        rt_plot.x_axis.maximum = 10;
        rt_plot.y_axis.minimum = -200;   
        rt_plot.y_axis.maximum = 200;
        // rt_plot.x_axis.showLabels = true;

        oh_plot.x_axis.minimum = -10;   
        oh_plot.x_axis.maximum = 10;
        oh_plot.y_axis.minimum = -10;   
        oh_plot.y_axis.maximum = 10;        

        rt_items.resize(2*num_joints);
        for (auto i = 0; i < rt_items.size(); i++){
            // rt_items[i].color = Grays::Gray50;
            if (i < num_joints) rt_items[i].label = "Command " + std::to_string(i);
            else                 rt_items[i].label = "Encoder " + std::to_string(i);
            rt_items[i].data.reserve(1000);
            rt_items[i].size = 3;
        }

        oh_grids.resize(4);
        oh_grids[0].color = Whites::White;
        oh_grids[1].color = Whites::White;
        oh_grids[0].data  = {ImVec2(oh_plot.x_axis.minimum, 0),ImVec2(oh_plot.x_axis.maximum, 0)};
        oh_grids[1].data  = {ImVec2(0,oh_plot.y_axis.minimum),ImVec2(0,oh_plot.y_axis.maximum)};
        oh_grids[0].size = 3;
        oh_grids[1].size = 3;
        oh_grids[0].type = ImGui::PlotItem::Line;
        oh_grids[1].type = ImGui::PlotItem::Line;
        oh_grids[0].label = "Axis";
        oh_grids[1].label = "Axis";

        //ref position
        oh_grids[2].color = Blues::DodgerBlue;
        oh_grids[2].data = {ImVec2(0.0f,0.0f)};
        oh_grids[2].type = ImGui::PlotItem::Scatter;
        oh_grids[2].size = 15;
        oh_grids[2].label = "Reference Position";

        oh_grids[3].color = Greens::Green;
        oh_grids[3].data = {ImVec2(0.0f,0.0f)};
        oh_grids[3].type = ImGui::PlotItem::Scatter;
        oh_grids[3].size = 15;
        oh_grids[3].label = "Current Position";
    }

    ~RobotControl() {

    }

    /// Override update from Application, called once per frame
    void update() override
    {
        while(angles.size() < num_joints){
            angles.push_back(0);
            encoders.push_back(0);
        }
        while(angles.size() > num_joints && num_joints>0){
            angles.pop_back();
            encoders.pop_back();
        }
        ImGui::Begin("Angle Control", &open);
        ImGui::InputInt("Number of Joints:", &num_joints);
        // ImGui::BeginGroup();
        if(num_joints > 0){
            for (size_t i = 0; i < num_joints; i++){
                ImGui::DragFloat(("Angle " + std::to_string(i)).c_str(),&angles[i],0.5,-1000,1000);
            }
            for (size_t i = 0; i < num_joints; i++){
                ImGui::DragFloat(("Encoder " + std::to_string(i)).c_str(),&encoders[i],0.5,-1000,1000);
            }
        }
        ImGui::InputInt("Comport number:", &comport_num);
        if(ImGui::Button("Connect")){
            begin_serial();
        }
        ImGui::Checkbox("Enable", &enabled);

        for (auto i = 0; i < num_joints; i++){
            ImGui::PlotItemBufferPoint(rt_items[i], (float)time().as_seconds(), angles[i], 1000);
            ImGui::PlotItemBufferPoint(rt_items[i+num_joints],(float)time().as_seconds(),encoders[i],1000);
        }
        rt_plot.x_axis.minimum = (float)time().as_seconds() - 10.0f;
        rt_plot.x_axis.maximum = (float)time().as_seconds();
        ImGui::Plot("Position and Encoders", rt_plot, rt_items, ImVec2(ImGui::GetWindowWidth()/2.0f-20.0f,-1.0f));

        ImGui::SameLine();

        
        ImGui::Plot("Overhead View Control", oh_plot, oh_grids, ImVec2(ImGui::GetWindowWidth()/2.0f-20.0f,-1.0f));
        if (ImGui::IsPlotHovered() && ImGui::GetIO().MouseClicked[0]){
            ImVec2 ee_positions = ImGui::GetPlotMousePos();
            angles = get_ik_angles(ee_positions, encoders);
        }
        oh_grids[2].data = {get_ee_pos(angles)};
        oh_grids[3].data = {get_ee_pos(encoders)};

        ImGui::End();
        if (enabled){
            write_serial();
        }
        if (!open){
            quit();
        }
    }

    ImVec2 get_ee_pos(std::vector<float> encoders){
        double length = 10.0*sin(encoders[1]*DEG2RAD);
        double ee_x = length*cos(encoders[0]*DEG2RAD);
        double ee_y = length*sin(encoders[0]*DEG2RAD);
        return ImVec2(ee_x,ee_y);
    }

    float get_closest_angle(float theta, float theta_d){
        std::cout << theta << " " << theta_d << std::endl;
        float theta_new = theta_d;
        float diff = theta - theta_new;
        std::cout <<theta_new << std::endl;
        while (abs(diff) > 180.0){
            theta_new = theta_new + ((diff > 0) - (diff < 0))*360.0;
            std::cout << theta_new << std::endl;
            diff = theta - theta_new;
        }
        std::cout << theta_new << std::endl;
        return theta_new;
    }

    std::vector<float> get_ik_angles(ImVec2 ee_pos, std::vector<float> encoders){
        float theta1_d = mahi::util::atan2(ee_pos[1],ee_pos[0])*RAD2DEG;
        float theta1 = get_closest_angle(encoders[0], theta1_d);
        std::cout <<theta1 << std::endl;

        double length = mahi::util::sqrt(pow(ee_pos[0],2) + pow(ee_pos[1],2));
        float theta2 = (length < 10.0) ? (asin(length/10.0)*RAD2DEG) : 90.0f;
        return {theta1, theta2};
    }

    void begin_serial(){
        std::wstring com_prefix = L"\\\\.\\COM";
        std::wstring com_suffix = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(std::to_string(comport_num));
        std::wstring comID = com_prefix + com_suffix;

        hSerial = CreateFileW(comID.c_str(),
                              GENERIC_READ | GENERIC_WRITE,
                              0,
                              0,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              0);

        DCB dcbSerialParams = {0};
        dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cout << "Could not get com state" << std::endl;
        }

        dcbSerialParams.BaudRate=CBR_9600;
        dcbSerialParams.ByteSize=8;
        dcbSerialParams.StopBits=ONESTOPBIT;
        dcbSerialParams.Parity=NOPARITY;
        if(!SetCommState(hSerial, &dcbSerialParams)){
            std::cout << "could not set com state" << std::endl;
        }

        COMMTIMEOUTS timeouts={0};
        timeouts.ReadIntervalTimeout=50;
        timeouts.ReadTotalTimeoutConstant=50;
        timeouts.ReadTotalTimeoutMultiplier=10;
        
        timeouts.WriteTotalTimeoutConstant=50;
        timeouts.WriteTotalTimeoutMultiplier=10;
        if(!SetCommTimeouts(hSerial, &timeouts)){
            std::cout << "could not set timeouts" << std::endl;
        }
    }

    void write_serial(){

        // write reference angles
        char *buff = (char *)&angles[0];
        DWORD dwBytesWritten = 0;
        if(!WriteFile(hSerial, buff, sizeof(angles[0])*angles.size(), &dwBytesWritten, NULL)){
            std::cout << "error writing to serial" << std::endl;
        }

        char * pos_buff = new char[encoders.size()];
        // read encoder positions
        DWORD dwBytesRead = 0;
        if(!ReadFile(hSerial, pos_buff, sizeof(encoders[0])*encoders.size(), &dwBytesRead, NULL)){
            std::cout << "error reading from serial" << std::endl;
        }
        else{
            if(dwBytesRead > 0){
                memcpy(&encoders[0],pos_buff,sizeof(encoders[0])*encoders.size());
            }
        }

        // clear up memory from declaring char vector with new operator
        delete[] pos_buff;
    }

    // Member Variables
    int comport_num = 8;
    int num_joints = 2;
    std::vector<float> angles = {0, 0, 0, 0, 0, 0, 0};
    std::vector<float> encoders = {0, 0, 0, 0, 0, 0, 0};
    HANDLE hSerial;
    bool enabled = false;
    bool open = true;
    ImGui::PlotInterface rt_plot;
    ImGui::PlotInterface oh_plot;
    std::vector<ImGui::PlotItem> rt_items;
    std::vector<ImGui::PlotItem> oh_grids;
    ImGui::PlotItem EE_pos;
    // ImGui::PlotItem EE_ref;
};

int main(int argc, char const *argv[])
{
    RobotControl control;
    control.run();
    return 0;
}