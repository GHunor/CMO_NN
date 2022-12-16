//
// Created by ghuno on 2021-11-24.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
class rnd_data{


void set_base(){
    srand((unsigned) time(0));
}
uint_8 make_uint8(){
    return rand() % 256;
}
double make_double(){
    return rand()/rand();
}
};