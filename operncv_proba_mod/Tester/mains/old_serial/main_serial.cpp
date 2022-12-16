//
// Created by ghuno on 2022-02-07.
//

#include <windows.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <map>
#include <bitset>
//#include <unistd.h>

#include "OWN_serialfuncs_win.h"
#include "useful_macros.h"

#define H16 255
struct DBLuint8{
    uint8_t UI1, UI2;
    DBLuint8 operator+(DBLuint8 Added){
        DBLuint8 TempDB;
        TempDB.UI1=UI1;
        TempDB.UI2=UI2;
        TempDB.UI2 += Added.UI2;
        if (TempDB.UI2 < UI2){
            TempDB.UI1++;
        }
        TempDB.UI1 += Added.UI1;
        return TempDB;
    }
    DBLuint8 operator+(uint8_t Added){
        DBLuint8 TempDB;
        TempDB.UI1=UI1;
        TempDB.UI2=UI2;
        TempDB.UI2 += Added;
        if (TempDB.UI2 < UI2){
            TempDB.UI1++;
        }
        return TempDB;
    }
    DBLuint8 operator+=(DBLuint8 Added){
        uint8_t Temp;
        Temp = UI2;
        Temp += Added.UI2;
        if (Temp < UI2){
            UI1++;
            UI2 = Temp;
        }
        UI1 += Added.UI1;
        return *this;
    }
    DBLuint8 operator+=(uint8_t Added){
        uint8_t Temp;
        Temp = UI2;
        Temp += Added;
        if (Temp < UI2){
            UI1++;
            UI2 = Temp;
        }
        return *this;
    }
    uint16_t Get_uint16(){
        uint16_t temp1 = (uint16_t)UI1;
        uint16_t temp2 = UI2;
        temp2 = temp2 & H16;
        return (temp1 << 8) | temp2;
    }
    int16_t Get_int16(){
        uint16_t temp1 = (uint16_t)UI1;
        uint16_t temp2 = UI2;
        temp2 = temp2 & H16;
        return (temp1 << 8) | temp2;
    }
};
uint16_t concat_ui8_ui16(uint8_t A, uint8_t B){
    uint16_t temp1 = (uint16_t)A;
    uint16_t temp2 = B;
    temp2 = temp2 & H16;
    return (temp1 << 8) | temp2;
}
int16_t concat_ui8_i16(uint8_t A, uint8_t B){
    uint16_t temp1 = (uint16_t)A;
    uint16_t temp2 = B;
    temp2 = temp2 & H16;
    return (temp1 << 8) | temp2;
}
bool UI16_2UI8_are_same(uint16_t S, uint8_t A, uint8_t B){   ///there must be a better way for this
    std::bitset<8> Abs(A), Bbs(B);
    std::bitset<16> Sbs(S);
    bool ret = 0;
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

///OPTOFORCE SPECIFIC

class OptoforceSensors{
    std::map<char*, HANDLE> list_of_sensors;
    std::map<char*, bool> LoS_goodheaders;
    std::map<char*, char*> LoS_raw_output;
    std::map<char*, uint16_t> LoS_counters;
    std::map<char*, uint16_t> LoS_statuses;
    std::map<char*, uint16_t> LoS_checksum;
    std::map<char*, std::vector<int16_t> > LoS_data;
    std::map<char*, std::vector<uint8_t> > LoS_statuses_interpreted;
    std::map<char*, bool> LoS_checksum_checked;


    HANDLE ConnectToOptoforce(char* ComName, char* ID){  /// If all sensors share the same name ID have to be copied --> either string or implement own smart char*
        //char *CName = new char(*ComName);
        //char *tID = new char(*ID);
        return CreateHandleSerial(ComName, ID);
    }
public:
    OptoforceSensors(){}
    OptoforceSensors(char* ID, HANDLE const &handle){
        list_of_sensors[ID] = handle;
    }
    OptoforceSensors(HANDLE const &handle, char* ID){
        list_of_sensors[ID] = handle;
    }
    OptoforceSensors(char* ComName, char* ID){
        list_of_sensors[ID] = ConnectToOptoforce(ComName, ID);
    }
    OptoforceSensors(OptoforceSensors const &OFSL){
        list_of_sensors = OFSL.list_of_sensors;
    }
    OptoforceSensors(std::map<char*,char*> const &OFSL){
        for(std::_Rb_tree_const_iterator<std::pair<char *const, char *> > IT = OFSL.begin(); IT != OFSL.end(); IT++){
            list_of_sensors[IT->second] = ConnectToOptoforce(IT->first, IT->second);
        }
    }

    bool CheckHeader(char* ID){
        if ((uint8_t )LoS_raw_output[ID][0] == 170 && LoS_raw_output[ID][1] == 7 && LoS_raw_output[ID][2] == 8 && LoS_raw_output[ID][3] == 10) return true;
        return false;
    }
    void CheckHeader(){
        for(std::_Rb_tree_const_iterator<std::pair<char *const, char *> > IT = LoS_raw_output.begin(); IT != LoS_raw_output.end(); IT++) {
            LoS_goodheaders[IT->first] = false;
            if ((uint8_t) IT->second[0] == 170 && IT->second[1] == 7 && IT->second[2] == 8 &&
                IT->second[3] == 10)
                LoS_goodheaders[IT->first] = true;
        }
    }

    bool CheckHeader80(char* ID){
        if ((uint8_t )LoS_raw_output[ID][0] == 170 && LoS_raw_output[ID][1] == 0 && LoS_raw_output[ID][2] == 80 && LoS_raw_output[ID][3] == 1) return true;
        return false;
    }
    void CheckHeader80(){
        for(std::_Rb_tree_const_iterator<std::pair<char *const, char *> > IT = LoS_raw_output.begin(); IT != LoS_raw_output.end(); IT++) {
            LoS_goodheaders[IT->first] = false;
            if ((uint8_t) IT->second[0] == 170 && IT->second[1] == 0 && IT->second[2] == 80 &&
                IT->second[3] == 1)
                LoS_goodheaders[IT->first] = true;
        }
    }


    int16_t* ExtractData(char* szBuff){
        int16_t* ret = new int16_t[3];
        ret[0] = ((int16_t)szBuff[6] << 8) | szBuff[7];
        ret[1] = ((int16_t)szBuff[8] << 8) | szBuff[9];
        ret[2] = ((int16_t)szBuff[10] << 8) | szBuff[11];
        return ret;
    }
    void ExtractSampleC(char* szBuff, uint16_t* ret){
        *ret = ((uint16_t)szBuff[5] << 8) | szBuff[4];
    }
    void ExtractStatus(char* szBuff, uint16_t* ret){
        *ret = ((uint16_t)szBuff[7] << 8) | szBuff[6];
    }
    void ExtractData(char* szBuff, int16_t* ret){
        ret[0] = ((int16_t)szBuff[9] << 8) | szBuff[8];
        ret[1] = ((int16_t)szBuff[11] << 8) | szBuff[10];
        ret[2] = ((int16_t)szBuff[13] << 8) | szBuff[12];
    }
    void ExtractChecksum(char* szBuff, uint16_t* ret){
        *ret = ((uint16_t)szBuff[15] << 8) | szBuff[14];
    }
    bool ValidateStatus(uint16_t* ret){
        if(*ret > 0) return false;
        return true;
    }
    /* TODO*/ void InterpretStatus(int16_t* Status,int16_t* ret){

    }
    bool ValidateChecksum(uint16_t* Checksum, uint16_t* Counter, uint16_t* Status, int16_t* F1, int16_t* F2, int16_t* F3){
        uint16_t own = 195 + *Counter + *Status + *F1 + *F2 + *F3;
        if (*Checksum != own) return false;
        return true;
    }
    void CreateConfigurationByteSeries(char* szBuff,uint8_t speed, uint8_t filter, uint8_t zero){
        szBuff[0]=170;
        szBuff[1]=0;
        szBuff[2]=50;
        szBuff[3]=3;
        DBLuint8 CS;
        CS.UI1 = 233;
        szBuff[4] = speed;
        szBuff[5] = filter;
        szBuff[6] = zero;
        CS+=speed;
        CS+=filter;
        szBuff[7] = CS.UI1;
        szBuff[8] = CS.UI2;
    }
};
bool CheckHeader(char* szBuff){
    if ((uint8_t )szBuff[0] == 170 && szBuff[1] == 7 && szBuff[2] == 8 && szBuff[3] == 10) return true;
    return false;
}
bool CheckHeader(uint16_t* szBuff){
    if (szBuff[0] == 43527 && szBuff[1] == 2058) return true;
    return false;
}
bool CheckHeader80(char* szBuff){
    if((uint8_t )szBuff[0] == 170 && szBuff[1] == 0 && szBuff[2] == 80 && szBuff[3] == 1) return true;
    return false;
}
int16_t* ExtractData(char* szBuff){
    int16_t* ret = new int16_t[3];
    ret[0] = ((int16_t)szBuff[6] << 8) | szBuff[7];
    ret[1] = ((int16_t)szBuff[8] << 8) | szBuff[9];
    ret[2] = ((int16_t)szBuff[10] << 8) | szBuff[11];
    return ret;
}
void ExtractSampleC(char* szBuff, uint16_t* ret){
    *ret = (uint16_t)szBuff[4];
    uint16_t temp = szBuff[5];
    temp = temp & H16;
    *ret = (*ret << 8) | temp;
}

void ExtractStatus(char* szBuff, uint16_t* ret){
    DBLuint8 DBLUI8T;
    DBLUI8T.UI1 = szBuff[6];
    DBLUI8T.UI2 = szBuff[7];
    *ret = DBLUI8T.Get_uint16();
    //*ret = ((uint16_t)szBuff[7] << 8) | szBuff[6];
}

void ExtractData(char* szBuff, int16_t* ret){
    ret[0] = concat_ui8_i16(szBuff[8],szBuff[9]);
    ret[1] = concat_ui8_i16(szBuff[10],szBuff[11]);
    ret[2] = concat_ui8_i16(szBuff[12],szBuff[13]);
    //ret[0] = ((int16_t)szBuff[9] << 8) | szBuff[8];
    //ret[1] = ((int16_t)szBuff[11] << 8) | szBuff[10];
    //ret[2] = ((int16_t)szBuff[13] << 8) | szBuff[12];
}

void ExtractChecksum(char* szBuff, uint16_t* ret){
    *ret = concat_ui8_ui16(szBuff[14],szBuff[15]);
    //*ret = ((uint16_t)szBuff[15] << 8) | szBuff[14];
}

uint16_t CreateChecksum(char* szBuff){
    uint16_t ret = 195;
    for(int i=4; i<14; i++){
        ret += ((uint16_t)szBuff[i] & H16);
    }
    return ret;
}

/* TODO*/ void InterpretStatus(int16_t* Status,int16_t* ret){

}
bool ValidateStatus(uint16_t* ret){
    if(*ret > 0) return false;
    return true;
}
bool ValidateChecksum(uint16_t* Checksum, uint16_t* Counter, uint16_t* Status, int16_t* F1, int16_t* F2, int16_t* F3){
    uint16_t own = 195 + *Counter + *Status + *F1 + *F2 + *F3;
    if (*Checksum != own) return false;
    return true;
}
void CreateConfigurationByteSeries(char* szBuff,uint8_t speed, uint8_t filter, uint8_t zero){
    szBuff[0]=170;
    szBuff[1]=0;
    szBuff[2]=50;
    szBuff[3]=3;
    DBLuint8 CS;
    CS.UI1 = 233;
    szBuff[4] = speed;
    szBuff[5] = filter;
    szBuff[6] = zero;
    CS+=speed;
    CS+=filter;
    szBuff[7] = CS.UI1;
    szBuff[8] = CS.UI2;
}

void Bytesize8(){
    std::ofstream file;
    file.open("log10000_8_new.txt");
    HANDLE hSerial1 = CreateHandleSerial("COM4", "Optoforce1");
    //HANDLE hSerial2 = CreateHandleSerial("COM4", "Optoforce2");

    DCB dcbSerialParams = CreateSerialPortParameterProfile(1000000);  //CBR_128000
    SetSerialPortParameters(hSerial1, dcbSerialParams);
    //SetSerialPortParameters(hSerial2, dcbSerialParams);
    SetSerialPortTimeOutProfile(hSerial1);
    //SetSerialPortTimeOutProfile(hSerial2);
    //func
    //func CheckHeader
    //func
    const int n = 16;
    char szBuff1[n + 1] = {0};
    //char szBuff12[n + 1] = {0};
    //char szBuff2[n + 1] = {0};
    //char szBuff22[n + 1] = {0};
    DWORD dwBytesRead = 0;
    /*
    if(!ReadFile(hSerial1, szBuff1, n, &dwBytesRead, NULL)){
        std::cout<<"error occureed 2"<<std::endl;
//error occurred. Report to user.
    }
     */
    std::vector<int16_t> log;


    for IRANGE(100){
        Sleep(0.025);
        GetByteSeries(hSerial1, szBuff1, 16,dwBytesRead);
        int16_t temp[6] = {0};
        ExtractData(szBuff1,temp);
        ExtractSampleC(szBuff1, reinterpret_cast<uint16_t *>(&temp[3]));
        ExtractStatus(szBuff1, reinterpret_cast<uint16_t *>(&temp[4]));
        ExtractChecksum(szBuff1, reinterpret_cast<uint16_t *>(&temp[5]));

            std::vector<std::bitset<8> > BUFF(16);
            for(int i=0; i<16; i++){
                BUFF[i] = std::bitset<8>(szBuff1[i]);
            }
            std::vector<std::bitset<16> > OUT_t(9);
            for(int i=0; i<6; i++){
                OUT_t[i] = std::bitset<16>(temp[i]);
            }
            OUT_t[6] = std::bitset<16>(195);
            OUT_t[7] = std::bitset<16>(((uint16_t )temp[3] + (uint16_t )temp[4] + temp[0] + temp[1] + temp[2] + 195));
            OUT_t[8] = std::bitset<16>(((uint16_t )temp[3] + (uint16_t )temp[4] + temp[0] + temp[1] + temp[2] + 195)-(uint16_t )temp[5]);

        file<<temp[0]<<"\t\t\t\t\t\t"<<temp[1]<<"\t\t\t\t\t"<<temp[2]<<"\t\t\t\t"<<(uint16_t )temp[3]<<"\t\t\t\t"<<(uint16_t )temp[4]<<"\t\t\t\t"<<195
            <<"\t\t\t\t\t\t"<<(uint16_t )temp[5]<<"\t\t\t\t\t"<<
            CreateChecksum(szBuff1)
            //(((uint16_t)szBuff1[4]& H16) + ((uint16_t)szBuff1[5]& H16) + ((uint16_t)szBuff1[6]& H16) + ((uint16_t)szBuff1[7]& H16) + ((uint16_t)szBuff1[8]& H16) + ((uint16_t)szBuff1[9]& H16) + ((uint16_t)szBuff1[10]& H16) + ((uint16_t)szBuff1[11]& H16) + ((uint16_t)szBuff1[12]& H16) + ((uint16_t)szBuff1[13]& H16) + 195)
            <<"\t\t\t\t"<< ((uint16_t )temp[3] + (uint16_t )temp[4] + temp[0] + temp[1] + temp[2] + 195)-(uint16_t )temp[5]
            <<"\t\t\t\t\t"<< ((uint16_t)szBuff1[0] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[1] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[2]& H16)<<"\t\t\t"<<((uint16_t)szBuff1[3]& H16)<<"\t\t\t"<<((uint16_t)szBuff1[4]& H16)<<"\t\t\t"<<((uint16_t)szBuff1[5]& H16)<<"\t\t\t"<<((uint16_t)szBuff1[6] & H16)<<"\t\t\t"
            <<((uint16_t)szBuff1[7] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[8] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[9] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[10] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[11] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[12] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[13] & H16)<<"\t\t\t"
            <<((uint16_t)szBuff1[14] & H16)<<"\t\t\t"<<((uint16_t)szBuff1[15] & H16)<<"\n"
            <<UI16_2UI8_are_same(temp[0], szBuff1[8], szBuff1[9])<<" "
            <<UI16_2UI8_are_same(temp[1], szBuff1[10], szBuff1[11])<<" "
            <<UI16_2UI8_are_same(temp[2], szBuff1[12], szBuff1[13])<<" "
            <<UI16_2UI8_are_same(temp[3], szBuff1[4], szBuff1[5])<<" "
            <<UI16_2UI8_are_same(temp[4], szBuff1[6], szBuff1[7])<<" "
            <<UI16_2UI8_are_same(temp[5], szBuff1[14], szBuff1[15])<<"\n"
            <<OUT_t[0]<<"\t"<<OUT_t[1]<<"\t"<<OUT_t[2]<<"\t"<<OUT_t[3]<<"\t"<<OUT_t[4]<<"\t"<<OUT_t[5]<<"\n"
            <<BUFF[8]<<BUFF[9]<<"\t"<<BUFF[10]<<BUFF[11]<<"\t"<<BUFF[12]<<BUFF[13]<<"\t"<<BUFF[4]<<BUFF[5]<<"\t"<<BUFF[6]<<BUFF[7]<<"\t"<<BUFF[14]<<BUFF[15]<<"\n";
            /*<<OUT_t[0]<<"\t"<<OUT_t[1]<<"\t"<<OUT_t[2]<<"\t"<<OUT_t[3]<<"\t"<<OUT_t[4]<<"\t"<<OUT_t[6]
            <<"\t\t"<<OUT_t[5]<<"\t"<<OUT_t[7]<<"\t"<<OUT_t[8]
            <<"\t\t"<<BUFF[0]<<"\t"<<BUFF[1]<<"\t"<<BUFF[2]<<"\t"<<BUFF[3]<<"\t"<<BUFF[4]<<"\t"<<BUFF[5]<<"\t"<<BUFF[6]<<"\t"<<BUFF[7]<<"\t"<<BUFF[8]<<"\t"<<BUFF[9]<<"\t"
            <<BUFF[10]<<"\t"<<BUFF[11]<<"\t"<<BUFF[12]<<"\t"<<BUFF[13]<<"\t"<<BUFF[14]<<"\t"<<BUFF[15]<<"\n";*/
    }

    /*
    std::cout<<":"<<+(uint8_t)szBuff1[0]<<"\n:"<<(int)szBuff1[1]<<"\n:"<<(int)szBuff1[2]<<"\n:"<<(int)szBuff1[3]<<"\n:"
            <<(int)szBuff1[4]<<"\n:"<<(int)szBuff1[5]<<"\n:"<<(int)szBuff1[6]<<"\n:"<<(int)szBuff1[7]<<"\n:"
            <<(int)szBuff1[8]<<"\n:"<<(int)szBuff1[9]<<"\n:"<<(int)szBuff1[10]<<"\n:"<<(int)szBuff1[11]<<"\n:"
            <<(int)szBuff1[12]<<"\n:"<<(int)szBuff1[13]<<"\n:"<<(int)szBuff1[14]<<"\n:"<<(int)szBuff1[15]<<"\n";
    std::cout<<CheckHeader(szBuff1)<<std::endl;
    std::cout<<dwBytesRead<<std::endl;
    int16_t temp[5] = {0};
    ExtractData(szBuff1,temp);
    ExtractSampleC(szBuff1,&temp[3]);
    ExtractStatus(szBuff1,&temp[4]);

    std::cout<<"\n:"<<temp[0]<<"\n:"<<temp[1]<<"\n:"<<temp[2]<<"\n:"<<temp[3]<<"\n:"<<temp[4]<<"\n";
*/
    CloseHandle(hSerial1);
    //CloseHandle(hSerial2);
}

void ExtractSampleC(uint16_t* szBuff, uint16_t* ret){
    *ret = szBuff[2];
}
void ExtractStatus(uint16_t* szBuff, uint16_t* ret){
    *ret = szBuff[3];
}
void ExtractData(uint16_t* szBuff, int16_t* ret){
    ret[0] = (int16_t)szBuff[4];
    ret[1] = (int16_t)szBuff[5];
    ret[2] = (int16_t)szBuff[6];
}
void ExtractChecksum(uint16_t* szBuff, uint16_t* ret){
    *ret = szBuff[7];
}

void Bytesize16(){
    std::ofstream file;
    file.open("log10000_16.txt");
    HANDLE hSerial1 = CreateHandleSerial("COM3", "Optoforce1");
    //HANDLE hSerial2 = CreateHandleSerial("COM4", "Optoforce2");

    DCB dcbSerialParams = CreateSerialPortParameterProfile(1000000, 16);  //CBR_128000
    SetSerialPortParameters(hSerial1, dcbSerialParams);
    //SetSerialPortParameters(hSerial2, dcbSerialParams);
    SetSerialPortTimeOutProfile(hSerial1);
    //SetSerialPortTimeOutProfile(hSerial2);
    //func
    //func CheckHeader
    //func
    const int n = 16;
    uint16_t szBuff1[n + 1] = {0};
    //char szBuff12[n + 1] = {0};
    //char szBuff2[n + 1] = {0};
    //char szBuff22[n + 1] = {0};
    DWORD dwBytesRead = 0;
    /*
    if(!ReadFile(hSerial1, szBuff1, n, &dwBytesRead, NULL)){
        std::cout<<"error occureed 2"<<std::endl;
//error occurred. Report to user.
    }
     */
    std::vector<int16_t> log;

    for(int i=0; i<60000; i++){
        Sleep(0.025);
        GetByteSeries(hSerial1, szBuff1, 8,dwBytesRead);
        int16_t temp[6] = {0};
        ExtractData(szBuff1,temp);
        ExtractSampleC(szBuff1, reinterpret_cast<uint16_t *>(&temp[3]));
        ExtractStatus(szBuff1, reinterpret_cast<uint16_t *>(&temp[4]));
        ExtractChecksum(szBuff1, reinterpret_cast<uint16_t *>(&temp[5]));
        file<<temp[0]<<"\t"<<temp[1]<<"\t"<<temp[2]<<"\t"<<(uint16_t )temp[3]<<"\t"<<(uint16_t )temp[4]<<"\t\t"<<(uint16_t )temp[5]<<"\t"<<
            ((uint16_t )temp[3] + (uint16_t )temp[4] + temp[0] + temp[1] + temp[2] + 195)<<"\t\t"<<
            (uint16_t)szBuff1[0]<<"\t"<<(uint16_t)szBuff1[1]<<"\t"<<(uint16_t)szBuff1[2]<<"\t"<<(uint16_t)szBuff1[3]<<"\t"<<(uint16_t)szBuff1[4]<<"\t"<<(uint16_t)szBuff1[5]<<"\t"<<(uint16_t)szBuff1[6]<<"\t"<<(uint16_t)szBuff1[7]<<"\n";//<<temp[4]<<"\n";
    }

    /*
    std::cout<<":"<<+(uint8_t)szBuff1[0]<<"\n:"<<(int)szBuff1[1]<<"\n:"<<(int)szBuff1[2]<<"\n:"<<(int)szBuff1[3]<<"\n:"
            <<(int)szBuff1[4]<<"\n:"<<(int)szBuff1[5]<<"\n:"<<(int)szBuff1[6]<<"\n:"<<(int)szBuff1[7]<<"\n:"
            <<(int)szBuff1[8]<<"\n:"<<(int)szBuff1[9]<<"\n:"<<(int)szBuff1[10]<<"\n:"<<(int)szBuff1[11]<<"\n:"
            <<(int)szBuff1[12]<<"\n:"<<(int)szBuff1[13]<<"\n:"<<(int)szBuff1[14]<<"\n:"<<(int)szBuff1[15]<<"\n";
    std::cout<<CheckHeader(szBuff1)<<std::endl;
    std::cout<<dwBytesRead<<std::endl;
    int16_t temp[5] = {0};
    ExtractData(szBuff1,temp);
    ExtractSampleC(szBuff1,&temp[3]);
    ExtractStatus(szBuff1,&temp[4]);

    std::cout<<"\n:"<<temp[0]<<"\n:"<<temp[1]<<"\n:"<<temp[2]<<"\n:"<<temp[3]<<"\n:"<<temp[4]<<"\n";
*/
    CloseHandle(hSerial1);
    //CloseHandle(hSerial2);
}



int main(){
    Bytesize8();
    /*
    std::ofstream file;
    file.open("log10000.txt");
    HANDLE hSerial1 = CreateHandleSerial("COM3", "Optoforce1");
    //HANDLE hSerial2 = CreateHandleSerial("COM4", "Optoforce2");

    DCB dcbSerialParams = CreateSerialPortParameterProfile(1000000);  //CBR_128000
    SetSerialPortParameters(hSerial1, dcbSerialParams);
    //SetSerialPortParameters(hSerial2, dcbSerialParams);
    SetSerialPortTimeOutProfile(hSerial1);
    //SetSerialPortTimeOutProfile(hSerial2);
    //func
    //func CheckHeader
    //func
    const int n = 16;
    char szBuff1[n + 1] = {0};
    //char szBuff12[n + 1] = {0};
    //char szBuff2[n + 1] = {0};
    //char szBuff22[n + 1] = {0};
    DWORD dwBytesRead = 0;

    //if(!ReadFile(hSerial1, szBuff1, n, &dwBytesRead, NULL)){
    //    std::cout<<"error occureed 2"<<std::endl;
            //error occurred. Report to user.
    //}
    //std::vector<int16_t> log;

    for(int i=0; i<60000; i++){
        Sleep(0.025);
        GetByteSeries(hSerial1, szBuff1, 16,dwBytesRead);
        int16_t temp[6] = {0};
        ExtractData(szBuff1,temp);
        ExtractSampleC(szBuff1, reinterpret_cast<uint16_t *>(&temp[3]));
        ExtractStatus(szBuff1, reinterpret_cast<uint16_t *>(&temp[4]));
        ExtractChecksum(szBuff1, reinterpret_cast<uint16_t *>(&temp[5]));
        file<<temp[0]<<"\t"<<temp[1]<<"\t"<<temp[2]<<"\t"<<(uint16_t )temp[3]<<"\t"<<(uint16_t )temp[4]<<"\t\t"<<(uint16_t )temp[5]<<"\t"<<
                ((uint16_t )temp[3] + (uint16_t )temp[4] + temp[0] + temp[1] + temp[2] + 195)<<"\t\t"<<
                (uint16_t)szBuff1[0]<<"\t"<<(uint16_t)szBuff1[1]<<"\t"<<(uint16_t)szBuff1[2]<<"\t"<<(uint16_t)szBuff1[3]<<"\t"<<(uint16_t)szBuff1[4]<<"\t"<<(uint16_t)szBuff1[5]<<"\t"<<(uint16_t)szBuff1[6]<<"\t"<<(uint16_t)szBuff1[7]<<"\t"<<(uint16_t)szBuff1[8]<<"\t"<<(uint16_t)szBuff1[9]<<"\t"<<(uint16_t)szBuff1[10]<<"\t"<<(uint16_t)szBuff1[11]<<"\t"<<(uint16_t)szBuff1[12]<<"\t"<<(uint16_t)szBuff1[13]<<"\t"<<(uint16_t)szBuff1[14]<<"\t"<<(uint16_t)szBuff1[15]<<"\n";//<<temp[4]<<"\n";
    }

    CloseHandle(hSerial1);
    //CloseHandle(hSerial2);

*/
    return 1;
}
