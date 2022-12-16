//
// Created by ghuno on 2022-04-24.
//

#ifndef TESTER_PROMPT_HANDLER_HPP
#define TESTER_PROMPT_HANDLER_HPP

#include <iostream>
#include <string>
#include <windows.h>


class promthandler{
public:
    //promthandler();
    //promthandler(int row, int coloums){};
    void clean(){
        std::cout << '\r';
    };
    void new_line(){
        std::cout << '\n';
    };
    void solidify(){
        std::cout << std::flush;
    };
    void total_wipe(){
        system("cls");
    };
    std::string askfor_string(){
        std::string tmp;
        std::cin>>tmp;
        return tmp;
    };
    int askfor_int(){
        int tmp;
        std::cin>>tmp;
        return tmp;
    };
    friend promthandler &operator<<(promthandler &promthandler, const std::string &string) {
        std::cout << string;
        return promthandler;
    }
    friend promthandler &operator<<(promthandler &promthandler, const int &number) {
        std::cout << number;
        return promthandler;
    }
    friend promthandler &operator<<(promthandler &promthandler, const double &number) {
        std::cout << number;
        return promthandler;
    }
    friend promthandler &operator<<(promthandler &promthandler, const float &number) {
        std::cout << number;
        return promthandler;
    }
    //friend promthandler &operator<<(promthandler &promthandler, std::endl) {
    //    promthandler.new_line();
    //    return promthandler;
    //}


};

#endif //TESTER_PROMPT_HANDLER_HPP
