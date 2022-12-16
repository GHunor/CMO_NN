// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.
//#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
//#include <ccomplex>
#include <ostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <algorithm>

#include <myo/myo.hpp>
#include <vhtBase.h>
#include "optoforce.h"

#include "prompt_handler.hpp"
//#include "useful_macros.h"
#include "keypress_handler.hpp"
//#include "opcv_handler.h"
#include "Coordinator.hpp"
#include "Datalogger.hpp"
#include "DataCollector.hpp"


#include "opencv/cv.h"
#include "opencv/highgui.h"

#define _WIN32_WINNT 0x0400			// avoid winsock problem
;using std::cout;

using namespace cv;


#define PI (355/113)


class DHubP{
myo::Hub* hub;
bool hub_working;
public:
	DHubP(){};
	void Set(std::string name, myo::DeviceListener* collector){
		hub_working = 1;
		try{
			bool isMyo;
			hub = new myo::Hub(name);
			myo::ThrowOnError();
			int bah = 100;
			myo::Myo* myo = hub->waitForMyo(10000);
			cout << "Attempting to find a Myo..." << std::endl;
			isMyo = true;
			if (!myo) {
				isMyo = false;
				hub_working = false;
				//throw std::runtime_error("Unable to find a Myo!");
				cout << "Unable to find a Myo!"<< std::endl;
			}
			cout << "Connected to a Myo armband!" << std::endl << std::endl;
			myo->setStreamEmg(myo::Myo::streamEmgEnabled);

			hub->addListener(collector);
			cout<<"Myo armband connected and ready to stream"<<std::endl;

		}
		catch (const std::exception& e) {
			hub_working = 0;
			std::cout << "Error: " << e.what() << std::endl;
		}
		catch (...) {
			hub_working = 0;
			std::cout << "Error:  great filter " //<< e.what() 
				<< std::endl;
		}

	};
	myo::Myo* waitForMyo(int msec){
		myo::Myo* ret;
		if(hub_working){
			try{
				ret = hub->waitForMyo(msec);
			}
			catch (const std::exception& e) {
				hub_working = 0;
			}
		}
		return ret;
	};


	void set_streaming(){
		try{
			myo::Myo* myo = hub->waitForMyo(10000);
			cout << "Attempting to find a Myo..." << std::endl;
			bool isMyo = true;
			if (!myo) {
				isMyo = false;
				//throw std::runtime_error("Unable to find a Myo!");
				cout << "Unable to find a Myo!"<< std::endl;
			}
			cout << "Connected to a Myo armband!" << std::endl << std::endl;
			if (hub_working) myo->setStreamEmg(myo::Myo::streamEmgEnabled);
		}
		catch (const std::exception& e) {
				hub_working = 0;
		}

        //Section 2
        //sect++;

        //hub.addListener(&collector);
        //cout<<"Myo armband connected and ready to stream"<<std::endl;
	};

	void addListener(myo::DeviceListener* collector){
		hub->addListener(collector);
	};
	void run(int msec){
		if (hub_working){
			hub->run(msec);
			return;
		}
		Sleep(msec);
	};
	bool Is_working(){
		return hub_working;
	}
};
void Seed(){
    srand((unsigned) time(0));
};
int create_random(){
    return rand();
};
std::vector<int> create_random(int size){
    std::vector<int> ret(size);
    for IRANGE(size){
        ret[i] = rand();
    }
    return ret;
};
template<class T>
std::vector<double> devide(std::vector<T> A, T qw){
    std::vector<double> ret(A.size());
    for IRANGE(A.size()){
        ret[i] = A[i]/qw;
    }
    return ret;
}
void imshow(const char *string, Mat mat) {

}


