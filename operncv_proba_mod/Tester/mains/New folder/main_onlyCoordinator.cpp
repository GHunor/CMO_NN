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
#include <windows.h>
//#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <ctime>

#include<conio.h>


//#include "Datalogger.hpp"
#include "Timer.hpp"
#include "Coordinator.hpp"
int main(){
    std::string tstr = "movements_list.txt";
    coordinator COOR(tstr.c_str());
    int second = 1000;//40;
    int amount = 100;
    int free_run = 120, wait = 5, movement_length = 5;

    double key_press = 0.5;

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
    int pressed_P =0, pressed_R = 0, pressed_X = 0;




    std::time_t result = std::time(NULL);



    while(!COOR.isDone()){
        iter++;
        movement = COOR.curr_statei();
        Message = COOR.message();
        /*
        if(pmovement-movement!=0) {if(!COOR.isWait){state_iter++;std::cout<<"STATE: "<<movement<<" "<<COOR.curr_state()
        <<"\nMESSAGE: "<<Message
        <<"  "<< state_iter<<"/"<<COOR.statelist.size()<<std::endl;}}
        pmovement = movement;*/
        int movement = COOR.curr_statei();
        if(movement!=pmovement && !COOR.isWait && !COOR.isPaused){system("cls");std::cout<<"STATE: "<<COOR.curr_state()<<"\nMESSAGE: "<<COOR.message(COOR.next_move())<<std::endl;}
        if(SubMessage != "")std::cout<<SubMessage<<COOR.statelist.size()<<std::endl;
        //clrscr();

        int pmovement = movement;
        COOR.DO(SubMessage);
        if(GetKeyState('P') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_P == 0)
        {
            pressed_P++;
            COOR.Pause();
            std::cout << "PAUSED";
        }
        if(pressed_P<key_press*second && pressed_P>0){pressed_P++;std::cout << "p";}
        if(pressed_P==key_press*second){pressed_P = 0;}
        //int pressed_R = 0;
        if(GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_R == 0)
        {
            pressed_R++;
            COOR.Repeat_last();
            std::cout << "Repeat";
        }
        if(pressed_R<key_press*second && pressed_R>0){pressed_R++;std::cout << "R";}
        if(pressed_R==key_press*second){pressed_R = 0;}

        if(GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && pressed_X == 0)
        {
            pressed_X++;
            //clrscr();
            system("cls");
            //std::cout << "\033[2J\033[1;1H";
            ///COOR.End();
            break;
        }
        if(pressed_X<key_press*second && pressed_X>0){pressed_X++;std::cout << "X";}
        if(pressed_X==key_press*second){pressed_X = 0;}

        //sleep(1);
    }
    std::cout<<iter<<std::endl;
    std::cout << std::asctime(std::localtime(&result))
              << result << " seconds since the Epoch\n";
    return 0;
}
