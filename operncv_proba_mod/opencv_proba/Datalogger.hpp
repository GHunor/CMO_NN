//
// Created by ghuno on 2021-11-19.
//

#ifndef CPPTESTER_DATALOGGER_H
#define CPPTESTER_DATALOGGER_H

#include <ostream>
#include <vector>
#include <fstream>
#include <direct.h>
#include <cstring>
#include <sstream>


//#include <fileapi.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include "useful_macros.h"
#include "Timer.hpp"
//#include "coordinator.hpp"

//vector to output operator
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
    if (vec.empty()) return os;
    os << vec[0];
    for (int i = 1; i<vec.size(); i++) { os << ", " << vec[i]; }
    return os;
};
/*
template <typename T, typename P>
void operator=(std::vector<T> &vec1, const std::vector<P> &vec2){
    vec1.empty();
    for (int i = 0; i<vec2.size(); i++) {
        T tmp = vec2[i];
        vec2.push_back(tmp);
    }
};*/

//vector printed vertically
template <typename T>
std::ostream & Vertical_read(std::ostream &os, const std::vector<T> &vec){
    if (vec.empty()) return os;
    os << vec[0];
    for (int i = 1; i<vec.size(); i++) { os << "\n" << vec[i]; }
    return os;
}

//convert int to string
std::string to_string(int in){
	std::ostringstream convert;
	convert << in;
	return convert.str();
}

//convert array to vector
template <typename T>
std::vector<T>& Array_to_vector(T* array, int size){
    std::vector<T>* vec = new std::vector<T>(size);
    for (int i = 1; i<size; i++) {
        (*vec)[i] = array[i];}
    return *vec;
}

std::vector<std::string> break_up_address(std::string address){
    std::vector<std::string> ret;
    std::string tmp = "";
    int ind = 0;
    int end = address.length()-1;
    bool dot = false;
    for IRANGE(address.length()){
        if(address[i] == '/' && i==address.length()-1){
            end--;
            break;
        }
        if (address[i] == '/' && i != 0 && !dot){
            ret.push_back(address.substr(ind, i));
            ind = i+1;
        }else{
            if (address[i] == '.' && (i != 0 || dot)){
                dot = true;
            }else{
                dot = false;
            }
        }
    }
    ret.push_back(address.substr(ind, end));
    return ret;
}

void create_directories(std::vector<std::string> address){
    std::string tmp = address[0];
    mkdir(tmp.c_str());
    for IRANGE(address.size()-1){
            tmp = tmp + '/' + address[i+1];
            mkdir(tmp.c_str());
    }
}

void create_directories(std::string address){
    create_directories(break_up_address(address));
}

class DataloggerS{

    std::ofstream f;
    std::string title, place;
    std::vector<std::string> move_names;     // use for file names
    std::vector<int> move_num;               // use for file names differentiation
    int norm_moves;                     // use for indexing correctly    from n: x normal, n-x-2 special, init and break
    int section;                        // use for continuity
    //coordinator* coor;

public:
    bool vht, myo, opt1, opt2, opt3;
    DataloggerS() {
        vht = true;
        myo = true;
        opt1 = true;
        opt2 = true;
        opt3 = true;
        section = 0;
    }
    void Give_title(std::string Title){
        title = Title;
    }
    void Give_place(std::string Place){
        place = Place;
		create_directories(place + "/meas");

    }
    //void Set_norm_moves_num(unsigned int Norm_moves):move_num(Norm_moves,0){norm_moves = Norm_moves;}
    void Set_move_names(std::vector<std::string> Move_names){
        move_names = Move_names;
    }
    void N0_myo(){
        myo = false;
    }
    void N0_vht(){
        vht = false;
    }
    void N0_opt1(){
        opt1 = false;
    }
    void N0_opt2(){
        opt2 = false;
    }
    void N0_opt3(){
        opt3 = false;
    }
    void push(const Timer::Ticks& data){
        float tmp = Timer::ms(data);
        f<<tmp<< ",\t";
    }
    void push(const int& data){
        float tmp = data;
        f<<tmp<< ",\t";
    }
    void push(const float& data){
        f<<data<< ",\t";
    }
    void push(const uint64_t& data){
        float tmp = data;
        f<<tmp<< ",\t";
    }
    void push(const double& data){
        float tmp = data;
        f<<tmp<< ",\t";
    }
    template<class T>
    void push(std::vector<T> data){
        float tmp;
        for IRANGE(data.size()){
            tmp = data[i];
            f<<tmp<< ",\t";
        }
    }
    template<class T>
    void push(std::vector<T> data, int start){
        float tmp;
        for (int i=start; i<data.size(); i++){
            tmp = data[i];
            f<<tmp<< ",\t";
        }
    }
    void push(const std::string& data){
        f<<data<< ",\t";
    }
    void push_state(const int& data){
        f<<data<< ",\t";
    }
    void push_line(){
        f<<"\n";
    }
    void reset_file(std::basic_string<char> name){
		f<<"kjbsdfjkhsdfhsdjkfhghui"<<std::flush;
        f.close();
        section++;
        std::string fname= place + "/meas/" + title + "_" + to_string(section) + "__" + name + ".txt";
        f.open(fname.c_str() );
        if(f.fail()) std::cout<<"\n"<<fname<<" is missing\n";
        //std::cout<<" SREAAAAM!"<<std::endl;
    }
    void reset_file_rep(std::string& name){
        f.close();
        section++;
        std::string fname= place + "/meas/" + title + "_" + to_string(section) + "__" + name + "_reped.txt";
        f.open(fname.c_str() );
        if(f.fail()) std::cout<<"\n"<<fname<<" is missing\n";
        //std::cout<<" SREAAAAM!"<<std::endl;
    }
    void close(){
        f.close();
        std::cout<<" end!"<<std::endl;
    }
    /*
    void open(std::string& name){
        std::string fname = place + '/' + title + to_string(section) + "_" + name + ".txt";
        f.open(fname.c_str() );
        std::cout<<" open!"<<std::endl;
    }
    */
    void open(std::basic_string<char> name){
        create_directories(place + "/meas");
        std::string fname = place + "/meas/" + title + "_" + to_string(section) + "__" + name + ".txt";
        f.open(fname.c_str() );;
        if(f.fail()) std::cout<<"\n"<<fname<<" is missing\n";
        std::cout<<" open!"<<std::endl;
		f<<"kjbsdfjkhsdfhsdjkfhghui"<<std::flush;
    }
    void set_place(std::string& Place){
        place = Place;
    };
    void set_title(std::string& Title){
        title = Title;
    };

