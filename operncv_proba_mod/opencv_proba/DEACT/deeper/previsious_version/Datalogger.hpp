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


#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <stdlib.h>

#include "Timer.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
	if (vec.empty()) {std::cout<<"NINCS VECTORDATA"<<std::endl; return os;}
    os << vec[0];
    for (int i = 1; i<vec.size(); i++) { os << ", " << vec[i]; }
    return os;
};
template <typename T>
std::ostream & Vertical_read(std::ostream &os, const std::vector<T> &vec){
    if (vec.empty()) return os;
    os << vec[0];
    for (int i = 1; i<vec.size(); i++) { os << "\n" << vec[i]; }
    return os;
}

template <typename T>
std::vector<T>& Array_to_vector(T* array, int size){
	std::vector<T>* vec = new std::vector<T>(size);
    for (int i = 1; i<size; i++) {
		(*vec)[i] = array[i];}
    return *vec;
}

std::string to_string(int in){
	std::ostringstream convert;
	convert << in;
	return convert.str();
}

///rework it so it keeps a file open and closes it on demand

class Datalogger{
    ///BUFFERSIZE
    const static int max_buffer=1000;
    ///BUFFERSIZE

    struct Dataline {
        float system_time;
        std::vector<int> myo;
        uint64_t myo_time;
        std::vector<double> glove;
        double glove_time;
        std::string movement, message, pressed_key;
		Dataline():system_time(0.0), myo(8),myo_time(0),glove(23), glove_time(0), movement(),message(),pressed_key(){};
        friend std::ostream &operator<<(std::ostream &os, const Dataline &dataline) {
            os << dataline.system_time << ";\t" << dataline.myo << ";\t"
               << dataline.myo_time << ";\t" << dataline.glove << ";\t" << dataline.glove_time
               << ";\t" << dataline.movement << ";\t'" << dataline.message << "';\t"
               << dataline.pressed_key;
            return os;
        }
    };
    //int max_myo, min_myo;
	//float max_glove, min_glove;
    std::string basename;
    std::string place;
	int readline;
	int partition;
    std::vector<Dataline> Data;
	std::ofstream f;

	void make_file(){
		std::cout<<" SREAAAAM!   ";
        if (Data.empty()) return;
        std::string name = to_string(partition);
        name = place + '/' + basename + name + ".txt";
        std::ofstream outfile;
        outfile.open(name.c_str() ); //, std::ofstream::out);
        Vertical_read(outfile, Data);
        outfile.close();
        partition++;
        readline = 0;
        Data.clear();
        std::cout<<" SREAAAAM!"<<std::endl;
    };
    void create_place(){
        std::string temp = //"./" +
                 place;
        const int dir_err = mkdir(temp.c_str());
        if(dir_err == -1) std::cerr << " Error : " << std::strerror(errno) << std::endl;
        //bool mess = CreateDirectory(
        //[in]
        //    temp.c_str(), NULL
        //);
        //if (mess) std::cout<<"directory created"<<std::endl;
    }
    void correct_readline(){
        readline=Data.size();
    }
public:
    Datalogger(std::string dirplace){
        partition = 0;
        readline = 0;
		basename = "data_";
        place = dirplace;
        create_place();
        //Data.push_back(Dataline());
    };
    ~Datalogger(){};

    bool check_readline(){
        return readline==Data.size();
    }

	void new_line(){
        if (readline==max_buffer)make_file();
        Data.push_back(Dataline());
        readline++;
    };
    void end(){
        Data.pop_back();
        make_file();
    }
	void set_system_time(float t)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].system_time = t;};
	void set_myo(std::vector<int> v)
	{if (readline==0)Data.push_back(Dataline()); 
		correct_readline();
        Data[Data.size()-1].myo = v;};
	void set_myo(int* v, int size)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].myo = Array_to_vector(v, size);};
	void set_myo_time(uint64_t mt)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].myo_time = mt;};
	void set_glove(	std::vector<double> all_joint)
	{if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].glove = all_joint;};
	void set_glove_time( double gt)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].glove_time = gt;};
	void set_movement(std::string mov)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].movement = mov;};
	void set_message(std::string mess)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].message = mess;};
	void set_pressed_key(std::string key)
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].pressed_key = key;}

    friend std::ostream &operator<<(std::ostream &os, const Datalogger &datalogger) {
        os << datalogger.Data;
        return os;
    };
	void push(Ticks data){
		f<<data<< ";\t";
	}
	void push(int& data){
		f<<data<< ";\t";
	}
	void push(float& data){
		f<<data<< ";\t";
	}
	void push(uint64_t& data){
		f<<data<< ";\t";
	}
	void push(double& data){
		f<<data<< ";\t";
	}
	
	void push(std::vector<int>& data){
		f<<data<< ";\t";
	}
	void push(std::string& data){
		f<<data<< ";\t";
	}
	void push(Ticks& data){
		f<<data<< ";\t";
	}
	void push_sub(int& data){
		f<<data<< ", ";
	}
	void push_sub(double& data){
		f<<data<< ", ";
	}
	void push_line(){
		f<<"\n";
	}
	void reset_file(std::string& name){
		f.close();
        std::string fname= place + '/' + basename + to_string(partition)+"_"+ name + ".txt";
        f.open(fname.c_str() ); //, std::ofstream::out);
        //Vertical_read(outfile, Data);
        partition++;
        readline = 0;
        //Data.clear();
        //std::cout<<" SREAAAAM!"<<std::endl;
	}
	void close(){
		f.close();
        std::cout<<" end!"<<std::endl;
	}
	void open(std::string& name){
		std::string fname= place + '/' + basename + name + to_string(partition) + ".txt";
        f.open(fname.c_str() );;
        std::cout<<" open!"<<std::endl;
	}
	void open(char* name){
		std::string fname = name;
		fname = place + '/' + basename + fname + to_string(partition) + ".txt";
        f.open(fname.c_str() );;
        std::cout<<" open!"<<std::endl;
	}
};
#endif //CPPTESTER_DATALOGGER_H