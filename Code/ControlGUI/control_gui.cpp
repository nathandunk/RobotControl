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
    RobotControl() : Application(500,500,"Robot Control") 
    { 
        ImGui::DisableViewports();
    }

    ~RobotControl() {

    }

    /// Override update from Application, called once per frame
    void update() override
    {
        while(angles.size() < num_joints){
            angles.push_back(0);
        }
        while(angles.size() > num_joints && num_joints>0){
            angles.pop_back();
        }
        ImGui::BeginFixed("Angle Control", {0,0}, {500,500}, ImGuiWindowFlags_NoTitleBar);
        ImGui::InputInt("Number of Joints:", &num_joints);
        if(num_joints > 0){
            for (size_t i = 0; i < num_joints; i++){
                ImGui::DragInt(("Angle " + std::to_string(i)).c_str(),&angles[i],1,0,100);
            }
        }
        ImGui::InputInt("Comport number:", &comport_num);
        if(ImGui::Button("Connect")){
            begin_serial();
        }
        ImGui::Checkbox("Enable", &enabled);
        ImGui::End();
        if (enabled){
            // for (auto i = 0; i < num_joints; i++){
                write_serial();
            // }
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
        std::string final_string = "";
        for (auto i = 0; i < angles.size(); i++){
            std::string angle_string = std::to_string(angles[i]);
            final_string += std::string( 3-angle_string.length(), '0').append(angle_string);
        }
        
        // std::string angle_string = std::to_string(angle);

        // std::string final_string = std::string( 3-angle_string.length(), '0').append(angle_string);

        char * buff;
        buff = new char[3*num_joints];
        
        strcpy(buff,final_string.c_str());

        std::cout << buff << std::endl;
        std::cout <<sizeof(buff)/sizeof(*buff) << std::endl;
        DWORD dwBytesRead = 0;
        if(!WriteFile(hSerial, buff, 3*num_joints, &dwBytesRead, NULL)){
            std::cout << "error writing to serial" << std::endl;;
        }
    }

    // Member Variables
    int comport_num = 8;
    int num_joints = 2;
    std::vector<int> angles = {0, 0, 0, 0, 0, 0, 0};
    HANDLE hSerial;
    bool enabled = false;
};

int main(int argc, char const *argv[])
{
    RobotControl control;
    control.run();
    return 0;
}