    void create_infotxt(coordinator* coor){
		create_directories(place);
        std::string fname = place + '/' + title + "_infos.txt";
        f.open(fname.c_str() );;
        std::cout<<" open!"<<std::endl;
        f<<"This is the header (vertically) for the " <<place<< " measurement\n";
        f<<"Main State:\n \t0: Initial state, lasts: " << coor->Get_time_MS(Main_states::Init) << " seconds\n" <<
                         "\t1: Prepare to move state, lasts: " << coor->Get_time_MS(Main_states::PrepForNext) << " seconds\n" <<
                         "\t2: Move state, lasts: " << coor->Get_time_MS(Main_states::Move) << " seconds\n" <<
                         "\t3: Break state, lasts: " << coor->Get_time_MS(Main_states::Break) << " seconds\n" <<
                         "\t -1: Pause state, lasts: indefinite seconds\n";
        f<<"Move ID:\n";
        for (int i = 1;i<=coor->Get_numberof_nmoves(); i++){
            f<<"\t"<<i<<": "<<coor->Move_name(i) << " lasts: " << coor->Get_time_move(i) << " seconds\n";
        }
        for (int i = -coor->Get_numberof_smoves(); i<=0; i++){
            f<<"\t"<<i<<": "<<coor->Move_name(i) << " lasts: " << coor->Get_time_move(i) << " seconds\n";
        }
        f<<"Computer time difference (ms)\n";
        if (myo) {
        f<<"EMGsamples (8 data 8bit resolution)\n";
        f<<"EMGtime (1 data)\n";}
        if (vht) {
        f<<"VHT or Glove (20 data double in radian):\n \t Finger1 2 side to side (thumb MCP)\n" <<    ///need to be fixed
                                     "\t  Finger1 1 flexio (thumb DIP)\n"  <<
                                     "\t  Finger1 2 flexio (thumb MCP)\n"  <<
                                     "\t  Finger2 1 side to side (pointing finger MCP)\n"  <<
                                     "\t  Finger2 1 flexio (pointing finger MCP)\n"  <<
                                     "\t  Finger2 2 flexio (pointing finger PIP)\n"  <<
                                     "\t  Finger2 3 flexio (pointing finger DIP)\n"  <<
                                     "\t  Finger3 2 side to side (middle finger DIP)\n"  <<
                                     "\t  Finger3 1 flexio (middle finger MCP)\n"  <<
                                     "\t  Finger3 1 flexio (middle finger MCP)\n"  <<
                                     "\t  Finger3 1 flexio (middle finger PIP)\n"  <<
                                     "\t  Finger4 1 side to side (ring finger DIP)\n"  <<
                                     "\t  Finger4 2 flexio (ring finger MCP)\n"  <<
                                     "\t  Finger4 1 flexio (ring finger MCP)\n"  <<
                                     "\t  Finger4 1 flexio (ring finger MCP)\n"  <<
                                     "\t  Finger5 2 side to side (pinky PIP)\n"  <<
                                     "\t  Finger5 3 flexio (pinky DIP)\n"  <<
                                     "\t  Finger5 2 flexio (pinky DIP)\n"  <<
                                     "\t  Finger5 1 side to side (pinky MCP)(estimated by the glove)\n"  <<
                                     "\t  Wrist flexio (pointing finger MCP)(later disregarded)\n"  <<
                                     "\t  Wrist flexio (pointing finger PIP)(later disregarded)\n"  <<
                                     "\t  Palmarch flexio (pointing finger PIP)(later disregarded)\n";
        f<<"VHT or Glove time (maybe useless)\n";}
        if (opt1) {
        f<<"Optoforce1 (16 bit resolution)\n" <<
                                     "\t  Internal clock time\n"  <<
                                     "\t  X axis\n"  <<
                                     "\t  Y axis\n"  <<
                                     "\t  Z axis\n";}
        if (opt2) {
        f<<"Optoforce2 (16 bit resolution)\n" <<
                                     "\t  Internal clock time\n"  <<
                                     "\t  X axis\n"  <<
                                     "\t  Y axis\n"  <<
                                     "\t  Z axis\n";}
        if (opt3) {
        f<<"Optoforce3 (16 bit resolution)\n" <<
                                     "\t  Internal clock time\n"  <<
                                     "\t  X axis\n"  <<
                                     "\t  Y axis\n"  <<
                                     "\t  Z axis\n";};
        f.close();
    }
    void pause(){

    }
};
#endif //CPPTESTER_DATALOGGER_H