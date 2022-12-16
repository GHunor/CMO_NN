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

#include <myo/myo.hpp>
#include <vhtBase.h>

#include "DataCollector.hpp"
#include "Datalogger.hpp"
//#include "Timer.hpp"
#include "Coordinator.hpp"
//#include "DHub.hpp"

#include "opencv/cv.h"
#include "opencv/highgui.h"

#define _WIN32_WINNT 0x0400			// avoid winsock problem
;using std::cout;


using namespace cv;


#define PI (355/113)


class DHubI : public myo::Hub {
public:
	DHubI(){};
	void Set(const std::string& applicationIdentifier){
		myo::Hub::Hub(applicationIdentifier);
		//libmyo_init_hub(&_hub(0), applicationIdentifier.c_str(), ThrowOnError());
	};
};

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

int main(int argc, char** argv)
{

    /// Armband connect
    int sect = 0;
    bool first = true;
	bool isMyo, isGlove, isOPF1, isOPF2, isOPF3;
	DataCollector collector;
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
    //Section 1
    sect++;
	DHubP hub;
    try{
		//
		
		hub.Set("com.example.emg-data-sample", &collector);

        //DHub hub("com.example.emg-data-sample");
		//myo::Hub hub("com.exampl.emg-data-sample");
		//bool hub_working = 1;
		/*try{
			myo::Myo* myo = hub.waitForMyo(10000);
			cout << "Attempting to find a Myo..." << std::endl;
			isMyo = true;
			if (!myo) {
				isMyo = false;
				//throw std::runtime_error("Unable to find a Myo!");
				cout << "Unable to find a Myo!"<< std::endl;
			}
			cout << "Connected to a Myo armband!" << std::endl << std::endl;
			myo->setStreamEmg(myo::Myo::streamEmgEnabled);

			//hub.set_streaming();
			//Section 2
			sect++;

			hub.addListener(&collector);
			cout<<"Myo armband connected and ready to stream"<<std::endl;
		}
		catch (const std::exception& e) {
				hub_working = 0;
				std::cout << "Error: " << e.what() << std::endl;
		}
		catch (vhtBaseException * e) {
        std::cerr << "Error: Main Loop at section" << sect << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        //return 1;
		}
		*/
        //Section 3
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
        //return 1;
    }
	catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
		collector.NoMyo();
        //return 1;
    }

        //Section 4
        sect++;

        namedWindow("emg_kep", WINDOW_NORMAL);
        // Finally we enter our main loop.
        std::ofstream outfile;
        outfile.open("dummy.txt"); //, std::ofstream::out);

        //Section 5
        sect++;
        int bookmark = 0;
        int pressed_X = 0, pressed_R = 0, pressed_P = 0;

        //empty  checks unix time every change, and counts when it changes  -> bookmarks?
        //button press starts the measurement
        //prepare
        //move
        //stop
        //cooldown
        //repeat

        //every few times another empty
        //by button press can be paused
        //by button press can be ended
        //by button press can the last one repeated (current if it's in the middle)



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

		///===========================================================
		///CYCLE BEGINS HERE
		///===========================================================
        while (1) {

            
            //Message = COOR.message();
            //Movement = COOR.curr_state();
            // kiir, vagy frissit


            //Section 6
            if(first)sect++;

            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            hub.run(1000/20);
			//alt if(hub_working){hub.run(25);}else{Sleep(25);};
            collector.GloveAndTrackerUpdate();

            //Section 7
            if(first)sect++;

            Log.push(timer.Time());
            collector.log(outfile, Log, hand, gtime);
			Log.push(Message);
			Log.push(Movement);
			Log.push(PressedKey);
			if(!COOR.isPaused){
				if(!COOR.isWait){
				Log.push(0);
				}else{
				Log.push(1);
				}
			}else
			{
				Log.push(2);
			}
			Log.push_line();
            //Log.set_system_time(timer.Time());
			//Log.set_message(Message);
			//Log.set_movement(Movement);
			//Log.set_pressed_key(PressedKey);
			//Log.new_line();

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

            if(GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_X < 1)
            {
                pressed_X++;
                //Log.end();
				Log.close();
				PressedKey = "X";
                break;
            }
            if(pressed_X<20 && pressed_X>0){pressed_X++;}
            if(pressed_X==20){pressed_X = 0;PressedKey = "";}

            if(GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_R < 1)
            {
                pressed_R++;
                COOR.Repeat_last();
				PressedKey = "R";
            }
            if(pressed_R<20 && pressed_R>0){pressed_R++;}
            if(pressed_R==20){pressed_R = 0;PressedKey = "";}

            if(GetKeyState('P') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_P <1)
            {
                pressed_P++;
                COOR.Pause();
				PressedKey = "P";
            }
            if(pressed_P<20 && pressed_P>0){pressed_P++;}
            if(pressed_P==20){pressed_P = 0;PressedKey = "";}

            // WINDOW_NORMAL cv namedwindow-nal a flag
            imshow("emg_kep", collector.kep);

            //Section 9
            if(first)sect++;

            waitKey(1);

            //Section 10
            if(first)sect++;
            first = false;
            if (COOR.isDone()) break;
        }
        std::cout<<iter<<std::endl;
        std::cout << std::asctime(std::localtime(&result))
                  << result << " seconds since the Epoch\n";
        //outfile.close();
        // If a standard exception occurred, we print out its message and exit.
	
    
	return 0;
}

void imshow(const char *string, Mat mat) {

}
