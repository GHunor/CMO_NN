//
// Created by ghuno on 2021-11-24.
//

#include "myo.hpp"

myo::Hub::Hub(const char *string):AB(){};

void myo::Hub::run(int i) {
    //sleep(25)
    //
    // DevLis onUnpair(AR, uint64_t timestamp);
    //gen data
    DevLis.onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);
}

void myo::Hub::addListener(myo::DeviceListener *DL) {
    DevLic = *DL;
}

void myo::Myo::setStreamEmg(bool &STE) {
    streamEmgEnabled = STE;
}

myo::Myo *myo::Hub::waitForMyo(int t) {
    return NULL;
}

myo::DeviceListener::DeviceListener(onUnpair myo) : Myo(myo) {}

myo::Myo::Myo() {
    streamEmgEnabled = 0;
}
