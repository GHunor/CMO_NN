//
// Created by ghuno on 2022-03-21.
//

#ifndef TESTER_OPTOFORCE_H
#define TESTER_OPTOFORCE_H

#include "OWN_serialfuncs_win.h"

#include <map>
#include <bitset>

#define H16 255

class optoforce{
    HANDLE sensor_Handle;
    const char* ID;

    char szBuff[17];
    DWORD dwBytesRead;

    void Get_Buff(){
        GetByteSeries(sensor_Handle, szBuff, 16,dwBytesRead);
    }
    bool Check_Header(){
        if ((uint8_t )szBuff[0] == 170 && szBuff[1] == 7 && szBuff[2] == 8 && szBuff[3] == 10) return true;
        return false;
    }
    bool Check_Status(){
        uint16_t ret = concat_ui8_ui16(szBuff[6],szBuff[7]);
        if (ret != 0) return false;
        return true;
    }
    bool Validate_Checksum(){
        uint16_t own = 195, checksum;
        for(int i=4; i<14; i++){
            own += ((uint16_t)szBuff[i] & H16);
        }
        checksum = concat_ui8_ui16(szBuff[14],szBuff[15]);
        if (checksum != own) return false;
        return true;
    }

    //ALL THE uint8 to uint16 functions
    static uint16_t concat_ui8_ui16(uint8_t A, uint8_t B){
        uint16_t temp1 = (uint16_t)A;
        uint16_t temp2 = B;
        temp2 = temp2 & H16;
        return (temp1 << 8) | temp2;
    }
    static int16_t concat_ui8_i16(uint8_t A, uint8_t B){
        uint16_t temp1 = (uint16_t)A;
        uint16_t temp2 = B;
        temp2 = temp2 & H16;
        return (temp1 << 8) | temp2;
    }

    static bool  UI16_2UI8_are_same(uint16_t S, uint8_t A, uint8_t B){   ///there must be a better way for this
        std::bitset<8> Abs(A), Bbs(B);
        std::bitset<16> Sbs(S);
        bool ret = false;
        for(int i=0; i<16; i++){
            if(i<8){
                ret = ret || (Sbs[i]^Bbs[i]);
            }
            else{
                ret = ret || (Sbs[i]^Abs[i-8]);
            }
        }
        return ret;
    }

public:
    optoforce(){
        dwBytesRead=0;
    };
    explicit optoforce(HANDLE serial_handle){
        dwBytesRead=0;
        sensor_Handle = serial_handle;
        ID = (char*)"FILLER";
        DCB dcbSerialParams = CreateSerialPortParameterProfile(1000000);
        SetSerialPortParameters(serial_handle, dcbSerialParams);
        SetSerialPortTimeOutProfile(serial_handle);
    }
    optoforce(const char* Com_name, const char* id){
        dwBytesRead=0;
        ID = id;
        sensor_Handle = CreateHandleSerial(Com_name, ID);
        DCB dcbSerialParams = CreateSerialPortParameterProfile(1000000);
        SetSerialPortParameters(sensor_Handle, dcbSerialParams);
        SetSerialPortTimeOutProfile(sensor_Handle);
    }

    bool Connected(){
        return !(sensor_Handle==INVALID_HANDLE_VALUE);
    }

    std::vector<int> Get_vector(){
        Get_Buff();
        std::vector<int> ret;
        ret.push_back(concat_ui8_ui16(szBuff[4], szBuff[5]));
        ret.push_back(concat_ui8_i16(szBuff[8],szBuff[9]));
        ret.push_back(concat_ui8_i16(szBuff[10],szBuff[11]));
        ret.push_back(concat_ui8_i16(szBuff[12],szBuff[13]));
        return ret;
    }
    bool All_GoodQ() {
        return Validate_Checksum() && Check_Status() && Check_Header();
    }

};

#endif //TESTER_OPTOFORCE_H
