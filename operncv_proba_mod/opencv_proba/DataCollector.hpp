//
// Created by ghuno on 2021-11-24.
//

#ifndef TESTER_DATACOLLECTOR_HPP
#define TESTER_DATACOLLECTOR_HPP

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


#include "Datalogger.hpp"
//#include "Timer.hpp"

#include "opencv/cv.h"
#include "opencv/highgui.h"

#define _WIN32_WINNT 0x0400			// avoid winsock problem
using std::cout;
using namespace cv;

#define PI (355/113)
/*
int iround(double x){
    int dec = int(x*10)%10;
    if (dec>5) {return int(ceil(x));}
    return int(floor(x));
}
*/
int refact(double data, double min = 0, double max = 1, int size = 256){
	double length = max - min;
	length = (data-min)/length;
	int ret = iround(double(length * double(size)));
	return ret;
}

class DataCollector : public myo::DeviceListener {
public:
    std::vector<int> emgSamples;
    uint64_t myosdkts;

    float glove_time;

    vhtIOConn *gloveDict;
    vhtCyberGlove *glove;
    vhtIOConn *trackerDict;
    vhtTracker *tracker;

    vhtTransform3D trackerXForm;
    vhtVector3d	position;
    vhtQuaternion  orientation;
    vhtVector3d	axis;


    Mat kep;
    int gap_value, cols;
    bool gap;

	bool myo, vht, opt1, opt2, opt3;
	
	/*
    DataCollector() : emgSamples(8, 0) delete 
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
        //kep = Mat::zeros(cols, 100, CV_8U ); // CV_16S --> short; CV_8S --> signed char; CV_8U --> unsigned char
        //for (int idx=0; idx<kep.cols; idx++) {
        //    kep.col(idx) = 2*idx; ///ez mit csinál az index szerint növeli az értékét minden adott oszlopnak
        //}
		myosdkts = 0;
		myo = true;
		vht = true;
        glove_time = 0;
    }
	*/
	DataCollector(bool Gap = true, bool Myo = true, bool Vht = true, bool Opt1 = true, bool Opt2 = true, bool Opt3 = true) : emgSamples(8, 0)
    //: emgSamples()
    ///OpenCV spec
    {
		myo = Myo;
		vht = Vht;
		opt1 = Opt1;
		opt2 = Opt2;
		opt3 = Opt3;

        gap_value =-1;
        gap = Gap;
		cols = 0;
		if(myo){
			cols=+8;
			if (gap)cols++;
		}
		if(vht){
			cols=+23;
			if (gap)cols=+2;
		}
		if(opt1){
			cols=+3;
			if (gap)cols++;
		}
		if(opt2){
			cols=+3;
			if (gap)cols++;
		}
		if(opt3){
			cols=+3;
			if (gap)cols++;
		}
        //kep = Mat::zeros(cols, 100, CV_8U ); // CV_16S --> short; CV_8S --> signed char; CV_8U --> unsigned char
        //for (int idx=0; idx<kep.cols; idx++) {
        //    kep.col(idx) = 2*idx; ///ez mit csinál az index szerint növeli az értékét minden adott oszlopnak
        //}
		myosdkts = 0;
		
        glove_time = 0;
    }

	bool Is_gap(){
		return gap;
	}


	void NoMyo(){
		myo = false;
	}
	
	void NoGlove(){
		vht = false;
	}

