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
#include "useful_macros.h"
#include "keypress_handler.hpp"
#include "coordinator.cpp"
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
			myo::Myo* myo = hub->waitForMyo(10000);
			cout << "Attempting to find a Myo..." << std::endl;
			isMyo = true;
			if (!myo) {
				isMyo = false;
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

int main(int argc, char** argv)
{
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
    directory = "test"; //ph.askfor_string();
    ph << "Name for the measurement? \n";
    title = "test1"; //ph.askfor_string();
    ph << "Which COM is optoforce 1? \n";
    //opt1 = ph.askfor_int();
    ph << "Which COM is optoforce 2? \n";
    //opt2 = ph.askfor_int();
    ph << "Which COM is optoforce 3? \n";
    //opt3 = ph.askfor_int();


    coordinator co(directory);
    lg.Give_place(directory);
    lg.Give_title(title);
    std::string file_title;
    file_title = co.OutTitle();
    std::replace( file_title.begin(), file_title.end(), ' ', '_');
    lg.open(file_title);
    Timer tm;

    /*
	bool isMyo, isGlove, isOPF1, isOPF2, isOPF3;

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
        //return 1;
    }
	catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
		collector.NoMyo();
        lg.N0_myo();
        //return 1;
    }

    lg.create_infotxt();

    sect++;
    ///pre CV
    //Section 3
    namedWindow("emg_kep", WINDOW_NORMAL);

    /*
    // Finally we enter our main loop.
    std::ofstream outfile;
    outfile.open("dummy.txt"); //, std::ofstream::out);

    //Section 5
    sect++;
    int bookmark = 0;
    int pressed_X = 0, pressed_R = 0, pressed_P = 0;


    int movement = COOR.curr_statei();
    int pmovement = 0, iter = 0, state_iter = 0;
    std::string &Message = COOR.message();
    std::string &Movement = COOR.curr_state();
    std::string SubMessage = "";
    std::string PressedKey = "";
    //COOR.DO(SubMessage);


    std::time_t result = std::time(NULL);
    Timer timer(true);
    float gtime = 0;
    Log.open("free_move");
    std::cout<<"CYCLE"<<std::endl;
    std::cout << std::flush;
    ///flush
    */
    ///optoforces
    optoforce opf1("COM"+ to_string(opt1),"opto1"), opf2("COM"+ to_string(opt2),"opto2"), opf3("COM"+ to_string(opt3),"opto3");
    if(!opf1.Connected()){lg.N0_opt1();};
    if(!opf2.Connected()){lg.N0_opt2();};
    if(!opf3.Connected()){lg.N0_opt3();};
    std::vector<int> opfv1, opfv2, opfv3;

    ///===========================================================
    ///CYCLE BEGINS HERE
    ///===========================================================
    bool first = true;
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
                if (co.Is_end()) {lg.close();break;}
                file_title = co.OutTitle();
                std::replace( file_title.begin(), file_title.end(), ' ', '_');
                lg.reset_file(file_title);
                ph.total_wipe()
                ph<<co.Current_move();
                ph.new_line();
                ph<<co.OutMessage();
                ph.new_line();
                ph<<co.Get_precentage_moves();
                ph.solidify();
            }
            ph.clean();
            ph.new_line();
            ph<<co.Get_counter()/40;
            ph.new_line();
            ph<<co.Get_precentage_time();
            sect++
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
            if(lg.op1) {
                opfv1 = opf1.Get_vector();
                ///opt1 time
                lg.push(opfv1[0]);
                ///opt1 data
                lg.push(opfv1, 1);
            }
            if(lg.op2) {
                opfv2 = opf2.Get_vector();
                ///opt2 time
                lg.push(opfv2[0]);
                ///opt2 data
                lg.push(opfv2, 1);
            }
            if(lg.op3) {
                opfv3 = opf3.Get_vector();
                ///opt3 time
                lg.push(opfv3[0]);
                ///opt3 data
                lg.push(opfv3, 1);
            }
            lg.push_line();
            ///
            ///================================================
            /*
            ///messages
			if(COOR.WaitEvent){
				///close and open log file
				if(COOR.isDone()){
					std::cout<<"isdone"<<std::endl;
					std::cout << std::flush;
					Log.close(); 
					break;}
				movement = COOR.curr_statei(); 
				Message = COOR.message(); 
				Movement = COOR.movement(movement);
				if(!COOR.isWait) Log.reset_file(Movement);
				if(!COOR.isWait) {
					system("cls");
					std::cout<<"STATE: "<<COOR.curr_state()<<"\nMESSAGE: "<<COOR.message()<<std::endl;
					std::cout << std::flush;
				}
				if(COOR.isWait) {
					system("cls");
					std::cout<<"STOP"<<std::endl;
					std::cout << std::flush;
				}
			}

			

            //int movement = COOR.curr_statei();
            //if(movement!=pmovement && !COOR.isWait && !COOR.isPaused){system("cls");std::cout<<"STATE: "<<COOR.curr_state()<<"\nMESSAGE: "<<COOR.message(COOR.next_move())<<std::endl;}
			if(COOR.SMEvent){
				system("cls");
				std::cout<<SubMessage<<(COOR.current_goal-COOR.own_iteration_num)/COOR.second<<std::endl;
				std::cout << std::flush;
			}

			///counter
			if (COOR.own_iteration_num%second == 0 && !COOR.isPaused){
			std::cout << '\r';
			std::cout << (COOR.current_goal-COOR.own_iteration_num)/second;
			std::cout << std::flush;
			}

            //clrscr();
			
            //int pmovement = movement;
            ///


			COOR.DO(SubMessage);

            //Section 8
            if(first)sect++;

            kh.Do();
            if (kh.key_bools2[0]) {ph<< "X pressed "; lg.close(); break;}  ///will end
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
            */
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
        std::cout<<iter<<std::endl;
        std::cout << std::asctime(std::localtime(&result))
                  << result << " seconds since the Epoch\n";
        //outfile.close();
        // If a standard exception occurred, we print out its message and exit.
	
    
	return 0;
}

