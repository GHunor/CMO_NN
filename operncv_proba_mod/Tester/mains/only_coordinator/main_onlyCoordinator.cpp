//
// Created by ghuno on 2021-11-26.
//
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
#include <unistd.h>

//#include "Datalogger.hpp"
#include "Timer.hpp"
#include "Coordinator.hpp"
int main(){
    std::string tstr = "movements_list.txt";
    coordinator COOR(tstr.c_str());
    int second = 40;
    int amount = 100;
    int free_run = 120, wait = 5, movement_length = 5;

    COOR.rhythim_setter(second, free_run*second, wait*second, movement_length*second, amount);
    int temp = COOR.get_max_state_num()*(movement_length+wait);
    temp += 41;
    std::cout<<"Egy egyseg hossza masodpercben: "<<temp<<std::endl;
    std::cout<<"Egesz hossza (szunet nelkul): "<<temp*amount<<std::endl;
    std::cout<<"Ennyi egyseg utan szunet (kb 2 ora munka utan): "<<3600/temp<<std::endl;
    COOR.statelist_maker(3600/temp);
    std::cout<<"Ennyi hosszu szunettel: "<<COOR.overall_time()/40<<std::endl;
    std::cout<<"A struktura torik: "<<COOR.check_sequence()<<std::endl;
    std::cout<<"A struktura hossza: "<<COOR.statelist.size()<<std::endl;


    int movement = COOR.curr_statei();
    int pmovement = movement, iter = 0, state_iter = 0;
    std::string mess = COOR.message();
    std::string Message = "";
    std::string SubMessage = "";
    COOR.DO(SubMessage);

    while(!COOR.isDone()){


        iter++;
        movement = COOR.curr_statei();
        Message = COOR.message();
        if(pmovement-movement!=0) {if(!COOR.isWait){state_iter++;std::cout<<"STATE: "<<movement<<" "<<COOR.curr_state()
        <<"\nMESSAGE: "<<Message
        <<"  "<< state_iter<<"/"<<COOR.statelist.size()<<std::endl;}}
        pmovement = movement;
        COOR.DO(SubMessage);


        if(iter==5001)
            COOR.Pause();
        if(iter==5200)
            COOR.Pause();
    }
    std::cout<<iter<<std::endl;
    return 0;
}
