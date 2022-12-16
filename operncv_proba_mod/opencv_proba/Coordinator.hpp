//
// Created by ghuno on 2022-04-29.
//

#ifndef TESTER_COORDINATOR_HPP
#define TESTER_STATE_MACHINE_HPP
#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

//#include "named_vector.hpp"
//#include "prompt_handler.hpp"
//#include "keypress_handler.hpp"
#include "useful_macros.h"
#include "Timer.hpp"
#define PI (355/113)
int iceil(double x){return int(ceil(x));}

template <typename T>
void insertafter(std::list<T> List, int Index, T Value){
	int i=0;
	for (typename std::list<T>::iterator IT = List.begin(); IT!=List.end(); IT++){
		i++;
		if (i == Index) List.insert(IT, Value);
	}
}
int iround(double x){
    int dec = int(x*10)%10;
    if (dec>5) {return int(ceil(x));}
    return int(floor(x));
}

double radtodeg(double rad){
    return rad/PI*180;
}


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
void mix_it_up(std::vector<int>& row){
    unsigned int amount = row.size();
	int tmp1, tmp2;
    for IRANGE(row.size()){
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
void copy_array(std::vector<int>& row1, std::vector<int>& row2){
    for IRANGE(row1.size()){
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
	 static MState Next_(MState S) {
        switch(S){
                    case Init: return PrepForNext;
                    case PrepForNext: return Move;
                    case Move: return PrepForNext;
                    case Break: return PrepForNext;
                    case Pause: return PrepForNext;
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

    std::vector<int> Move_list;  //1-n Normal moves // m -> -1 Special move // o == break
    std::vector<int>::iterator prev, next, current;
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
	int ID_curr, Move_list_size;
    coordinator(){
        _read_moves("movements_list.txt");
        _read_special_moves("spec_movements_list.txt");
        _read_times_n_other_messages("other_attribute_n_messages.txt");
        _builder();
		_act_on_msm();
		ID_curr = 0;
		Move_list_size = Move_list.size();
    }
    coordinator(const std::string direct){
        _read_moves((direct + "/movements_list.txt").c_str());
        _read_special_moves((direct + "/spec_movements_list.txt").c_str());
        _read_times_n_other_messages((direct + "/other_attribute_n_messages.txt").c_str());
        _builder();
		_act_on_msm();
		ID_curr = 0;
		Move_list_size = Move_list.size();
    }
    coordinator(const char* name1, const char* name2, const char* name3){
        _read_moves(name1);
        _read_special_moves(name2);
        _read_times_n_other_messages(name3);
        _builder();
		_act_on_msm();
		ID_curr = 0;
		Move_list_size = Move_list.size();
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

//
// Created by ghuno on 2022-04-29.
//

void coordinator::_read_moves(const char* name){
    std::ifstream infile;
    infile.open(name); //, std::ofstream::out);
    if(infile.fail()) std::cout<<"\n" << name <<"\n movements.txt is missing\n";
    bool l = false;
    std::string temp, temp2;
    while(getline(infile, temp)){
        std::getline(infile, temp2);
        Moves.push_back(temp);
        Moves_message.push_back(temp2);
    }
    infile.close();
}
void coordinator::_read_special_moves(const char* name){
    std::ifstream infile;
    infile.open(name); //, std::ofstream::out);
    if(infile.fail()) std::cout<<"\nspec_movements.txt is missing\n";
    bool l = false;
    std::string temp, temp2;
    while(getline(infile, temp)){
        std::getline(infile, temp2);
        Special_moves.push_back(temp);
        Special_moves_message.push_back(temp2);
    }
    infile.close();
}
/*
void coordinator::_read_other_messages(const char* name){
    std::ifstream infile;
    infile.open(name); //, std::ofstream::out);
    std::string temp;
    while(getline(infile, temp)){
        other_message.push_back(temp);
    }
    infile.close();
}*/
void coordinator::_read_times_n_other_messages(const char* name){
    std::ifstream infile;
    infile.open(name); //, std::ofstream::out);
    if(infile.fail()) std::cout<<"\nother_attribute_n_messages.txt is missing\n";
    infile >> time_constant >> Repeat_amount >> Amount_spec_inblock >> For_Break_time >> Init_time >> Prep_time >> Move_time >> Specmove_time >> Break_time;
    std::string temp;
    getline(infile, temp);
    while(getline(infile, temp)){
        Other_message.push_back(temp);
    }
    infile.close();
}
void coordinator::_builder(){
    int moves = Moves.size();
    int special = Special_moves.size();
    // time_constant >> Repeat_amount >> Amount_spec_inblock >> Init_time >> Prep_time >> Move_time >> Specmove_time >> Break_time    For_Break_time ;

    int block = moves*(Prep_time+Move_time) + Amount_spec_inblock*(Specmove_time*special);
    int FBTwB = iround(For_Break_time/block);
    int FFBTwB = iround((For_Break_time-Init_time)/block);

    all_time = moves*(Prep_time + Move_time)*Repeat_amount + Repeat_amount*Amount_spec_inblock*Specmove_time+Init_time + iround((Repeat_amount-FFBTwB)/FBTwB)+1;
    all_moves = Repeat_amount*(moves+Amount_spec_inblock);

    msm.MStimes[0] = -1;
    msm.MStimes[1] = Init_time;
    msm.MStimes[2] = Prep_time;
    msm.MStimes[3] = 0;
    msm.MStimes[4] = Break_time;

    float quat = 1000/time_constant;
    Init_time = iround(Init_time*quat);
    Prep_time = iround(Prep_time*quat);
    Move_time = iround(Move_time*quat);
    Specmove_time = iround(Specmove_time*quat);
    Break_time = iround(Break_time*quat);
    float FBT = For_Break_time*quat;
    block = iround(block*quat);



    srand((unsigned) time(0));
    int amount;
	std::vector<int> indexes(moves); 
	std::vector<int> indexesTEMPL(moves);
    int tmp1, tmp2;
    for IRANGE(moves) {
        indexes[i] = i+1;
        indexesTEMPL[i] = i+1;
    }
    int Spec_amount1 = Repeat_amount*Amount_spec_inblock/special;
    int Spec_amount2 = (Repeat_amount*Amount_spec_inblock)%special;
    std::vector<int> Spec_moves_base(Repeat_amount*Amount_spec_inblock);
    for IRANGE(Spec_amount1){
        for (int j=0;j<special;j++){
            Spec_moves_base[i*special +j] = -(j+1);
        }
    }
    std::vector<int> tmp_ar(special);
    for IRANGE(special){
        tmp_ar[i]=-i-1;
    }
    mix_it_up(tmp_ar);
    for IRANGE(Spec_amount2){
        Spec_moves_base[Spec_amount1*special+i] = tmp_ar[i];
    }
    mix_it_up(Spec_moves_base);
    int Spec_mov_counter = 0;

    for IRANGE(Repeat_amount) {
        amount = moves;//+Amount_spec_inblock;
        copy_array(indexes, indexesTEMPL);
        mix_it_up(indexes);
        if (i + 1 == FFBTwB) Move_list.push_back(0);
        if ((i + 1 - FFBTwB) % FBTwB == 0) Move_list.push_back(0);
        for (int j=0;j<moves;j++){
                Move_list.push_back(indexes[j]);
        }
        for (int j=0; j<Amount_spec_inblock; j++){
                Move_list.push_back(Spec_moves_base[Spec_mov_counter + j]);
        }
        Spec_mov_counter += Amount_spec_inblock;
    }
    current=Move_list.begin();
    prev = Move_list.end();
    next = current;
    next++;
    counter = Init_time;
	global_counter=0;
	move_place=0;
	Message = Other_message[0];
}



///not sure
void coordinator::_step_move(){
    if (*next == 0) {msm.Break_(); _act_on_msm();} else{move_place++;}
    current++;
	ID_curr++;
    if(prev == Move_list.end()) {prev=Move_list.begin();}else{prev++;}
    next++;
}
void coordinator::_act_on_msm() {
    switch (msm.MS) {
        case Main_states::Init:
            counter = Init_time;
            Message = Other_message[0];
            Title = "init";
            break;
///maybe set a bit larger time after special move
        case Main_states::PrepForNext:
            counter = Prep_time;
            Message = Other_message[1]; //timer set //message //move
            Title = Get_move(*next);
            ;
            break;
        case Main_states::Move:
            counter = Get_time_move(*current);
            Message = Get_message(*current);//timer set //move //message
            Title = Get_move(*current);
            ;
            break;
        case Main_states::Break:
            counter = Get_time_move(*current);
            Message = Other_message[2];  //timer set //message
            Title = "break";
            ;
            break;
        case Main_states::Pause:
            counter = -1;
            Message = Other_message[3];//timer set //message
            Title = "title";
            ;
            break;
    };
}
std::string coordinator::Get_move(int index){
    if (index > int(Moves.size()) || -index > int(Special_moves.size())){return "error: boundary outstepped";}
    if (index > 0) return Moves[index-1];
    return Special_moves[-index];
}
std::string coordinator::Get_message(int index){
    if (index > int(Moves_message.size()) || -index > int(Special_moves_message.size())) {return "error: boundary outstepped";}
    if (index > 0) return Moves_message[index-1];
    return Special_moves_message[-index];
};
std::string coordinator::Get_MS(int st) {
    switch (st) {
        case Main_states::Init:
            return "Init";
        case Main_states::PrepForNext:
            return "PrepForNext";
        case Main_states::Move:
            return "Move";
        case Main_states::Break:
            return "Break";
        case Main_states::Pause:
            return "Pause";
    }
    return "";
}
int coordinator::Get_time_move(int index){
    if (index > int(Moves.size()) || -index > int(Special_moves.size())) return 1000;
    if (index > 0) return Move_time;
    if (index == 0) return Break_time;
    return Specmove_time;
}
std::string coordinator::Next_move(){
    return Get_move(*next);
};

void coordinator::Step(){
    msm.Next_();
};
//sends
std::string coordinator::Current_move(){
    return Get_move(*current);
};
std::string coordinator::OutTitle() {
    return Title;
}
std::string coordinator::OutMessage(){
    return Message;
};
int coordinator::Get_counter() {
    return counter;
}
float coordinator::Get_precentage_moves() {
    return move_place/all_moves*100;
}
float coordinator::Get_precentage_time() {
    return global_counter/all_time*100;
}
int coordinator::Get_time_MS(Main_states::MState I) {
    if(I==2){ return Get_time_move(*current);}
	int i = I+1;
	return msm.MStimes[I+1];
}
std::vector<std::string> coordinator::Send_moves(){
    return Moves;
}
std::vector<std::string> coordinator::Send_specmoves(){
    return Special_moves;
}

int coordinator::Num_of_MS(){
    return msm.MS;
}
int coordinator::Num_of_move(){
    return *current;
}
//recieve
bool coordinator::Repeat(){
    //true - steps one move back
    //if(msm.MS == Main_states::Break) { msm.SReset_(); _step_move(); global_counter = global_counter-Break_time+counter; return false;};
    if(msm.MS == Main_states::Break || msm.MS == Main_states::Pause || msm.MS == Main_states::Init) {return false;}
    if(msm.MS == Main_states::Move) { msm.SReset_();_act_on_msm();return true;};
    msm.SReset_();
    current--;
	ID_curr--;
    prev--;
    next--;
    move_place--;
    _act_on_msm();
    return true;
};
bool coordinator::Pause(){
    //true - starts the pause
    if (msm.MS == Main_states::Pause) {msm.Next_(); _act_on_msm();return false;}

    switch (msm.MS){
        case Main_states::Init: global_counter= global_counter+counter; break;
        case Main_states::PrepForNext: global_counter= global_counter-Prep_time+counter; break;
        case Main_states::Move: global_counter= global_counter- Get_time_move(*current)-Prep_time+counter; break;
        case Main_states::Break: global_counter= global_counter+counter; break;
        //case Main_states::Pause: msm.Next_(); break;
    }
    msm.Pause_();
    return true;
};
//main cycle
bool coordinator::Update(){
    if (msm.MS != Main_states::Pause){counter--;global_counter++;};
    if (counter==0){
        switch (msm.MS){
                case Main_states::Init: msm.Next_(); break;
                case Main_states::PrepForNext: msm.Next_(); break;
                case Main_states::Move: if(*next == 0) {msm.Break_();}else{msm.Next_();}; break;
                case Main_states::Break: msm.Next_(); break;
                case Main_states::Pause: msm.Next_(); break;
            }
            /// for now
            _act_on_msm(); //set timer
            if (msm.MS == Main_states::PrepForNext){_step_move();} //moves on list also sets
            return true;
        }
    return false;
}

int coordinator::Get_numberof_moves() {
    return (Moves.size()+Special_moves.size());
}

int coordinator::Get_numberof_nmoves() {
    return Moves.size();
}

int coordinator::Get_numberof_smoves() {
    return Special_moves.size();
}

std::string coordinator::Move_name(int ID) {
    if (ID>0) return Moves[ID-1];
	if (ID==0) return "Break_here";
    return Special_moves[-ID-1];
}

bool coordinator::Is_end() {
    return Move_list.end()==next;
}










#endif //TESTER_STATE_MACHINE_HPP
