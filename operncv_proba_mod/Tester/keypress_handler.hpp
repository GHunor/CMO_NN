//
// Created by ghuno on 2022-04-22.
//

#ifndef TESTER_KEYPRESS_HANDLER_HPP
#define TESTER_KEYPRESS_HANDLER_HPP

#include <vector>
#include <map>
#include <set>

#include "useful_macros.h"


template< typename F, typename S, typename T>
class trio{
public:
    F* first;
    S* second;
    T* third;
    trio();
    trio(F First, S Second, T Third){
        first = new F(First);
        second = new S(Second);
        third = new T(Third);
    }
    trio(trio const &Trio){
        first = new F(*Trio.first);
        second = new S(*Trio.second);
        third = new T(*Trio.third);
    }
    ~trio(){
        delete(first);
        delete(second);
        delete(third);
    }
};

template<typename F, typename S, typename T>
trio<F, S, T> make_trio(F First, S Second, T Third) {
    return trio<F, S, T> ::trio(First, Second, Third);
}

class keypress_handler{
    std::vector<std::pair<char, int> > list_of_keys;
    static const char valid_keys[]; //= {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','1','2','3','4','5','6','7','8','9','0'};
    static const int key_number;
    std::set<char> Search_keys;
    void _set_seter(){
        std::set<char> TSet(valid_keys, valid_keys+key_number);
        Search_keys = TSet;
        key_bools = new bool;
        key_bools2 = new bool;
    }

public:
    bool *key_bools;
    bool *key_bools2;
    keypress_handler(){
        _set_seter();
    };
    keypress_handler(const std::vector<std::pair<char, int> > &listOfKeys){
        _set_seter();
        for IRANGE(listOfKeys.size()) {
            if (Search_keys.find(listOfKeys[i].first)!=Search_keys.end()){
                list_of_keys.push_back(listOfKeys[i]);
            }
        }

    };
    keypress_handler(const std::vector<char > &listOfKeys) {
        _set_seter();
        for IRANGE(listOfKeys.size()) {
            if (Search_keys.find(listOfKeys[i])!=Search_keys.end()){
                list_of_keys.push_back(std::make_pair(listOfKeys[i], 0));
            }
        }
    };
    keypress_handler(const char &Key){
        if (key_validity_check(Key)){
            list_of_keys.push_back(std::make_pair(Key, 20));
        }
    };
    void Add_key(const char &Key, int time){
        if (key_validity_check(Key)){
            list_of_keys.push_back(std::make_pair(Key, time));
        }
    }
    void Create_key_bools(){
        delete(key_bools);
        delete(key_bools2);
        key_bools = new bool[list_of_keys.size()];
        key_bools2 = new bool[list_of_keys.size()];
        for IRANGE(list_of_keys.size()){
            key_bools[i] = false;
            key_bools2[i] = false;
        }
    }
    //bool key_validity_check(std::string key){return Search_keys.find(key)!=Search_keys.end();}
    bool key_validity_check(char key){
        //std::string tmp = "" + key;
        return Search_keys.find(key)!=Search_keys.end();
    }
    void Do(){
        for IRANGE(list_of_keys.size()) {
                if (list_of_keys[i].second < 20 && list_of_keys[i].second > 0){ list_of_keys[i].second++; key_bools2[i] = false;}
                if (list_of_keys[i].second == 20){ list_of_keys[i].second = 0; key_bools[i]= false; key_bools2[i] = false;}
                if (GetKeyState(list_of_keys[i].first) & 0x8000/*Check if high-order bit is set (1 << 15)*/ && list_of_keys[i].second < 1) {
                    list_of_keys[i].second++;
                    std::cout << "pressed ";
                    key_bools[i] = true;
                    key_bools2[i] = true;
                }
        };
    }
};
const char keypress_handler::valid_keys[] = {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','1','2','3','4','5','6','7','8','9','0'};
/*{"Q","W","E","R","T",
                                                "Y","U","I","O","P",
                                                "A","S","D","F","G",xxxppprrrr
                                                "H","J","K","L","Z",
                                                "X","C","V","B","N",

                                                "M","1","2","3","4",
                                                "5","6","7","8","9","0"};*/
const int keypress_handler::key_number = 36;

/*
if(GetKeyState('X') & 0x8000 && pressed_X < 1)
{
pressed_X++;
//Log.end();
Log.close();
PressedKey = "X";
break;
}
if(pressed_X<20 && pressed_X>0){pressed_X++;}
if(pressed_X==20){pressed_X = 0;PressedKey = "";}

if(GetKeyState('R') & 0x8000 && pressed_R < 1)
{
pressed_R++;
COOR.Repeat_last();
PressedKey = "R";
}
if(pressed_R<20 && pressed_R>0){pressed_R++;}
if(pressed_R==20){pressed_R = 0;PressedKey = "";}

if(GetKeyState('P') & 0x8000 && pressed_P <1)
{
pressed_P++;
COOR.Pause();
PressedKey = "P";
}
if(pressed_P<20 && pressed_P>0){pressed_P++;}
if(pressed_P==20){pressed_P = 0;PressedKey = "";}
*/
#endif //TESTER_KEYPRESS_HANDLER_HPP