struct blabla{
    std::ofstream myfile;
    std::string place;
    blabla(){};
    //blabla(std::string fname){myfile.open((place + "/" + fname).c_str());}
    void set_place(std::string Pname){
        place = Pname;
        create_directories(place);
    }
    void open(std::string fname){
        create_directories(place);
        myfile.open ((place + "/" + fname).c_str());
        //if(myfile.fail()) {std::cout<<"what is missing???\n";std::cin.ignore();}
    }
    void close(){
        myfile.close();
    }
    void refresh(std::string fname){
        myfile.close();
        myfile.open ((place + "/" + fname).c_str());
    }
	/*
    void push(std::string data){
        myfile << data;
    }
	*/
	void push(const Timer::Ticks& data){
        float tmp = Timer::ms(data);
        myfile<<tmp<< ",\t";
    }
    void push(const int& data){
        float tmp = data;
        myfile<<tmp<< ",\t";
    }
    void push(const float& data){
        myfile<<data<< ",\t";
    }
    void push(const uint64_t& data){
        float tmp = data;
        myfile<<tmp<< ",\t";
    }
    void push(const double& data){
        float tmp = data;
        myfile<<tmp<< ",\t";
    }
    template<class T>
    void push(std::vector<T> data){
        float tmp;
        for IRANGE(data.size()){
            tmp = data[i];
            myfile<<tmp<< ",\t";
        }
    }
    template<class T>
    void push(std::vector<T> data, int start){
        float tmp;
        for (int i=start; i<data.size(); i++){
            tmp = data[i];
            myfile<<tmp<< ",\t";
        }
    }
    void push(const std::string& data){
        myfile<<data<< ",\t";
    }
    void push_state(const int& data){
        myfile<<data<< ",\t";
    }
    void push_line(){
        myfile<<"\n";
    }
	void create_infotxt(std::string title){
        std::string fname = place + '/' + title + "_infos.txt";
        myfile.open(fname.c_str() );
        std::cout<<" open!"<<std::endl;
        myfile<<"This is the header (vertically) for the " <<place<< " measurement\n";
        myfile<<"Main State:\n \t0: Initial state, lasts: " << 100 << " seconds\n" <<
                         "\t1: Prepare to move state, lasts: " << 5 << " seconds\n" <<
                         "\t2: Move state, lasts: " << 10 << " seconds\n" <<
                         "\t3: Break state, lasts: " << 400 << " seconds\n" <<
                         "\t -1: Pause state, lasts: indefinite seconds\n";
        myfile<<"Move ID:\n";
        
        myfile<<"Computer time difference (ms)\n";

        myfile<<"EMGsamples (8 data 8bit resolution)\n";
        myfile<<"EMGtime (1 data)\n";
        
        myfile<<"VHT or Glove (20 data double in radian):\n \t Finger1 2 side to side (thumb MCP)\n" <<    ///need to be fixed
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
        myfile<<"VHT or Glove time (maybe useless)\n";
        
        myfile<<"Optoforce1 (16 bit resolution)\n" <<
                                     "\t  Internal clock time\n"  <<
                                     "\t  X axis\n"  <<
                                     "\t  Y axis\n"  <<
                                     "\t  Z axis\n";

        myfile<<"Optoforce2 (16 bit resolution)\n" <<
                                     "\t  Internal clock time\n"  <<
                                     "\t  X axis\n"  <<
                                     "\t  Y axis\n"  <<
                                     "\t  Z axis\n";

        myfile<<"Optoforce3 (16 bit resolution)\n" <<
                                     "\t  Internal clock time\n"  <<
                                     "\t  X axis\n"  <<
                                     "\t  Y axis\n"  <<
                                     "\t  Z axis\n";
        myfile.close();
    }
};
class Interval
{
private:
    unsigned int initial_;

public:
    inline Interval() : initial_(GetTickCount()){}
    virtual ~Interval(){}

    inline unsigned int value() const
    {
        return GetTickCount()-initial_;
    }
};

