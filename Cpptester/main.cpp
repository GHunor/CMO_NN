//
// Created by ghuno on 2021-11-19.

#include <iostream>
#include <string>
#include "Datalogger.hpp"





int main()
{

    std::vector<int> vecint;
    vecint.push_back(1);
    vecint.push_back(2);
    vecint.push_back(3);
    vecint.push_back(4);
    std::vector<double> vecdouble;
    vecdouble.push_back(1.1);
    vecdouble.push_back(1.2);
    vecdouble.push_back(1.3);
    vecdouble.push_back(1.4);
    std::string str = "message";

    Datalogger D("measurement_result");
    for (int i = 0; i<2000; i++)
    {
        D.set_system_time(float(i));
        D.set_myo(vecint);
        D.set_myo_time(uint64_t(i));
        D.set_glove(vecdouble) ;
        D.set_glove_time( double(i));
        D.set_movement(str);
        D.set_message(str);
        D.set_pressed_key(str);
        D.new_line();
    }
    D.end();

    return 1;
}
