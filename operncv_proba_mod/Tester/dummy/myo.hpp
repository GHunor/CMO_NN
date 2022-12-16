//
// Created by ghuno on 2021-11-24.
//

#ifndef TESTER_MYO_H
#define TESTER_MYO_H

#include <stdint.h>

namespace myo {

    class Myo{
    public:
        static bool streamEmgEnabled;
        Myo();

        void setStreamEmg(bool& STE);
    };
    class DeviceListener{
    public:
        DeviceListener();
        // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
        virtual void onUnpair(myo::Myo* myo, uint64_t timestamp);
        // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
        virtual void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);
    };
    class Hub{
        DeviceListener DevLic;
        Myo AB;
    public:
        void addListener(myo::DeviceListener *DL);

        Hub(const char string[28]);

        myo::Myo* waitForMyo(int t);

        void run(int i);
    };

};


#endif //TESTER_MYO_H
