//
// Created by ghuno on 2022-03-11.
//

#ifndef WINHSUBSTITUTE_H
#define WINHSUBSTITUTE_H

#define CBR_19200 19200;
#define ONESTOPBIT 1;
#define NOPARITY false;
// #define GENERIC_READ GENERIC_WRITE OPEN_EXISTING FILE_ATTRIBUTE_NORMAL INVALID_HANDLE_VALUE ERROR_FILE_NOT_FOUND

class HANDLE{

};

class DWORD{

};

class COMMTIMEOUTS{
public:
    int ReadIntervalTimeout;
    int ReadTotalTimeoutConstant;
    int ReadTotalTimeoutMultiplier;
    int WriteTotalTimeoutConstant;
    int WriteTotalTimeoutMultiplier;

};

class DCB{
public:
    int DCBlength;
    int BaudRate;
    int ByteSize;
    int StopBits;
    bool Parity;
};



class placeholder1{

};
HANDLE CreateFile(char* ComName,
        GENERIC_READ | GENERIC_WRITE,
0,
0,
OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL,
0);
std::string GetLastError();
bool SetCommState(HANDLE hSerial, DCB &dcbSerialParams);
bool SetCommTimeouts(HANDLE &hSerial, COMMTIMEOUTS &timeouts);
bool ReadFile(HANDLE , char* szBuff, unsigned int n, &dwBytesRead, placeholder1 lpOverlapped = NULL);
bool WriteFile(HANDLE , char* szBuff, unsigned int n, &dwBytesRead, placeholder1 lpOverlapped = NULL);

void system(std::string command){};
#endif //WINHSUBSTITUTE_H
