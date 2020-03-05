#include <mahi/gui.hpp>
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <codecvt>
#include <locale>

using namespace mahi::gui;

class RobotControl : public Application {
public:
    /// Constructor
    RobotControl() : Application() 
    { 
        // ImGui::DisableViewports();
        // ImGui::StyleColorsLight();
        // hideWindow();

        // // Add plotting parameters necessary
        rt_plot.xAxis.minimum = 0;   
        rt_plot.xAxis.maximum = 10;
        rt_plot.yAxis.minimum = -200;   
        rt_plot.yAxis.maximum = 200;
        // rt_plot.xAxis.showLabels = true;

        oh_plot.xAxis.minimum = -10;   
        oh_plot.xAxis.maximum = 10;
        oh_plot.yAxis.minimum = -10;   
        oh_plot.yAxis.maximum = 10;        

        rt_items.resize(2*num_joints);
        for (auto i = 0; i < rt_items.size(); i++){
            // rt_items[i].color = Grays::Gray50;
            if (i < num_joints) rt_items[i].label = "Command " + std::to_string(i);
            else                 rt_items[i].label = "Encoder " + std::to_string(i);
            rt_items[i].data.reserve(1000);
            rt_items[i].size = 3;
        }

        oh_items.resize(2);
        oh_items[0].color = Whites::White;
        oh_items[1].color = Whites::White;
        oh_items[0].data  = {ImVec2(oh_plot.xAxis.minimum, 0),ImVec2(oh_plot.xAxis.maximum, 0)};
        oh_items[1].data  = {ImVec2(0,oh_plot.yAxis.minimum),ImVec2(0,oh_plot.yAxis.maximum)};
        oh_items[0].size = 3;
        oh_items[1].size = 3;
        oh_items[0].type = ImGui::PlotItem::Line;
        oh_items[1].type = ImGui::PlotItem::Line;
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
                ImGui::DragFloat(("Angle " + std::to_string(i)).c_str(),&angles[i],0.5,-200,200);
            }
            for (size_t i = 0; i < num_joints; i++){
                ImGui::DragFloat(("Encoder " + std::to_string(i)).c_str(),&encoders[i],0.5,-200,200);
            }
        }
        ImGui::InputInt("Comport number:", &comport_num);
        if(ImGui::Button("Connect")){
            begin_serial();
        }
        ImGui::Checkbox("Enable", &enabled);
        for (auto i = 0; i < num_joints; i++){
            ImGui::PlotItemBufferPoint(rt_items[i], (float)time(), angles[i], 1000);
            ImGui::PlotItemBufferPoint(rt_items[i+num_joints],(float)time(),encoders[i],1000);
        }
        rt_plot.xAxis.minimum = (float)time() - 10.0f;
        rt_plot.xAxis.maximum = (float)time();
        ImGui::Plot("Position and Encoders", rt_plot, rt_items, ImVec2(ImGui::GetWindowWidth()/2.0-20.0,-1));
        
        // ImGui::Text("Test");
        ImGui::SameLine();

        ImGui::Plot("Overhead View Control", oh_plot, oh_items, ImVec2(ImGui::GetWindowWidth()/2.0-20.0,-1));
        ImGui::End();
        if (enabled){
            write_serial();
        }
        if (!open){
            quit();
        }
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
    std::vector<ImGui::PlotItem> oh_items;
};

int main(int argc, char const *argv[])
{
    RobotControl control;
    control.run();
    return 0;
}