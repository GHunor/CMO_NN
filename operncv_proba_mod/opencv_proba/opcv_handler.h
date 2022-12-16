#include <cmath>
#include <vector>

#include "opencv/cv.h"
#include "opencv/highgui.h"

#define _WIN32_WINNT 0x0400	



class OpCV_handler{
	Mat kep;
    int gap_value;
    bool gap;
	bool myo, vht, opt1, opt2, opt3;
public:
	//OpCV():gap_value(-1),gap(true), myp(true), vht(true), opt1(false), opt2(false), opt3(false){};
	OpCV(bool Gap = true, bool Myo = true, bool Vht = true, bool Opt1 = true, bool Opt2 = true, bool Opt3 = true):gap_value(-1),gap(Gap), myp(Myo), vht(Vht), opt1(Opt1), opt2(Opt2), opt3(Opt3){};
	Build(){
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
	Build(bool Gap = true, bool Myo = true, bool Vht = true, bool Opt1 = true, bool Opt2 = true, bool Opt3 = true){
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
			start =+ 20
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
		data = Datamaker(std::vector<unsigned char> data, std::vector<bool> devices);
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