int main(int argc, char** argv)
{
	Seed();
    int sect = 0;
    ///init
    //Section 0
    promthandler ph;
    keypress_handler kh;
    blabla lg;
    kh.Add_key('X', 20);
    kh.Add_key('R', 20);
    kh.Add_key('P', 20);
    kh.Create_key_bools();

    std::string title, directory;
    int opt1, opt2, opt3;

    ///input
    //Section 1


    sect++;
    ph << "Directory name please: \n";
    directory = ph.askfor_string();
    ph << "Name for the measurement? \n";
    title = ph.askfor_string();
    ph << "Which COM is optoforce 1? \n";
    opt1 = ph.askfor_int();
	//opt1 = 3;
    ph << "Which COM is optoforce 2? \n";
    opt2 = ph.askfor_int();
	//opt2 = 4;
    ph << "Which COM is optoforce 3? \n";
    opt3 = ph.askfor_int();
	//opt3 = 5;


    coordinator co(directory);
    lg.set_place(directory + "/meas");
    //lg.Give_title(title);
    std::string file_title;
    file_title = co.OutTitle();
    std::replace( file_title.begin(), file_title.end(), ' ', '_');
	int section = 0;
	file_title = title + "_" + to_string(section) + "__" + file_title + ".txt";
    lg.open(file_title);
    //Timer tm;
	OpCV_handler ocv;
	bool isMyo = true, isGlove = true, isOPF1 = true, isOPF2 = true, isOPF3 = true;
    /*
	

    Datalogger Log("D:/measurement");
    std::string tstr = "movements_list.txt";
    coordinator COOR(tstr.c_str());
	int second = 22;
    int amount = 100;
    int free_run = 120, wait = 4, movement_length = 6;

    COOR.rhythim_setter(second, free_run*second, wait*second, movement_length*second, amount);
    int temp = COOR.get_max_state_num()*(movement_length+wait);
    temp += 41;
    COOR.statelist_maker(3600/temp);
	std::vector<double> hand(23,0);
    */
    sect++;
    /// Armband connect
    //Section 2

    DataCollector collector;
	DHubP hub;
    try{
		hub.Set("com.example.emg-data-sample", &collector);
		sect++;
	}
	catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
		collector.NoMyo();
        //lg.N0_myo();
		ocv.NoMyo();
		isMyo = false;
        //return 1;
    }
	if(!hub.Is_working()){//lg.N0_myo();
		ocv.NoMyo();
		isMyo = false;
	};
	try{
		///=============================================================
		///BIG TROUBLE HERE
		///=============================================================
        if (!collector.GetGlove() ) return 1;
			/// I need a throw here or removing the whole thing from try...

			//collector.GetTracker();
        collector.tracker = new vhtTrackerEmulator();
		} 
	catch (vhtBaseException * e) {
        std::cerr << "Error: Main Loop at section " << sect << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
		collector.NoGlove();
        //lg.N0_vht();
		ocv.NoGlove();
		isGlove = false;
        //return 1;
    }

    //lg.create_infotxt(&co);

    sect++;
    ///pre CV
    //Section 3
    namedWindow("emg_kep", WINDOW_NORMAL);

    ///optoforces
	string tmp_string = "COM"+ to_string(opt1);
	string tmp_string2 = "opto1";
    optoforce opf1(tmp_string.c_str(),tmp_string2.c_str() );

	tmp_string = "COM"+ to_string(opt2); tmp_string2 = "opto2";
	optoforce opf2(tmp_string.c_str(),tmp_string2.c_str());

	tmp_string = "COM"+ to_string(opt3); tmp_string2 = "opto3";
	optoforce opf3(tmp_string.c_str(),tmp_string2.c_str());

    if(!opf1.Connected()){//lg.N0_opt1(); 
		ocv.NoOpt1();
		isOPF1 = false;
	};
    if(!opf2.Connected()){//lg.N0_opt2(); 
		ocv.NoOpt2();
		isOPF2 = false;
	};
    if(!opf3.Connected()){//lg.N0_opt3(); 
		ocv.NoOpt3();
		isOPF3 = false;
	};
    std::vector<int> opfv1, opfv2, opfv3;

    ///===========================================================
    ///CYCLE BEGINS HERE
    ///===========================================================
    bool first = true;

	std::cerr << "Press enter to continue.";
    std::cin.ignore();
	ph.total_wipe();
	ph<<co.OutMessage();
    ph.new_line();
	ph<<"Move: "<<co.Current_move();
    ph.new_line();
	ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;
	Interval tm;
	//
        while (1) {

            //Section 6
            if(first)sect++;
            ///================================================
            ///
            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            hub.run(1000/20);
			//alt if(hub_working){hub.run(25);}else{Sleep(25);};


            //Section 6
            if(first)sect++;
            ///coordinator update

            if (co.Update()){
                if (co.Is_end()) {lg.close();
				break;}
				if (co.ID_curr>co.Move_list_size-2){
					ph<<"\n_-hah-_\n";
				}
				ph.total_wipe();
                ph<<co.OutMessage();
                ph.new_line();
				ph<<"Move: "<<co.Current_move();
                ph.new_line();
				ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;
                
				if (co.Num_of_MS() != Main_states::Move){
					file_title = co.OutTitle();
					std::replace( file_title.begin(), file_title.end(), ' ', '_');
					section++;
					file_title = title + "_" + to_string(section) + "__" + file_title + ".txt";
					lg.refresh(file_title);
				}
				ph.solidify();
                
            }
            ph.clean();
			ph.clean();
            //ph.new_line();
			std::cout<<"Counter: "<<co.Get_counter()<<"  |   ";
			//ph.new_line();
            ph<<"Global_Counter: "<<co.ID_curr<<"  |   ";
            //ph.new_line();
			std::cout<<"Percentage (Time): "<<co.Get_precentage_time()<<"  |   ";
			//ph.solidify();
            sect++;
            ///push data to logger
            //Section 7

            ///Main_State

			lg.push_state(co.Num_of_MS());
            ///Move
            lg.push_state(co.Num_of_move());
            ///Computer timer
            lg.push(int(tm.value()));
            if(isMyo){
                ///Myo timer
                lg.push(collector.Get_Myo_time());
                ///Myo Data
                lg.push(collector.Get_Myo_vec());
            }
            collector.GloveAndTrackerUpdate();
            if(isGlove){
                ///glove timer
                lg.push(collector.Get_glove_time());
                ///glove data
                lg.push(collector.Get_glove_data_all());
            }
            if(isOPF1) {
                opfv1 = opf1.Get_vector();
                ///opt1 time
                lg.push(opfv1[0]);
                ///opt1 data
                lg.push(opfv1, 1);
            }
            if(isOPF2) {
                opfv2 = opf2.Get_vector();
                ///opt2 time
                lg.push(opfv2[0]);
                ///opt2 data
                lg.push(opfv2, 1);
            }
            if(isOPF3) {
                opfv3 = opf3.Get_vector();
                ///opt3 time
                lg.push(opfv3[0]);
                ///opt3 data
                lg.push(opfv3, 1);
            }
            lg.push_line();
            ///
            ///================================================
            
            //Section 8
            if(first)sect++;

            kh.Do();
            if (kh.key_bools2[0]) {
				ph<< "X pressed "; 
				std::cerr << "                                               Are you sure you want to end the measurement? (y or x means yes, anything else is no) ";
				char tmp;
				std::cin>>tmp;
				if (tmp == 'y' || tmp == 'x'){lg.close(); break;}else{ph<< "going on";}
				
			}  ///will end
            if (kh.key_bools2[1]) {
                ph<< "R pressed ";
                if (co.Repeat()) {
                    file_title = co.OutTitle();
                    std::replace( file_title.begin(), file_title.end(), ' ', '_');
					section++;
					file_title = title + "_" + to_string(section) + "__" + file_title + "_reped.txt";
                    lg.refresh(file_title);

                }
				ph.total_wipe();
				ph<<co.OutMessage();
				ph.new_line();
				ph<<"Move: "<<co.Current_move();
				ph.new_line();
				ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;
            } ///resets coor and log
            if (kh.key_bools2[2]) {
                ph<< "P pressed ";
                if(co.Pause()){

					ph.total_wipe();
					ph<<co.OutMessage();
					ph.new_line();
					//ph<<"Move: "<<co.Current_move();
					ph.new_line();
					ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;

                    section++;
					file_title = title + "_" + to_string(section) + "__" + "pause.txt";
					lg.refresh(file_title);
                }else{
					ph.total_wipe();
					ph<<co.OutMessage();
					ph.new_line();
					ph<<"Move: "<<co.Current_move();
					ph.new_line();
					ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;
					file_title = co.OutTitle();
					std::replace( file_title.begin(), file_title.end(), ' ', '_');
					section++;
					file_title = title + "_" + to_string(section) + "__" + file_title + ".txt";
                    lg.refresh(file_title);
                }
            };
            // WINDOW_NORMAL cv namedwindow-nal a flag

            ///=============================
			
            imshow("emg_kep", collector.kep);
            waitKey(1);
            ///=============================

            //Section 10
            if(first)sect++;
            first = false;
            //if (COOR.isDone()) break;
        }
        //std::cout<<iter<<std::endl;
        //std::cout << std::asctime(std::localtime(&result))
        //          << result << " seconds since the Epoch\n";
        //outfile.close();
        // If a standard exception occurred, we print out its message and exit.
	
    
	return 0;
	/*
	Timer tmt;
	blabla bla;
    //mkdir("dier");
	
    bla.set_place("dier/dier2");
	bla.create_infotxt("test");
    bla.open("example.txt");
    bla.push("Writing this to a file.\n");
	bla.push_line();
	bla.push_state(1);
	bla.push_line();
	bla.push_state(5);
	bla.push_line();
	bla.push(tmt.ms());
	bla.push(create_random());
        ///Myo Data
        bla.push(create_random(8));
        ///glove timer
        bla.push(create_random()/3);
        ///glove data
        bla.push(
                devide(
                        create_random(23),3));
        ///opt1 time
        bla.push(create_random());
        ///opt1 data
        bla.push(create_random(3));
        ///opt2 time
        bla.push(create_random());
        ///opt2 data
        bla.push(create_random(3));
        ///opt3 time
        bla.push(create_random());
        ///opt3 data
        bla.push(create_random(3));
        bla.push_line();
    bla.refresh("example2.txt");
    bla.push("Writing this to a file sjkahfjksd.\n");
    bla.close();
    return 0;*/

	/*
	Seed();
    int sect = 0;
    ///init
    //Section 0
    promthandler ph;
    keypress_handler kh;
    DataloggerS lg;
    kh.Add_key('X', 20);
    kh.Add_key('R', 20);
    kh.Add_key('P', 20);
    kh.Create_key_bools();

    std::string title, directory;
    int opt1, opt2, opt3;

    ///input
    //Section 1


    sect++;
    ph << "Directory name please: \n";
    directory = ph.askfor_string();
    ph << "Name for the measurement? \n";
    title = ph.askfor_string();
    ph << "Which COM is optoforce 1? \n";
    opt1 = ph.askfor_int();
	//opt1 = 3;
    ph << "Which COM is optoforce 2? \n";
    opt2 = ph.askfor_int();
	//opt2 = 4;
    ph << "Which COM is optoforce 3? \n";
    opt3 = ph.askfor_int();
	//opt3 = 5;


    coordinator co(directory);
    lg.Give_place(directory);
    lg.Give_title(title);
    std::string file_title;
    file_title = co.OutTitle();
    std::replace( file_title.begin(), file_title.end(), ' ', '_');
    lg.open(file_title);
    Timer tm;
	OpCV_handler ocv;
	bool isMyo, isGlove, isOPF1, isOPF2, isOPF3;
    sect++;
    /// Armband connect
    //Section 2

    DataCollector collector;
	DHubP hub;
    try{
		hub.Set("com.example.emg-data-sample", &collector);
		sect++;
	}
	catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
		collector.NoMyo();
        lg.N0_myo();
		ocv.NoMyo();
        //return 1;
    }
	if(hub.Is_working()){lg.N0_myo();ocv.NoMyo();};
	try{
		///=============================================================
		///BIG TROUBLE HERE
		///=============================================================
        if (collector.GetGlove() ) return 1;
			/// I need a throw here or removing the whole thing from try...

			//collector.GetTracker();
        collector.tracker = new vhtTrackerEmulator();
		} 
	catch (vhtBaseException * e) {
        std::cerr << "Error: Main Loop at section " << sect << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
		collector.NoGlove();
        lg.N0_vht();
		ocv.NoGlove();
        //return 1;
    }

    lg.create_infotxt(&co);

    sect++;
    ///pre CV
    //Section 3
    namedWindow("emg_kep", WINDOW_NORMAL);

    ///optoforces
	string tmp_string = "COM"+ to_string(opt1);
	string tmp_string2 = "opto1";
    optoforce opf1(tmp_string.c_str(),tmp_string2.c_str() );

	tmp_string = "COM"+ to_string(opt2); tmp_string2 = "opto2";
	optoforce opf2(tmp_string.c_str(),tmp_string2.c_str());

	tmp_string = "COM"+ to_string(opt3); tmp_string2 = "opto3";
	optoforce opf3(tmp_string.c_str(),tmp_string2.c_str());

    if(!opf1.Connected()){lg.N0_opt1(); ocv.NoOpt1();};
    if(!opf2.Connected()){lg.N0_opt2(); ocv.NoOpt2();};
    if(!opf3.Connected()){lg.N0_opt3(); ocv.NoOpt3();};
    std::vector<int> opfv1, opfv2, opfv3;

    ///===========================================================
    ///CYCLE BEGINS HERE
    ///===========================================================
    bool first = true;

	std::cerr << "Press enter to continue.";
    std::cin.ignore();
	ph.total_wipe();
	ph<<co.OutMessage();
    ph.new_line();
	ph<<"Move: "<<co.Current_move();
    ph.new_line();
	ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;
	//
        while (1) {

            //Section 6
            if(first)sect++;
            ///================================================
            ///
            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            hub.run(1000/20);
			//alt if(hub_working){hub.run(25);}else{Sleep(25);};


            //Section 6
            if(first)sect++;
            ///coordinator update

            if (co.Update()){
                if (co.Is_end()) {lg.close();
				break;}
				if (co.ID_curr>co.Move_list_size-2){
					ph<<"\n_-hah-_\n";
				}
				ph.total_wipe();
                ph<<co.OutMessage();
                ph.new_line();
				ph<<"Move: "<<co.Current_move();
                ph.new_line();
				ph<<"Percentage: "<<co.Get_precentage_moves()<<" "<<co.ID_curr/co.Move_list_size;
                
				if (co.Num_of_MS() != Main_states::Move){
					file_title = co.OutTitle();
					std::replace( file_title.begin(), file_title.end(), ' ', '_');
					lg.reset_file(file_title);
				}
				ph.solidify();
                
            }
            ph.clean();
			ph.clean();
            //ph.new_line();
			std::cout<<"Counter: "<<co.Get_counter()<<"  |   ";
			//ph.new_line();
            ph<<"Global_Counter: "<<co.ID_curr<<"  |   ";
            //ph.new_line();
			std::cout<<"Percentage (Time): "<<co.Get_precentage_time()<<"  |   ";
			//ph.solidify();
            sect++;
            ///push data to logger
            //Section 7

            ///Main_State

			lg.push_state(co.Num_of_MS());
            ///Move
            lg.push_state(co.Num_of_move());
            ///Computer timer
            lg.push(tm.ms());
            if(lg.myo){
                ///Myo timer
                lg.push(collector.Get_Myo_time());
                ///Myo Data
                lg.push(collector.Get_Myo_vec());
            }
            collector.GloveAndTrackerUpdate();
            if(lg.vht){
                ///glove timer
                lg.push(collector.Get_glove_time());
                ///glove data
                lg.push(collector.Get_glove_data_all());
            }
            if(lg.opt1) {
                opfv1 = opf1.Get_vector();
                ///opt1 time
                lg.push(opfv1[0]);
                ///opt1 data
                lg.push(opfv1, 1);
            }
            if(lg.opt2) {
                opfv2 = opf2.Get_vector();
                ///opt2 time
                lg.push(opfv2[0]);
                ///opt2 data
                lg.push(opfv2, 1);
            }
            if(lg.opt3) {
                opfv3 = opf3.Get_vector();
                ///opt3 time
                lg.push(opfv3[0]);
                ///opt3 data
                lg.push(opfv3, 1);
            }
            lg.push_line();
            ///
            ///================================================
            
            //Section 8
            if(first)sect++;

            kh.Do();
            if (kh.key_bools2[0]) {
				ph<< "X pressed "; 
				std::cerr << "                                               Are you sure you want to end the measurement? (y or x means yes, anything else is no) ";
				char tmp;
				std::cin>>tmp;
				if (tmp == 'y'){lg.close(); break;}else{ph<< "going on";}
				
			}  ///will end
            if (kh.key_bools2[1]) {
                ph<< "R pressed ";
                if (co.Repeat()) {
                    file_title = co.OutTitle();
                    std::replace( file_title.begin(), file_title.end(), ' ', '_');
                    lg.reset_file_rep(file_title);
                }
            } ///resets coor and log
            if (kh.key_bools2[2]) {
                ph<< "P pressed ";
                if(co.Pause()){
                    lg.reset_file("pause");
                }else{
                    file_title = co.OutTitle();
                    std::replace( file_title.begin(), file_title.end(), ' ', '_');
                    lg.reset_file("pause");
                }
            };
            // WINDOW_NORMAL cv namedwindow-nal a flag

            ///=============================
			
            imshow("emg_kep", collector.kep);
            waitKey(1);
            ///=============================

            //Section 10
            if(first)sect++;
            first = false;
            //if (COOR.isDone()) break;
        }
        //std::cout<<iter<<std::endl;
        //std::cout << std::asctime(std::localtime(&result))
        //          << result << " seconds since the Epoch\n";
        //outfile.close();
        // If a standard exception occurred, we print out its message and exit.
	
    
	return 0;
	*/
}

