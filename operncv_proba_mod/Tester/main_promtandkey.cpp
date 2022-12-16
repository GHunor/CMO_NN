//
// Created by ghuno on 2022-04-24.
//

#include <algorithm>

#include "prompt_handler.hpp"
#include "useful_macros.h"
#include "keypress_handler.hpp"
//#include "coordinator.hpp"
#include "coordinator.cpp"
#include "Datalogger.hpp"

void Seed(){
    srand((unsigned) time(0));
};
int create_random(){
    return rand();
};
std::vector<int> create_random(int size){
    std::vector<int> ret(size);
    for IRANGE(size){
        ret[i] = rand();
    }
    return ret;
};
template<class T>
std::vector<double> operator/(std::vector<T> A, T qw){
    std::vector<double> ret(A.size());
    for IRANGE(A.size()){
        ret[i] = A[i]/qw;
    }
}

template<class T>
std::vector<double> devide(std::vector<T> A, T qw){
    std::vector<double> ret(A.size());
    for IRANGE(A.size()){
        ret[i] = A[i]/qw;
    }
    return ret;
}

int main(){
    promthandler ph;
    keypress_handler kh;
    DataloggerS lg;
    kh.Add_key('X', 20);
    kh.Add_key('R', 20);
    kh.Add_key('P', 20);
    kh.Create_key_bools();

    std::string title, directory;
    int opt1, opt2, opt3;

    ph << "Directory name please: \n";
    directory = "test"; //ph.askfor_string();
    ph << "Name for the measurement? \n";
    title = "test1"; //ph.askfor_string();
    ph << "Which COM is optoforce 1? \n";
    //opt1 = ph.askfor_int();
    ph << "Which COM is optoforce 2? \n";
    //opt2 = ph.askfor_int();
    ph << "Which COM is optoforce 3? \n";
    //opt3 = ph.askfor_int();

    coordinator co(directory);
    lg.Give_place(directory);
    lg.Give_title(title);
    std::string file_title;
    file_title = co.OutTitle();
    std::replace( file_title.begin(), file_title.end(), ' ', '_');
    lg.open(file_title);
    Timer tm;

    while(true)
    {
        Sleep(25);
        if (co.Update()){
            if (co.Is_end()) {lg.close();break;}
            file_title = co.OutTitle();
            std::replace( file_title.begin(), file_title.end(), ' ', '_');
            lg.reset_file(file_title);
            ph<<co.Current_move();
            ph.new_line();
            ph<<co.OutMessage();
            ph.new_line();
            ph<<co.Get_precentage_moves();
            ph.solidify();
        }
        std::cout<<"  "<<co.Get_counter()<<"  "<<co.Num_of_MS()<<"  "<<co.Num_of_move()<<std::endl;
        ///Main_State
        lg.push_state(co.Num_of_MS());
        ///Move
        lg.push_state(co.Num_of_move());
        ///Computer timer
        lg.push(tm.ms());
        ///Myo timer
        lg.push(create_random());
        ///Myo Data
        lg.push(create_random(8));
        ///glove timer
        lg.push(create_random()/3);
        ///glove data
        lg.push(
                devide(
                        create_random(23),3));
        ///opt1 time
        lg.push(create_random());
        ///opt1 data
        lg.push(create_random(3));
        ///opt2 time
        lg.push(create_random());
        ///opt2 data
        lg.push(create_random(3));
        ///opt3 time
        lg.push(create_random());
        ///opt3 data
        lg.push(create_random(3));
        lg.push_line();

        ///key check
        kh.Do();
        if (kh.key_bools2[0]) {ph<< "X pressed "; lg.close(); break;}  ///will end
        if (kh.key_bools2[1]) {
            ph<< "R pressed ";
            if (co.Repeat()) {
                file_title = co.OutTitle();
                std::replace( file_title.begin(), file_title.end(), ' ', '_');
                lg.reset_file_rep(file_title);
            }
        } ///resets coor and log
        if (kh.key_bools2[2]) {
            ph<< "P pressed ";
            if(co.Pause()){
                lg.reset_file("pause");
            }else{
                file_title = co.OutTitle();
                std::replace( file_title.begin(), file_title.end(), ' ', '_');
                lg.reset_file("pause");
            }
        };
        //co.Num_of_MS() == Main_states::Pause)}  ///pauses

        ///display messages
        ///from coord
        /*
        ph<<co.Current_move();
        ph.new_line();
        ph<<co.OutMessage();
        ph.new_line();
        ph<<co.Get_precentage_moves();
        */

        //coor update
        //collect update
        //display;
        //log
        //key


        /*
        if(GetKeyState('X') & 0x8000//Check if high-order bit is set (1 << 15)
                && pressed_X < 1)
        {
            pressed_X++;
            //ph.total_wipe();
            ph<< "X pressed" << " " <<pressed_X;
            ph.new_line();
            //ph.solidify();
            //PressedKey = "X";
            //break;
        }
        if(pressed_X<20 && pressed_X>0){
            pressed_X++;
            //ph.clean();
            ph<<"X  "<<pressed_X;
            ph.new_line();

        }
        if(pressed_X==20){
            pressed_X = 0;
            //PressedKey = "";
            //ph.clean();
        }

        if(GetKeyState('R') & 0x8000 //Check if high-order bit is set (1 << 15)
                && pressed_R < 1)
        {
            pressed_R++;
            //ph.total_wipe();
            ph<< "R pressed" << " " <<pressed_R;
            ph.new_line();
            //ph.solidify();
            //PressedKey = "R";xrp
        }
        if(pressed_R<20 && pressed_R>0){
            pressed_R++;
            //ph.clean();
            ph<<"R  "<<pressed_R;
            ph.new_line();
        }
        if(pressed_R==20){
            pressed_R = 0;
            //PressedKey = "";
            //ph.clean();
        }

        if(GetKeyState('P') & 0x8000 //Check if high-order bit is set (1 << 15)
                    && pressed_P <1)
        {
            pressed_P++;
            //ph.total_wipe();
            ph<< "P pressed" << " " <<pressed_P;
            ph.new_line();
            //ph.solidify();
           // PressedKey = "P";
        }
        if(pressed_P<20 && pressed_P>0){
            pressed_P++;
            //ph.clean();
            ph<<"P  "<<pressed_P;
            ph.new_line();
        }
    }
        if(pressed_P==20){
            pressed_P = 0;
            //PressedKey = "";
            //ph.clean();
            }
        */
    }
    return 0;
}