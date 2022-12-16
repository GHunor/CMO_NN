//
// Created by ghuno on 2022-03-21.
//
/// windows specific
#ifndef TESTER_OWN_SERIALFUNCS_WIN_H
#define TESTER_OWN_SERIALFUNCS_WIN_H

#include <windows.h>

#include <iostream>
#include <stdint.h>
#include <vector>

HANDLE CreateHandleSerial(char* ComName, char* ID){
    HANDLE hSerial = CreateFile(ComName,
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                0,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                0);
    if(hSerial==INVALID_HANDLE_VALUE){
        if(GetLastError()==ERROR_FILE_NOT_FOUND){
            std::cout<<ID<<" serial port does not exist"<<std::endl;
            //serial port does not exist. Inform user.
        }
        std::cout<<"On "<<ID<<" some other error occurred"<<std::endl;
        //some other error occurred. Inform user.
    }
    return hSerial;
}
DCB CreateSerialPortParameterProfile(int BaudRate = CBR_19200, int ByteSize = 8, int StopBits = ONESTOPBIT, bool Parity = NOPARITY){
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate=BaudRate;//CBR_19200;
    dcbSerialParams.ByteSize=ByteSize;
    dcbSerialParams.StopBits=StopBits;
    dcbSerialParams.Parity=Parity;
    return dcbSerialParams;
}
void SetSerialPortParameters(HANDLE &hSerial, DCB &dcbSerialParams){
    if(!SetCommState(hSerial, &dcbSerialParams)){
        std::cout<<"error setting serial port state"<<std::endl;
        //error setting serial port state
    }
}
COMMTIMEOUTS CreateSerialPortTimeOutProfile(int ReadIntervalTimeout=50, int ReadTotalTimeoutConstant=50, int ReadTotalTimeoutMultiplier=10, int WriteTotalTimeoutConstant=50, int WriteTotalTimeoutMultiplier=10){
    COMMTIMEOUTS timeouts={0};
    timeouts.ReadIntervalTimeout=ReadIntervalTimeout;
    timeouts.ReadTotalTimeoutConstant=ReadTotalTimeoutConstant;
    timeouts.ReadTotalTimeoutMultiplier=ReadTotalTimeoutMultiplier;
    timeouts.WriteTotalTimeoutConstant=WriteTotalTimeoutConstant;
    timeouts.WriteTotalTimeoutMultiplier=WriteTotalTimeoutMultiplier;
    return timeouts;
}
void SetSerialPortTimeOutProfile(HANDLE &hSerial, int ReadIntervalTimeout=50, int ReadTotalTimeoutConstant=50, int ReadTotalTimeoutMultiplier=10, int WriteTotalTimeoutConstant=50, int WriteTotalTimeoutMultiplier=10){
    COMMTIMEOUTS timeouts = CreateSerialPortTimeOutProfile(ReadIntervalTimeout, ReadTotalTimeoutConstant, ReadTotalTimeoutMultiplier, WriteTotalTimeoutConstant, WriteTotalTimeoutMultiplier);
    if(!SetCommTimeouts(hSerial, &timeouts)){
        std::cout<<"error occureed with SetCommTimeouts"<<std::endl;
        //error occureed. Inform user
    }
}
void GetByteSeries(HANDLE &hSerial, char* szBuff, const int n, DWORD &dwBytesRead){
    if(!ReadFile(hSerial, szBuff, n, &dwBytesRead, NULL)){
        std::cout<<"error occureed with ReadFile"<<std::endl;
//error occurred. Report to user.
    }
}


/// UNUSED
__attribute__((unused)) DCB CreateSerialPortParameterProfile(const HANDLE &SerialPort) {
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);   //uses dcbSerialParams as parameter, but it also the first setter - might be bad?
    if (!GetCommState(SerialPort, &dcbSerialParams)) {
        std::cout<<"error getting state"<<std::endl;
        //error getting state
    }
    return dcbSerialParams;
}
__attribute__((unused)) char* GetByteSeries(HANDLE &hSerial, const int n, DWORD &dwBytesRead){
    char szBuff[n + 1] = {0};
    if(!ReadFile(hSerial, szBuff, n, &dwBytesRead, NULL)){
        std::cout<<"error occureed 2"<<std::endl;
//error occurred. Report to user.
    }
    return szBuff;
}
__attribute__((unused)) void SetSerialPortParameters(HANDLE &hSerial, int BaudRate = CBR_19200, int ByteSize = 8, int StopBits = ONESTOPBIT, bool Parity = NOPARITY){
    DCB dcbSerialParams = CreateSerialPortParameterProfile(BaudRate, ByteSize, StopBits, Parity);
    if(!SetCommState(hSerial, &dcbSerialParams)){
        std::cout<<"error setting serial port state"<<std::endl;
        //error setting serial port state
    }
}
__attribute__((unused)) void SetSerialPortTimeOutProfile(HANDLE &hSerial, COMMTIMEOUTS &timeouts){
    if(!SetCommTimeouts(hSerial, &timeouts)){
        std::cout<<"error occureed with SetCommTimeouts"<<std::endl;
        //error occureed. Inform user
    }
}
__attribute__((unused)) void SetByteSeries(HANDLE &hSerial, char* szBuff, const int n, DWORD &dwBytesRead){
    if(!WriteFile(hSerial, szBuff, n, &dwBytesRead, NULL)){
        std::cout<<"error occureed 2"<<std::endl;
//error occurred. Report to user.
    }
}

///16BIT GET AND SET
/*DOESN'T WORK*/ __attribute__((unused)) void GetByteSeries(HANDLE &hSerial, uint16_t* szBuff, const int n, DWORD &dwBytesRead){  //throws errors
    if(!ReadFile(hSerial, szBuff, n, &dwBytesRead, NULL)){
        std::cout<<"read file error"<<std::endl;
//error occurred. Report to user.
    }
}
/*DOESN'T WORK*/ __attribute__((unused)) void SetByteSeries(HANDLE &hSerial, uint16_t* szBuff, const int n, DWORD &dwBytesRead){
    if(!WriteFile(hSerial, szBuff, n, &dwBytesRead, NULL)){
        std::cout<<"error occureed 2"<<std::endl;
//error occurred. Report to user.
    }
}

#endif //TESTER_OWN_SERIALFUNCS_WIN_H
