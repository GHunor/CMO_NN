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
#include <cmath>
//#include <ccomplex>

#include <ostream>
#include <fstream>
#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h"

#define _WIN32_WINNT 0x0400			// avoid winsock problem
using std::cout;
#include <vhtBase.h>

using namespace cv;

#define PI (355/113)

int round(double x){
	int dec = int(x*10)%10;
	if (dec>5) {return ceil(x);}
	return floor(x);
}

double radtodeg(double rad){
	return rad/PI*180;
}

class DataCollector : public myo::DeviceListener {
public:
	std::vector<int> emgSamples;
	
	vhtIOConn *gloveDict;
	vhtCyberGlove *glove;
	vhtIOConn *trackerDict;
	vhtTracker *tracker;
	
	vhtTransform3D trackerXForm;
	vhtVector3d	position;
	vhtQuaternion  orientation;
	vhtVector3d	axis;
	
	
	Mat kep;
	int gap_value;
	bool gap;
	
	DataCollector() : emgSamples(8, 0)
    //: emgSamples()
	///OpenCV spec
    {
		///8 a myo-nak
		///3 ujjanként?
		///'6' ujj
		///1 üres hely két ujj között
		gap_value =-1;
		gap = true;
		int cols =31;
		if(gap) cols = 37;
		kep = Mat::zeros(cols, 100, CV_8U); // CV_16S --> short; CV_8S --> signed char; CV_8U --> unsigned char
		for (int idx=0; idx<kep.cols; idx++) {
			kep.col(idx) = 2*idx; ///ez mit csinál az index szerint növeli az értékét minden adott oszlopnak
		}
    }

	void NoGap(){
		gap = false;
	}
	
	///Glove connect
	void GetGlove(){
		// Get the default glove connection object
		gloveDict = vhtIOConn::getDefault( vhtIOConn::glove );

		// You could alternatively connect to a specific glove
		//gloveDict = new vhtIOConn( "cyberglove", "192.168.0.60", "12345", "com1", "38400" );

		// If that failed, then try to connect to the default touch
		if ( gloveDict == NULL )
		{
			gloveDict = vhtIOConn::getDefault( vhtIOConn::touch );
		}

		// Create the glove from our connection object
		glove = new vhtCyberGlove(gloveDict);
	}
	
