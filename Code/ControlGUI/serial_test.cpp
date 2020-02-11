#include "Windows.h"
#include <tchar.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char const *argv[]){
    HANDLE hSerial;

    hSerial = CreateFile(_T("COM8"),
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          0,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          0);

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cout << "Could not get com state";
    }

    dcbSerialParams.BaudRate=CBR_9600;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    if(!SetCommState(hSerial, &dcbSerialParams)){
        std::cout << "could not set com state";
    }

    COMMTIMEOUTS timeouts={0};
    timeouts.ReadIntervalTimeout=50;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier=10;
    
    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier=10;
    if(!SetCommTimeouts(hSerial, &timeouts)){
        std::cout << "could not set timeouts";
    }

    char buff[] = {'0', '1', '0'};
    DWORD dwBytesRead = 0;
    if(!WriteFile(hSerial, buff, sizeof(buff)/sizeof(*buff), &dwBytesRead, NULL)){
        std::cout << "error writing to serial";
    }

    return 0;
}
