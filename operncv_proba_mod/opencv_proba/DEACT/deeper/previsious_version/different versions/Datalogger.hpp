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


#include <fileapi.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
    if (vec.empty()) return os;
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

std::string to_string(int in){
	std::ostringstream convert;
	convert << in;
	return convert.str();
}

class Datalogger{
    ///BUFFERSIZE
    const static int max_buffer=15;
    ///BUFFERSIZE

    struct Dataline {
        float system_time;
        std::vector<int> myo;
        uint64_t myo_time;
        std::vector<double> glove;
        double glove_time;
        std::string movement, message, pressed_key;

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

	void make_file(){
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
    {if (readline==0)Data.push_back(Dataline()); correct_readline();
        Data[Data.size()-1].myo = v;};
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
};
#endif //CPPTESTER_DATALOGGER_H