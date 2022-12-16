//
// Created by ghuno on 2021-11-24.
//

#ifndef TESTER_VHTBASE_H
#define TESTER_VHTBASE_H

#include <exception>
class GHM{
public:
    static int nbrFingers;
    static int nbrJoints;
    class Fingers{

    public:
        Fingers(int i);
    };
    class Joints{

    public:
        Joints(int i);
    };

    static GHM::Fingers palm;
    static GHM::Joints palmArch;
    static GHM::Joints wristFlexion;
    static GHM::Joints abduct;
};
class vhtIOConn{
public:
    vhtIOConn(vhtIOConn *pConn);

    static vhtIOConn* getDefault(int g);

    static  int glove;
    static  int touch;
    static  int tracker;
};
class vhtCyberGlove{
    ///data
public:
    vhtCyberGlove(vhtIOConn *pConn);

    void update();  ///modosit

    double getData(GHM::Fingers fingers, GHM::Joints joints);
    double getData(int fingers, int joints);

    double getLastUpdateTime();
};
class vhtTracker{
public:
    vhtTracker();

    vhtTracker(vhtIOConn *pConn);

    void update();
};
class vhtTrackerEmulator: public vhtTracker{
public:
    vhtTrackerEmulator();

};

class vhtTransform3D{

};
class vhtVector3d{

};
class vhtQuaternion{

};

class vhtBaseException: public std::exception{
    std::string what();
};


#endif //TESTER_VHTBASE_H