	///Tracker specification
	void GetTracker(){
			// Get the default tracker connection object
			trackerDict = vhtIOConn::getDefault( vhtIOConn::tracker );
			// Create the tracker from our connection object
			tracker = new vhtTracker( trackerDict );
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
	
	void GloveAndTrackerUpdate(){
		glove->update();
		tracker->update();
	}
		
    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.
    // We define this function to print the current values that were updated by the on...() functions above.
    void print()
    {
		double tmp;
		unsigned int tmpint;
		double degree;
		for (int idx=0; idx<8; idx++) {
			std::cout << '\t' << emgSamples[idx];
		};
		cout <<'\t'<<std::endl;
		

		for (int i=0; i<kep.cols-1; i++) {
			kep.col(i+1).copyTo(kep.col(i)); /// mozgat 1-gyel arrébb
		}
		for (int i=0; i<8; i++) {
			kep.at<unsigned char>(i, kep.cols-1) = static_cast<int>(emgSamples[i]) + 128;
		}
		// Get update time delta
		//cout << "deltaTime: " << glove->getLastUpdateTime() - baseT << "\n";

		// For every finger
		int last_place = 7+gap;
		for( int finger = 0; finger < GHM::nbrFingers; finger++ )
		{
			cout<<"finger: "<< finger+1<<" :  ";
			// For every joint on this finger
			for( int joint = 0; joint < GHM::nbrJoints; joint++ )
			{
				// Print the joint angle
				tmp = glove->getData( (GHM::Fingers)finger, (GHM::Joints)joint ); ///double valószínűleg 0 és 1 között.
				tmpint = round(tmp*256);
				kep.at<unsigned char>(last_place+joint, kep.cols-1) = tmpint;
				last_place = last_place+joint;
				cout << tmp << " "; 
				
			}

			// Print the abduction value
			tmp = glove->getData( (GHM::Fingers)finger, GHM::abduct );
			tmpint = round(tmp*256);
			kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;
			last_place = last_place+1+gap;
			cout << tmp;
			cout << "\t";
		}

		// Print the palmArch, wristFlexion, and wristAbduction values (treated as a 6th finger)
		//cout << 5 << " ";
		cout<<"palm arch: "<<":  ";
		tmp = glove->getData( GHM::palm, GHM::palmArch ); ///double valószínűleg 0 és 1 között.
		tmpint = round(tmp*256);
		kep.at<unsigned char>(last_place+1+gap, kep.cols-1) = tmpint;
		last_place = last_place+1+gap;
		cout << tmp << '\t';
		//cout << glove->getData( GHM::palm, GHM::palmArch ) << " ";
		cout<<"wrist flextion: "<<":  ";
		tmp = glove->getData( GHM::palm, GHM::wristFlexion ); ///double valószínűleg 0 és 1 között.
		tmpint = round(tmp*256);
		kep.at<unsigned char>(last_place+1+gap, kep.cols-1) = tmpint;
		last_place = last_place+1+gap;
		cout << tmp << '\t';
		//cout << glove->getData( GHM::palm, GHM::wristFlexion ) << " ";
		cout<<"wrist abduction: "<<":  ";
		tmp = glove->getData( GHM::palm, GHM::wristFlexion ); ///double valószínűleg 0 és 1 között.
		tmpint = round(tmp*256);
		kep.at<unsigned char>(last_place+1+gap, kep.cols-1) = tmpint;
		last_place = last_place+1+gap;
		cout << tmp << '\t';
		//cout << glove->getData( GHM::palm, GHM::wristAbduction );
		cout << "\n";
		/*
		// Get tracker data as a vhtTransform3D in world frame
		tracker->getLogicalDevice(0)->getTransform( &trackerXForm );

		// print translation and orientaion
		trackerXForm.getTranslation( position );
		trackerXForm.getRotation( orientation );
		orientation.getAxis( axis );

		if ( tracker->getType() != VHT_TRACKER )
		{
			//cout << "Tracker: \n";
		}
		else
		{
			//cout << "No tracker found - values will be zero! \n";
		}

		cout << "Tracker: \n";
		cout << position.x << " " << position.y << " " << position.z << "\n";
		cout << axis.x << " " << axis.y << " " << axis.z << " " << orientation.getAngle() << "\n";
		*/
		cout << "\n";

    }
    // The values of this array is set by onEmgData() above.
    //std::array<int8_t, 8> emgSamples;
	void log(std::ofstream& fajl)
    {
		double tmp;
		unsigned int tmpint;
		for (int idx=0; idx<8; idx++) {
			fajl << emgSamples[idx]<<'\t';
		};
		//fajl <<'\t'<<std::endl;

		for (int i=0; i<kep.cols-1; i++) {
			kep.col(i+1).copyTo(kep.col(i)); /// mozgat 1-gyel arrébb
		}
		for (int i=0; i<8; i++) {
			kep.at<unsigned char>(i, kep.cols-1) = static_cast<int>(emgSamples[i]) + 128;
		}
		// Get update time delta
		//cout << "deltaTime: " << glove->getLastUpdateTime() - baseT << "\n";

		// For every finger
		int last_place = 7;
			if(gap){
		kep.at<unsigned char>(last_place+1, kep.cols-1) = gap_value;
		last_place = last_place+1;}

		for( int finger = 0; finger < GHM::nbrFingers; finger++ )
		{
			fajl<<"\t";
			// For every joint on this finger
			for( int joint = 0; joint < GHM::nbrJoints; joint++ )
			{
				// Print the joint angle
				tmp = glove->getData( (GHM::Fingers)finger, (GHM::Joints)joint ); ///double valószínűleg 0 és 1 között.
				fajl << round(radtodeg(tmp)) << '\t'; 
				tmpint = round(tmp*256);
				kep.at<unsigned char>(last_place+joint+1, kep.cols-1) = tmpint;
				//last_place = last_place+joint;	
			}
			last_place = last_place+GHM::nbrJoints;
			fajl << '\t';
			// Print the abduction value
			tmp = glove->getData( (GHM::Fingers)finger, GHM::abduct );
			fajl << round(radtodeg(tmp)) << '\t';
			tmpint = round(tmp*256);
			kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;
			
			last_place = last_place+1;
			if(gap){
			kep.at<unsigned char>(last_place+1, kep.cols-1) = gap_value;
			last_place = last_place+1;}
			
		}

		// Print the palmArch, wristFlexion, and wristAbduction values (treated as a 6th finger)
		//cout << 5 << " ";
		fajl<<"\t,";
		tmp = glove->getData( GHM::palm, GHM::palmArch ); ///double valószínűleg 0 és 1 között.
		fajl << round(radtodeg(tmp)) << '\t';

		tmpint = round(tmp*256);
		kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

		last_place = last_place+1;
		//cout << glove->getData( GHM::palm, GHM::palmArch ) << " ";
		//cout<<"wrist flextion: "<<":  ";
		tmp = glove->getData( GHM::palm, GHM::wristFlexion ); ///double valószínűleg 0 és 1 között.
		fajl << round(radtodeg(tmp)) << '\t';

		tmpint = round(tmp*256);
		kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

		last_place = last_place+1;

		//cout << glove->getData( GHM::palm, GHM::wristFlexion ) << " ";
		//cout<<"wrist abduction: "<<":  ";
		tmp = glove->getData( GHM::palm, GHM::wristFlexion ); ///double valószínűleg 0 és 1 között.
		fajl << round(radtodeg(tmp)) << '\n';

		tmpint = round(tmp*256);
		kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

		last_place = last_place+1;
    }
	
};
int main(int argc, char** argv)
{   
	
		/// Armband connect
		int sect = 0;
		bool first = true;
		try {

			DataCollector collector;
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
				collector.log(outfile);
				
				//Section 8
				if(first)sect++;

				if(GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
				{
					sect=100; //biggest
					break;
				}
				if(GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
				{
					outfile<<" bookmark : "<<bookmark<<"\n";
					bookmark++;
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
