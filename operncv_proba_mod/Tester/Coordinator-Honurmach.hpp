//
// Created by ghuno on 2022-04-29.
//

#ifndef TESTER_COORDINATOR_HPP
#define TESTER_STATE_MACHINE_HPP

#include <list>
#include "named_vector.hpp"
#include "prompt_handler.hpp"
#include "keypress_handler.hpp"
#include "useful_macros.h"

void mix_it_up(int row[], int size){
    int amount = size, tmp1, tmp2;
    for IRANGE(size){
        tmp1 = rand() % amount;
        tmp2 = row[tmp1];
        row[tmp1] = row[amount-1];
        row[amount-1] = tmp2;
        amount--;
    }
}

void copy_array(int* row1, int* row2, int size){
    for IRANGE(size){
        row1[i]=row2[i];
    }
}

struct Main_states{
    enum MState{ Pause = -1, Init = 0, PrepForNext = 1, Move = 2, Break = 3 }; //4
    int MStimes[5];
    MState MS;
    void Add_times(int* Times){
        for IRANGE(4){
            MStimes[i] = Times[i];
        }
    }
    Main_states(){
        MS = Init;
    }
    Main_states(int* Times){
        MS = Init;
        for IRANGE(4){
            MStimes[i] = Times[i];
        }
    }
    void Next_() {
        switch(MS){
                    case Init: MS = PrepForNext; break;
                    case PrepForNext: MS = Move; break;
                    case Move: MS = PrepForNext; break;
                    case Break: MS = PrepForNext; break;
                    case Pause: MS = PrepForNext; break;
            }
    }
    void Break_(){
        MS = Break;
    }
    void Pause_(){
        MS = Pause;
    }
    void SReset_(){
        MS = PrepForNext;
    }
    int TimeReq(){
        return MStimes[MS+1];
    }


};

class coordinator {
    Main_states msm;

    std::vector<std::string> Moves;
    std::vector<std::string> Moves_message;
    std::vector<std::string> Special_moves;
    std::vector<std::string> Special_moves_message;
    std::vector<std::string> Other_message;
    int Repeat_amount, Amount_spec_inblock, Move_time, Specmove_time, Init_time, Prep_time, For_Break_time, Break_time;

    std::list<int> Move_list;  //1-n Normal moves // m -> -1 Special move // o == break
    std::list<int>::iterator prev, next, current;
    int break_ID;

    int counter, global_counter;
    std::string Message, Title;
    int move_place, all_moves, all_time;

    float time_constant;

    void _read_moves(const char* name);
    void _read_special_moves(const char* name);
    //void _read_other_messages(const char* name);
    void _read_times_n_other_messages(const char* name);
    //void _read_exact(const char* name);
    void _builder();
    void _step_move();
    void _act_on_msm();
public:
    coordinator(){
        _read_moves("movements_list.txt");
        _read_special_moves("spec_movements_list.txt");
        _read_times_n_other_messages("other_attribute_n_messages.txt");
        _builder();
    }
    coordinator(const std::string direct){
        _read_moves((direct + "/movements_list.txt").c_str());
        _read_special_moves((direct + "/spec_movements_list.txt").c_str());
        _read_times_n_other_messages((direct + "/other_attribute_n_messages.txt").c_str());
        _builder();
    }
    coordinator(const char* name1, const char* name2, const char* name3){
        _read_moves(name1);
        _read_special_moves(name2);
        _read_times_n_other_messages(name3);
        _builder();
    }
    std::string Next_move();

    void Step();
    ///sends info
    std::string Get_move(int index);
    std::string Get_message(int index);
    std::string Get_MS(int st);
    int Get_time_move(int index);
    int Get_time_MS(Main_states::MState I);
    int Get_counter();
    float Get_precentage_moves();
    float Get_precentage_time();
    int Get_numberof_nmoves();
    int Get_numberof_smoves();
    int Get_numberof_moves();
    std::string Current_move();
    std::string OutTitle();
    std::string OutMessage();
    std::vector<std::string> Send_moves();
    std::vector<std::string> Send_specmoves();
    std::string Move_name(int ID);
    int Num_of_MS();
    int Num_of_move();
    bool Is_end();

    ///recieve
    bool Repeat();
    bool Pause();
    //main cycle
    bool Update();



};


#endif //TESTER_STATE_MACHINE_HPP
