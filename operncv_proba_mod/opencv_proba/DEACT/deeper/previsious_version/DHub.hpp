//dummy hub
//needed so the hub can be used outside of a try
#include <windows.h>
#include <myo/myo.hpp>

class DHub{
myo::Hub hub;
bool hub_working;
public:

	/*
	DHub(){
		hub_working = 1;
		try{
			hub();
		}
		catch (const std::exception& e) {
        hub_working = 0;
		}
	};
	*/
	DHub(std::string name){
		hub_working = 1;
		try{
			myo::Hub hub(name);
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
				ret = hub.waitForMyo(msec);
			}
			catch (const std::exception& e) {
				hub_working = 0;
			}
		}
		return ret;
	};


	void set_streaming(){
		try{
			myo::Myo* myo = hub.waitForMyo(10000);
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
		hub.addListener(collector);
	};
	void run(int msec){
		if (hub_working){
			hub.run(msec);
			return;
		}
		Sleep(msec);
	};
}


class DHubP{
myo::Hub* hub;
bool hub_working;
public:


	DHubP(){};
	void Set(std::string name){
		hub_working = 1;
		try{
			hub* = new myo::Hub(name);
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
			//*/
			//hub.set_streaming();
			//Section 2
			sect++;

			hub->addListener(&collector);
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
}
