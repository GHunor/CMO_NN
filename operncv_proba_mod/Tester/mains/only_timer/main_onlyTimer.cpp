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
//#include "Coordinator.hpp"
int main(){
    std::cout<<CLOCKS_PER_SEC<<"\n";
    Timer timer(true);
    sleep(25);
    timer.Time();
    std::cout<<timer.ms();
    timer.Time();
    std::cout<<"\n ; "<<timer.ms();
    return 0;
}