    void NoGap(){
        gap = false;
    }
	void NoOpt1(){
		opt1 = false;
	}
	void NoOpt2(){
		opt2 = false;
	}
	void NoOpt3(){
		opt3 = false;
	}
    ///myo onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
        //emgSamples.fill(0);
        for (int i=0; i<8; i++) {
            emgSamples[i] = 0;
        }
    }

    ///myo onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {
        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }
        myosdkts = timestamp;
        //std::cout << "#####\n";
    }

    ///vht Glove connect
    bool GetGlove(){
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
        if ( gloveDict != NULL )
        {
            glove = new vhtCyberGlove(gloveDict);
        }
        return gloveDict != NULL;
    }

    ///vht Tracker specification
    void GetTracker(){
        // Get the default tracker connection object
        trackerDict = vhtIOConn::getDefault( vhtIOConn::tracker );
        // Create the tracker from our connection object
        tracker = new vhtTracker( trackerDict );
    }

	///vht update
    void GloveAndTrackerUpdate(){
		if(vht){
			glove->update();
			tracker->update();
		}
    }

    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.
    // We define this function to print the current values that were updated by the on...() functions above.
    
    // The values of this array is set by onEmgData() above.
    //std::array<int8_t, 8> emgSamples;
    uint64_t Get_Myo_time(){
        if(myo) return myosdkts;
        return 0;
    };
    std::vector<int> Get_Myo_vec(){
        return emgSamples;
    };
    std::vector<double> Get_glove_data_all(){
        std::vector<double> ret;
        double tmp;
        if(!vht) return ret;
        for( int finger = 0; finger < GHM::nbrFingers; finger++ )
        {
            for( int joint = 0; joint < GHM::nbrJoints; joint++ )///the three flexio
            {
                tmp = glove->getData( (GHM::Fingers)finger, (GHM::Joints)joint );
                ret.push_back(tmp);
            }
            tmp = glove->getData( (GHM::Fingers)finger, GHM::abduct );
            ret.push_back(tmp);
            /// abduction printed
        }
        ///wrist & palm
        tmp = glove->getData( GHM::palm, GHM::palmArch );
        ret.push_back(tmp);
        ///palm arch
        tmp = glove->getData( GHM::palm, GHM::wristFlexion );
        ret.push_back(tmp);
        ///wrist flexio
        tmp = glove->getData( GHM::palm, GHM::wristAbduction);
        ret.push_back(tmp);
        ///wrist abduction
        return ret;
    };
    std::vector<double> Get_glove_data_onlyfingers(){
        std::vector<double> ret;
        double tmp;
        if(!vht) return ret;
        for( int finger = 0; finger < GHM::nbrFingers; finger++ )
        {
            for( int joint = 0; joint < GHM::nbrJoints; joint++ )///the three flexio
            {
                tmp = glove->getData( (GHM::Fingers)finger, (GHM::Joints)joint );
                ret.push_back(tmp);
            }
            tmp = glove->getData( (GHM::Fingers)finger, GHM::abduct );
            ret.push_back(tmp);
            /// abduction printed
        }
        return ret;
    };
    float Get_glove_time(){
        if (vht) return glove->getLastUpdateTime();
        return 0;
    };
    float Get_glove_time_add(){
        if (vht) glove_time=+glove->getLastUpdateTime();
        return glove_time;
    };
	void OpCVb(std::vector<unsigned char> data){
		for (int i=0; i<data.size(); i++) {
            //kep.at<unsigned char>(i, kep.cols-1) = data[i];
        }
	}
	std::vector<unsigned char> OCV_datamaker(std::vector<unsigned char> myo, std::vector<unsigned char> glove){
		std::vector<unsigned char> ret;
		for (int i=0; i<myo.size(); i++) {
            ret.push_back(myo[i]);
        }
		if(gap) ret.push_back(0);
		for (int i=0; i<glove.size(); i++) {
            ret.push_back(glove[i]);
        }
		return ret;
	};
	std::vector<unsigned char> OCV_datamaker(std::vector<int> myo, std::vector<double> glove){
		std::vector<unsigned char> ret;
		for (int i=0; i<myo.size(); i++) {
            ret.push_back(static_cast<int>(myo[i]) + 128);
        }
		if(gap) ret.push_back(0);
		for (int i=0; i<glove.size(); i++) {
            ret.push_back(refact(glove[i], - PI, PI ));
        }
		return ret;
	};
	std::vector<unsigned char> OCV_datamaker(std::vector<unsigned char> data, std::vector<bool> devices){
		std::vector<unsigned char> ret;
		int start = 0;
		bool dont = false;
		if (devices.empty() || data.size()<3 ) return ret;
		if(devices[0]){
			if(data.size()<8) dont = true;
			for (int i=start; i<data.size() && i<start+8; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 8;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>1 && devices[1] && !dont){
			if(data.size()-start<23) dont = true;
			for (int i=start; i<data.size() && i<start+20; i++) {
				ret.push_back(data[i-start-1]);
			}
			if(gap) ret.push_back(gap_value);
			start =+ 20;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>2 && devices[2] && !dont){
			if(data.size()-start<3) dont = true;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>3 && devices[3] && !dont){
			if(data.size()-start<3) dont = true;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>4 && devices[4] && !dont){
			if(data.size()-start<3) dont = true;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		return ret;
	};
	void Load(std::vector<unsigned char> data, std::vector<bool> devices){
		data = OCV_datamaker(data, devices);
		for (int i=0; i<data.size(); i++) {
            kep.at<unsigned char>(i, kep.cols-1) = data[i];
        }
	}
	static std::vector<unsigned char> Convert_myo(std::vector<int> myo){
		std::vector<unsigned char> ret;
		for (int i=0; i<myo.size(); i++) {
            ret.push_back(static_cast<int>(myo[i]) + 128);
        }
		return ret;
	};
	static std::vector<unsigned char> Convert_vht(std::vector<double> glove){
		std::vector<unsigned char> ret;
		for (int i=0; i<glove.size(); i++) {
            ret.push_back(refact(glove[i], - PI, PI ));
        }
		return ret;
	};
	static std::vector<unsigned char> Convert_opt(std::vector<int> opt){
		std::vector<unsigned char> ret;
		for (int i=0; i<opt.size(); i++) {
            ret.push_back(refact(opt[i], -32768, 32767));
        }
		return ret;
	};
/*
    void log(std::ofstream& fajl, Datalogger& Log, std::vector<double> joints, float& glove_time)
    {
        double tmp = 0;
        unsigned int tmpint = 0;
        float baseT = glove_time;
        //baseT = glove->getLastUpdateTime();

        ///MYO DATA
        //for (int idx=0; idx<8; idx++) {
        //    fajl << emgSamples[idx]<<'\t';
        //};
		if(emgSamples.empty()) std::cout<<"Why is the emgSamples empty?"<<std::endl;
        //Log.set_myo(emgSamples);
		Log.push(emgSamples);
        //Log.set_myo_time(myosdkts);
		Log.push(myosdkts);
			//fajl <<'\t'<<std::endl;

        //for (int i=0; i<kep.cols-1; i++) {
        //    kep.col(i+1).copyTo(kep.col(i)); /// mozgat 1-gyel arrébb
        //}
        for (int i=0; i<8; i++) {
            //kep.at<unsigned char>(i, kep.cols-1) = static_cast<int>(emgSamples[i]) + 128;
        }
        // Get update time delta
        //cout << "deltaTime: " << glove->getLastUpdateTime() - baseT << "\n";

        // For every finger
        int last_place = 7;
        if(gap){
            //kep.at<unsigned char>(last_place+1, kep.cols-1) = gap_value;
            last_place = last_place+1;}

        for( int finger = 0; finger < GHM::nbrFingers; finger++ )
        {
            //fajl<<"\t";
            // For every joint on this finger
            for( int joint = 0; joint < GHM::nbrJoints; joint++ )
            {
                // Print the joint angle

                /// adat gyujtese
                if (vht) tmp = glove->getData( (GHM::Fingers)finger, (GHM::Joints)joint ); ///double valószínűleg 0 és 1 között.

					///fajl bekuldes
					//fajl << iround(radtodeg(tmp)) << '\t';
                //joints[finger*4 + joint] = tmp;
				if (vht) Log.push(tmp);
					///fajl bekuldes

                tmpint = iround(tmp*256);
                //kep.at<unsigned char>(last_place+joint+1, kep.cols-1) = tmpint;
                //last_place = last_place+joint;
            }
            if (vht) last_place = last_place+GHM::nbrJoints;

            //fajl << '\t';

            // Print the abduction value
            if (vht) tmp = glove->getData( (GHM::Fingers)finger, GHM::abduct );
            //fajl << iround(radtodeg(tmp)) << '\t';
            //joints[finger*4 + 3] = tmp;
			if (vht) Log.push(tmp);
            /// abduction printed

            tmpint = iround(tmp*256);
            //kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

            last_place = last_place+1;
            if(gap){
                //kep.at<unsigned char>(last_place+1, kep.cols-1) = gap_value;
                last_place = last_place+1;}

        }

        // Print the palmArch, wristFlexion, and wristAbduction values (treated as a 6th finger)
			//cout << 5 << " ";
			//fajl<<"\t,";
        if (vht) tmp = glove->getData( GHM::palm, GHM::palmArch ); ///double valószínűleg 0 és 1 között.
			//fajl << iround(radtodeg(tmp)) << '\t';
        //joints[20] = tmp;
		if (vht) Log.push(tmp);
        tmpint = iround(tmp*256);
        //kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

        last_place = last_place+1;
			//cout << glove->getData( GHM::palm, GHM::palmArch ) << " ";
			//cout<<"wrist flextion: "<<":  ";
        if (vht) tmp = glove->getData( GHM::palm, GHM::wristFlexion ); ///double valószínűleg 0 és 1 között.
			//fajl << iround(radtodeg(tmp)) << '\t';
        //joints[21] = tmp;
		if (vht) Log.push(tmp);
        tmpint = iround(tmp*256);
        //kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

        last_place = last_place+1;

        //cout << glove->getData( GHM::palm, GHM::wristFlexion ) << " ";
        //cout<<"wrist abduction: "<<":  ";
        if (vht) tmp = glove->getData( GHM::palm, GHM::wristFlexion ); ///double valószínűleg 0 és 1 között.
        //fajl << iround(radtodeg(tmp)) << '\n';
        //joints[22] = tmp;
		if (vht) Log.push(tmp);
        tmpint = iround(tmp*256);
        //kep.at<unsigned char>(last_place+1, kep.cols-1) = tmpint;

        last_place = last_place+1;

        if (vht) glove_time = glove->getLastUpdateTime();
		if(joints.empty()) std::cout<<"Why is the glove data empty?"<<std::endl;
        //Log.set_glove(joints);
        //Log.set_glove_time(glove_time-baseT);
		if (vht) Log.push(glove_time-baseT);
    }

	*/
};

class OpCV_handler{
	Mat kep;
    int gap_value;
    bool gap;
	bool myo, vht, opt1, opt2, opt3;
public:
	//OpCV():gap_value(-1),gap(true), myp(true), vht(true), opt1(false), opt2(false), opt3(false){};
	OpCV_handler(bool Gap = true, bool Myo = true, bool Vht = true, bool Opt1 = true, bool Opt2 = true, bool Opt3 = true):gap_value(-1),gap(Gap), myo(Myo), vht(Vht), opt1(Opt1), opt2(Opt2), opt3(Opt3){};
	void Build(){
		gap_value =-1;
        gap = true;
        int cols =31;
        if(gap) cols = 37;
        kep = Mat::zeros(cols, 100, CV_8U ); // CV_16S --> short; CV_8S --> signed char; CV_8U --> unsigned char
        for (int idx=0; idx<kep.cols; idx++) {
            kep.col(idx) = 2*idx; ///ez mit csinál az index szerint növeli az értékét minden adott oszlopnak
        }
		myo = true;
		vht = true;
		opt1 = false;
		opt2 = false;
		opt3 = false;
	}
	void Build(bool Gap = true, bool Myo = true, bool Vht = true, bool Opt1 = true, bool Opt2 = true, bool Opt3 = true){
		myo = Myo;
		vht = Vht;
		opt1 = Opt1;
		opt2 = Opt2;
		opt3 = Opt3;

		gap_value =-1;
		gap = Gap;
		int cols = 0;
		if(myo){
			cols=+8;
			if (gap)cols++;
		}
		if(vht){
			cols=+23;
			if (gap)cols=+2;
		}
		if(opt1){
			cols=+3;
			if (gap)cols++;
		}
		if(opt2){
			cols=+3;
			if (gap)cols++;
		}
		if(opt3){
			cols=+3;
			if (gap)cols++;
		}
		kep = Mat::zeros(cols, 100, CV_8U ); // CV_16S --> short; CV_8S --> signed char; CV_8U --> unsigned char
		for (int idx=0; idx<kep.cols; idx++) {
			kep.col(idx) = 2*idx; ///ez mit csinál az index szerint növeli az értékét minden adott oszlopnak
		}
	}
	bool Is_gap(){
		return gap;
	}
	void Load(std::vector<unsigned char> data){
		for (int i=0; i<data.size(); i++) {
            kep.at<unsigned char>(i, kep.cols-1) = data[i];
        }
	}
	std::vector<unsigned char> Datamaker(std::vector<unsigned char> myo, std::vector<unsigned char> glove){
		std::vector<unsigned char> ret;
		for (int i=0; i<myo.size(); i++) {
            ret.push_back(myo[i]);
        }
		if(gap) ret.push_back(gap_value);
		for (int i=0; i<glove.size(); i++) {
            ret.push_back(glove[i]);
        }
		return ret;
	};
	std::vector<unsigned char> Datamaker(std::vector<int> myo, std::vector<double> glove){
		std::vector<unsigned char> ret;
		for (int i=0; i<myo.size(); i++) {
            ret.push_back(static_cast<int>(myo[i]) + 128);
        }
		if(gap) ret.push_back(gap_value);
		for (int i=0; i<glove.size(); i++) {
            ret.push_back(refact(glove[i], - PI, PI ));
        }
		return ret;
	};
	std::vector<unsigned char> Datamaker(std::vector<unsigned char> data, std::vector<bool> devices){
		std::vector<unsigned char> ret;
		int start = 0;
		bool dont = false;
		if (devices.empty() || data.size()<3 ) return ret;
		if(devices[0]){
			if(data.size()<8) dont = true;
			for (int i=start; i<data.size() && i<start+8; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 8;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>1 && devices[1] && !dont){
			if(data.size()-start<23) dont = true;
			for (int i=start; i<data.size() && i<start+20; i++) {
				ret.push_back(data[i-start-1]);
			}
			if(gap) ret.push_back(gap_value);
			start =+ 20;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>2 && devices[2] && !dont){
			if(data.size()-start<3) dont = true;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>3 && devices[3] && !dont){
			if(data.size()-start<3) dont = true;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		if(devices.size()>4 && devices[4] && !dont){
			if(data.size()-start<3) dont = true;
			for (int i=start; i<data.size() && i<start+3; i++) {
				ret.push_back(data[i-start-1]);
			}
			start =+ 3;
			if(gap) ret.push_back(gap_value);
		}
		return ret;
	};
	void Load(std::vector<unsigned char> data, std::vector<bool> devices){
		data = Datamaker(data,devices);
		for (int i=0; i<data.size(); i++) {
            kep.at<unsigned char>(i, kep.cols-1) = data[i];
        }
	}
	void Step(){
		for (int i=0; i<kep.cols-1; i++) {
            kep.col(i+1).copyTo(kep.col(i)); /// mozgat 1-gyel arrébb
        }
	};
	void NoMyo(){
		myo = false;
	}
	void NoGlove(){
		vht = false;
	}

    void NoGap(){
        gap = false;
    }
	void NoOpt1(){
		opt1 = false;
	}
	void NoOpt2(){
		opt2 = false;
	}
	void NoOpt3(){
		opt3 = false;
	}
}

#endif //TESTER_DATACOLLECTOR_HPP
