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
#include "Timer.hpp"
#include "Coordinator.hpp"

#include "opencv/cv.h"
#include "opencv/highgui.h"

#define _WIN32_WINNT 0x0400			// avoid winsock problem
using std::cout;


using namespace cv;


#define PI (355/113)




int main(int argc, char** argv)
{

    /// Armband connect
    int sect = 0;
    bool first = true;
    try {

        DataCollector collector;
        Datalogger Log("D:/measurement");
        std::string tstr = "movements_list.txt";
        coordinator COOR(tstr.c_str());

        int second = 40;
        int amount = 100;
        int free_run = 120, wait = 5, movement_length = 5;

        COOR.rhythim_setter(second, free_run*second, wait*second, movement_length*second, amount);
        int temp = COOR.get_max_state_num()*(movement_length+wait);
        temp += 41;
        COOR.statelist_maker(3600/temp);


        std::vector<double> hand(23);
        //Section 1
        sect++;

        myo::Hub hub("com.example.emg-data-sample");
        myo::Myo* myo = hub.waitForMyo(10000);
        cout << "Attempting to find a Myo..." << std::endl;
        if (!myo) {
            throw std::runtime_error("Unable to find a Myo!");
        }
        cout << "Connected to a Myo armband!" << std::endl << std::endl;
        myo->setStreamEmg(myo::Myo::streamEmgEnabled);
        //Section 2
        sect++;

        hub.addListener(&collector);
        cout<<"Myo armband connected and ready to stream"<<std::endl;
        //Section 3
        sect++;

        collector.GetGlove();
        //collector.GetTracker();
        collector.tracker = new vhtTrackerEmulator();

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
        int pmovement = movement, iter = 0, state_iter = 0;
        std::string mess = COOR.message();
        std::string Message = "";
        std::string SubMessage = "";
        COOR.DO(SubMessage);


        std::time_t result = std::time(NULL);
        Timer timer(true);
        while (1) {

            COOR.DO(SubMessage);
            Message = COOR.message();
            COOR.curr_state();
            // kiir, vagy frissit


            //Section 6
            if(first)sect++;

            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            //hub.run(1000/20);
            hub.run(25);
            collector.GloveAndTrackerUpdate();

            //Section 7
            if(first)sect++;

            
            collector.log(outfile, Log, hand);
            Log.set_system_time(timer.Time());
			Log.new_line();

            ///messages
            int movement = COOR.curr_statei();
            if(movement!=pmovement && !COOR.isWait && !COOR.isPaused){system("cls");std::cout<<"STATE: "<<COOR.curr_state()<<"\nMESSAGE: "<<COOR.message(COOR.next_move())<<std::endl;}
            if(SubMessage != "")std::cout<<SubMessage<<COOR.statelist.size()<<std::endl;
            //clrscr();

            int pmovement = movement;
            ///




            //Section 8
            if(first)sect++;

            if(GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_X < 1)
            {
                pressed_X++;
                Log.end();
                break;
            }
            if(pressed_X<20 && pressed_X>0){pressed_X++;}
            if(pressed_X==20){pressed_X = 0;}

            if(GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_R < 1)
            {
                pressed_R++;
                COOR.Repeat_last();
            }
            if(pressed_R<20 && pressed_R>0){pressed_R++;}
            if(pressed_R==20){pressed_R = 0;}

            if(GetKeyState('P') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_P <1)
            {
                pressed_P++;
                COOR.Pause();
            }
            if(pressed_P<20 && pressed_P>0){pressed_P++;}
            if(pressed_P==20){pressed_P = 0;}

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
    } catch (vhtBaseException * e) {
        std::cerr << "Error: Main Loop at section" << sect << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }

}

void imshow(const char *string, Mat mat) {

}
