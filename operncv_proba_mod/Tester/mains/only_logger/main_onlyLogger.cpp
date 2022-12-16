//
// Created by ghuno on 2021-11-26.
//

#include <vector>
#include <iostream>
//#include <sstream>
//#include <stdexcept>
#include <string>
//#include <cmath>
//#include <ccomplex>
//#include <ostream>
//#include <fstream>
//#include <windows.h>
//#include <stdio.h>
#include <stdint.h>


#include "Datalogger.hpp"
//#include "Timer.hpp"
//#include "Coordinator.hpp"
int main(){
    Datalogger DL("ttt");

    int n = 20;

    float ST = 0;
    std::vector<int> VI(8,0.0);
    uint64_t mt = 0;
    std::vector<double> all_joint(20, 0.0);
    double gt = 0;
    std::string mess = "message";
    std::string mov = "movement";
    std::string key = "key";
    for(int i = 0; i<n; i++){
        DL.set_system_time(++ST);
        VI[i%8]++;
        DL.set_myo( VI) ;
        DL.set_myo_time( ++mt );
        all_joint[i%20]++;
        DL.set_glove( all_joint );
        DL.set_glove_time( ++gt );
        if (i%10 == 0) mov.append("0");
        DL.set_movement(mov);
        if (i%10 == 1) mess.append("0");
        DL.set_message(mess);
        if (i%10 == 2) key.append("0");
        DL.set_pressed_key(key);
        std::cout<<DL.check_readline()<<std::endl;
        DL.new_line();
    }
    DL.end();



    return 0;
}