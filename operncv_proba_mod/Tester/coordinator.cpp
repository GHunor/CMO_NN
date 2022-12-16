//
// Created by ghuno on 2022-04-29.
//

#include <fstream>
#include <cmath>
#include "coordinator.hpp"

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
    int FBTwB = round(For_Break_time/block);
    int FFBTwB = round((For_Break_time-Init_time)/block);

    all_time = moves*(Prep_time + Move_time)*Repeat_amount + Repeat_amount*Amount_spec_inblock*Specmove_time+Init_time + round((Repeat_amount-FFBTwB)/FBTwB)+1;
    all_moves = Repeat_amount*(moves+Amount_spec_inblock);

    msm.MStimes[0] = -1;
    msm.MStimes[1] = Init_time;
    msm.MStimes[2] = Prep_time;
    msm.MStimes[3] = 0;
    msm.MStimes[4] = Break_time;

    float quat = 1000/time_constant;
    Init_time = round(Init_time*quat);
    Prep_time = round(Prep_time*quat);
    Move_time = round(Move_time*quat);
    Specmove_time = round(Specmove_time*quat);
    Break_time = round(Break_time*quat);
    float FBT = For_Break_time*quat;
    block = round(block*quat);



    srand((unsigned) time(0));
    int amount;
    int indexes[moves], indexesTEMPL[moves];
    int tmp1, tmp2;
    for IRANGE(moves) {
        indexes[i] = i+1;
        indexesTEMPL[i] = i+1;
    }
    int Spec_amount1 = Repeat_amount*Amount_spec_inblock/special;
    int Spec_amount2 = (Repeat_amount*Amount_spec_inblock)%special;
    int Spec_moves_base[Repeat_amount*Amount_spec_inblock];
    for IRANGE(Spec_amount1){
        for (int j=0;j<special;j++){
            Spec_moves_base[i*special +j] = -(j+1);
        }
    }
    int tmp_ar[special];
    for IRANGE(special){
        tmp_ar[i]=-i-1;
    }
    mix_it_up(tmp_ar, special);
    for IRANGE(Spec_amount2){
        Spec_moves_base[Spec_amount1*special+i] = tmp_ar[i];
    }
    mix_it_up(Spec_moves_base, Repeat_amount*Amount_spec_inblock);
    int Spec_mov_counter = 0;

    for IRANGE(Repeat_amount) {
        amount = moves;//+Amount_spec_inblock;
        copy_array(indexes, indexesTEMPL, moves);
        mix_it_up(indexes, moves);
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
}



///not sure
void coordinator::_step_move(){
    if (*next == 0) {msm.Break_(); _act_on_msm();} else{move_place++;}
    current++;
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
            Message = Other_message[1] + "\n" + Get_move(*next); //timer set //message //move
            Title = Get_move(*next);
            ;
            break;
        case Main_states::Move:
            counter = Get_time_move(*current);
            Message = Get_move(*current) + "\n" + Get_message(*current);//timer set //move //message
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
    move_place/all_moves*100;
}
float coordinator::Get_precentage_time() {
    global_counter/all_time*100;
}
int coordinator::Get_time_MS(Main_states::MState I) {
    if(I==2){ return Get_time_move(*current);}
    return msm.MStimes[I + 1];
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
            if (msm.MS != Main_states::Move) return true;
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
    return Special_moves[-ID];
}

bool coordinator::Is_end() {
    return Move_list.end()==current;
}








