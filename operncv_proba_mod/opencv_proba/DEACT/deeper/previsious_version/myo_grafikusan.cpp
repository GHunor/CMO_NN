// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.
//#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <myo/myo.hpp>

#include "opencv/cv.h"
#include "opencv/highgui.h"

using namespace cv;

class DataCollector : public myo::DeviceListener {
public:
	std::vector<int> emgSamples;
	Mat kep;
	DataCollector() : emgSamples(8, 0)
    //: emgSamples()
    {
		kep = Mat::zeros(8, 100, CV_8U); // CV_16S --> short; CV_8S --> signed char; CV_8U --> unsigned char
		for (int idx=0; idx<kep.cols; idx++) {
			kep.col(idx) = 2*idx;
		}
    }
    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
        //emgSamples.fill(0);
		for (int i=0; i<8; i++) {
			emgSamples[i] = 0;
		}
    }
    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {
        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }
		//std::cout << "#####\n";
    }
    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.
    // We define this function to print the current values that were updated by the on...() functions above.
    void print()
    {
        /*
		// Clear the current line
        std::cout << '\r';
        // Print out the EMG data.
        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            //oss << static_cast<int>(emgSamples[i]);
            oss << emgSamples[i];
			std::string emgString = oss.str();
            std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
        }
        std::cout << std::flush;
		*/
		for (int idx=0; idx<8; idx++) {
			std::cout << '\t' << emgSamples[idx];
		}
		std::cout << '\n';

		for (int i=0; i<kep.cols-1; i++) {
			kep.col(i+1).copyTo(kep.col(i));
		}
		for (int i=0; i<8; i++) {
			kep.at<unsigned char>(i, kep.cols-1) = static_cast<int>(emgSamples[i]) + 128;
		}


    }
    // The values of this array is set by onEmgData() above.
    //std::array<int8_t, 8> emgSamples;
	
};
int main(int argc, char** argv)
{
    // We catch any exceptions that might occur below -- see the catch statement for more details.
	myo::Hub hub("com.example.emg-data-sample");
	DataCollector collector;
    try {
    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    
    std::cout << "Attempting to find a Myo..." << std::endl;
    // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
    // immediately.
    // waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
    // if that fails, the function will return a null pointer.
    myo::Myo* myo = hub.waitForMyo(10000);
    // If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
    if (!myo) {
        throw std::runtime_error("Unable to find a Myo!");
    }
    // We've found a Myo.
    std::cout << "Connected to a Myo armband!" << std::endl << std::endl;
    // Next we enable EMG streaming on the found Myo.
    myo->setStreamEmg(myo::Myo::streamEmgEnabled);
    // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
    
    // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
    // Hub::run() to send events to all registered device listeners.
    hub.addListener(&collector);

	namedWindow("emg_kep", WINDOW_NORMAL);

    // Finally we enter our main loop.
    // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        //return 1;
    }
	while (1) {
        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
        //hub.run(1000/20);
		hub.run(25);
		// After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
        collector.print();

		
		// WINDOW_NORMAL cv namedwindow-nal a flag
		imshow("emg_kep", collector.kep);
		waitKey(1);
    }
}