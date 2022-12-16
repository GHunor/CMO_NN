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

#include "dummy/myo.hpp" //<myo.hpp>
#include "dummy/vhtBase.h" //<vhtBase.h>

#include "DataCollector.hpp"
#include "Datalogger.hpp"
#include "Timer.hpp"

#include "dummy/opencv/cv.h" //"opencv/cv.h"
#include "dummy/opencv/highgui.h"  //"opencv/highgui.h"

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
        outfile.open("data.txt"); //, std::ofstream::out);

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

        ///make speciality filebu

        double prec = TestSysTimer();
        double basesysT = get_curtime_INms();
        while (1) {


            //Section 6
            if(first)sect++;

            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            //hub.run(1000/20);
            hub.run(25);
            collector.GloveAndTrackerUpdate();

            //Section 7
            if(first)sect++;

            // After processing events, we call the print() member function we defined above to print out the values we've
            // obtained from any events that have occurred.
            collector.log(outfile, Log, hand);
            Log.set_system_time(get_curtime_INms() - basesysT);
            basesysT = get_curtime_INms();
            //Section 8
            if(first)sect++;

            if((GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/))
            {
                sect=100; //biggest

                break;
            }
            if(GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_R<20)
            {
                outfile<<" bookmark : "<<bookmark<<"\n";
                bookmark++;
                pressed_R++;
            }else{
                pressed_R = 0;
            }
            if(GetKeyState('P') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_P<20)
            {
                outfile<<" bookmark : "<<bookmark<<"\n";
                bookmark++;
                pressed_P++;
            }else{
                pressed_P = 0;
            }

            // WINDOW_NORMAL cv namedwindow-nal a flag
            imshow("emg_kep", collector.kep);

            //Section 9
            if(first)sect++;

            waitKey(1);

            //Section 10
            if(first)sect++;
            first = false;
        }
        outfile.close();
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
