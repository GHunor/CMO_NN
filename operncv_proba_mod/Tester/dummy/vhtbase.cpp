//
// Created by ghuno on 2021-11-24.
//

#include "vhtbase.h"

vhtTrackerEmulator::vhtTrackerEmulator() {}

std::string vhtBaseException::what() {
    return NULL;
}

vhtTracker::vhtTracker() {}

vhtIOConn *vhtIOConn::getDefault(int g) {
    return NULL;
}

vhtIOConn::vhtIOConn(vhtIOConn *pConn) {

}

vhtCyberGlove::vhtCyberGlove(vhtIOConn *pConn) {

}

void vhtCyberGlove::update() {

}

void vhtTracker::update() {

}

double vhtCyberGlove::getData(GHM::Fingers fingers, GHM::Joints joints) {
    return 0;
}

double vhtCyberGlove::getLastUpdateTime() {
    return 0;
}

GHM::Fingers::Fingers(int i) {

}

vhtTracker::vhtTracker(vhtIOConn *pConn) {

}

GHM::Joints::Joints(int i) {

}
