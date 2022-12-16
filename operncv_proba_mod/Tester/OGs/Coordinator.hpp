//
// Created by ghuno
//
#ifndef COORDINATOR_H
#define COORDINATOR_H


#include <ctime>
#include <list>
#include <fstream>
#include <cstdlib>
#include <cmath>


    int iceil(double x){
        return int(ceil(x));
    }

	template <typename T>
	void insertafter(std::list<T> List, int Index, T Value){
		int i=0;
		for (typename std::list<T>::iterator IT = List.begin(); IT!=List.end(); IT++){
			i++;
			if (i == Index) List.insert(IT, Value);
		}
	}
struct coordinator{

    int max_state, amount, movement_length;
    int second;
    int free_run, wait;
    int own_iteration_num, current_goal;
	std::vector<std::string> movements;
    std::vector<std::string> messages;
	std::list<int> statelist;
    std::list<int>::iterator cur, curs;
    bool isPaused;
    bool isWait;

    std::vector<std::string> spec_movements;
    std::vector<std::string> spec_messages;

    void create_special_states(){

        spec_movements.push_back("FREE_MOVE");
        spec_messages.push_back("MOVE HOW YOU LIKE ,YOUR FINGER, WRIST, ARM. Every possition possible!");

        spec_movements.push_back("WAIT");
        spec_messages.push_back("DON'T MOVE your HAND and ARM !|| move EVERYTHING ELSE!");

        spec_movements.push_back("FREE_ACTIVE_FINGER");
        spec_messages.push_back("Move your arm HOW YOU LIKE ,but BE ACTIVE WITH YOUR FINGERS!");

        spec_movements.push_back("NO_WRIST_ACTIVE_FINGER");
        spec_messages.push_back("DON'T MOVE your WRIST but MOVE EVERYTHING ELSE!");

        spec_movements.push_back("FREE_NO_FINGER");
        spec_messages.push_back("DON'T MOVE your FINGER but MOVE EVERYTHING ELSE!");

        spec_movements.push_back("NO_FINGER_NO_WRIST");
        spec_messages.push_back("DON'T MOVE your FINGER and DON'T MOVE your WRIST but MOVE EVERYTHING ELSE!");

        //spec_movements.push_back("EMPTY_RUN");
        //spec_messages.push_back("MEASUREMENT ISN'T USEFUL");

        //special states
        // -1 -> no movements (On arm, but everywhere else)
        // -2 -> free movements (technically no active measuring)
        // -3 -> free active movements (with wrist, arm twist, elbow)
        // -4 -> free active movements (without wrist, with arm twist, with elbow)
        // -5 -> no finger movements (with wrist, arm twist, elbow)
        // -6 -> no finger movements (without wrist, with arm twist, with elbow)
        //free movements (without wrist, elbow) //free movements with wrist  //free movement fully

    }
	coordinator(){};
	coordinator(const char* name){
		std::ifstream infile;
        infile.open(name); //, std::ofstream::out);
		bool l = false;
		std::string temp, temp2;
        while(getline(infile, temp)){
            std::getline(infile, temp2);
            movements.push_back(temp);
            messages.push_back(temp2);
		}
        infile.close();
		max_state = movements.size();
        create_special_states();
        isPaused = false;
        isWait = true;
        own_iteration_num = 0;
	};
	~coordinator(){};
	void rhythim_setter(int _second, int emp, int w, int movlen, int _amount){  //hibas
		second = _second; free_run = emp; wait = w; movement_length = movlen; amount = _amount;
	}
	void reader(char* name){

        ///=============================================================================
        //File built like
        // movement
        // message
        // movement
        // message
        //...
        ///=============================================================================
        ///it just has the movements everything else is hard coded -> not good

		std::ifstream infile;
        infile.open(name); //, std::ofstream::out);
		bool l = false;
		std::string temp, temp2;
        while(getline(infile, temp) !=""){
            std::getline(infile, temp2);
            movements.push_back(temp);
            messages.push_back(temp2);
		}
        infile.close();
		max_state = movements.size();
	}
    void readerG(char* name, std::string){

        ///=============================================================================
        //Files:
        // movement_list -> only has the movements
        // special_movements -> same as movements
        // events -> has a list of events and their duration and repetition? maybe just what main events will happen
        // basic config -> which instruments are used, how long, how many repeats, minimum useful movements, etc.
        //...
        ///=============================================================================
        ///it just has the movements everything else is hard coded -> not good

        std::ifstream infile;
        infile.open(name); //, std::ofstream::out);
        bool l = false;
        std::string temp, temp2;
        while(getline(infile, temp) !=""){
            std::getline(infile, temp2);
            movements.push_back(temp);
            messages.push_back(temp2);
        }
        infile.close();
        max_state = movements.size();
    }
	void statelist_maker(int after_how_many){
        srand((unsigned) time(0));
        int RN, PN, helper;
        int temp = (max_state+spec_movements.size())*100;
        int temp2 = temp/after_how_many;
        RN = amount/(spec_movements.size()-1);
        std::vector<int> spec_amount(spec_movements.size()-1, RN);
        std::vector<int> tempv(max_state);
        for (int j = 1; j<=amount; j++) {

            for (int i = 0; i < max_state; i++) {
                tempv[i] = i;
            }
            for (int i = 0; i < max_state * 3; i++) {
                RN = int(rand() % max_state);
                PN = int(rand() % max_state);
                helper = tempv[PN];
                tempv[PN] = tempv[RN];
                tempv[RN] = helper;
            }
            for (int i = 0; i < tempv.size(); i++) {
                statelist.push_back(tempv[i]);
            }
            RN = int(rand() % spec_amount.size());
            while (spec_amount[RN] - 1 < 0) {
                RN = int(rand() % spec_amount.size());
            }
            RN = -1 * (RN + 2);
            statelist.push_back(RN);
            if (j%after_how_many == 0) statelist.push_back(-1);
        }
        statelist.push_front(-1);
        cur = statelist.begin();
        current_goal = free_run;
	}
    int overall_time(){  //hibas
        int sum = 0;
        for(std::list<int>::iterator IT = statelist.begin(); IT!=statelist.end(); IT++){
            if(*IT==-1) {sum += free_run; continue;}
            if(*IT>-1) {sum += movement_length+wait;continue;}
            if(*IT>-7) {sum += 41*second;}
        }
        return sum;
    }
   int check_sequence(){
        int sum1 = 0,sum2 = 0;
        std::list<int>::iterator IT = statelist.begin();
        if (*IT!=-1) return *IT;
        sum2++;
        IT++;
        for( ;IT!=statelist.end(); IT++){
            if (*IT<0){if(sum1 != max_state && sum1!=0) return sum2; sum1 = 0;} else {sum1++;}
            sum2++;
        }
        return -1;
    }
    int get_max_state_num(){
        return max_state;
    }
    int get_special_state_num(){
        return spec_movements.size();
    }
	std::string message() const {if (*cur>-1) return messages[*cur];
        if (*cur>-(spec_movements.size()+1)) return spec_messages[abs(*cur)-1];
        return "ERROR";
    }
    std::string message(int state) const {if (state>-1) return messages[state];
        if (state>-(spec_movements.size()+1)) return spec_messages[abs(state)-1];
        return "ERROR";
    }
    std::string curr_state() const {if (*cur>-1) return movements[*cur];
        if (*cur>-(spec_movements.size()+1)) return spec_movements[abs(*cur)-1];
        return "ERROR";
    }
    int curr_statei() const {if (isWait) return -1;
        return *cur;};
    void update_goal(){
        if(*cur==-1) {current_goal = free_run; return;}
        if(*cur>-1) {current_goal = movement_length; return;}
        if(*cur>-(spec_movements.size()+1)) {current_goal = 36*second; return;}
    }
    void Pause()
    {
        if(isPaused){cur=curs;update_goal();}else{curs=cur;cur=statelist.begin();current_goal = -1;}
        isPaused = !isPaused;
        own_iteration_num = 0;
    };
    void Repeat_last(){
        cur--;
        isWait= true;
        current_goal = wait;
        own_iteration_num = 0;
    };
    int& curr_iter(){return own_iteration_num;}
    int state_move(){
        return *(++cur);
    }
    int next_move(){
        cur++;
        return *(cur--);
    }
    void DO( std::string& NEXT) {
        own_iteration_num++;
        if(own_iteration_num == current_goal){isWait = !isWait;if(isWait){current_goal = wait;}else{state_move();update_goal();}own_iteration_num = 0;}
        if(current_goal - own_iteration_num <= 2*second) {
            if (isWait) { NEXT = "Prepare for next movement"; }
        }else if (own_iteration_num == 0){
            NEXT = "";
        }
    }
    bool isDone(){return cur == statelist.end();}
};
#endif //COORDINATOR_H