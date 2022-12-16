//
// Created by ghuno
//
#include <ctime>

#ifndef SYSTIMER_H
#define SYSTIMER_H
    std::clock_t get_curtime_INtick(){
		return std::clock();
	}
	double INms(std::clock_t ctime){
		return ctime / CLOCKS_PER_SEC  * 1000.0 ;
	}
	double get_curtime_INms(){
		return INms(get_curtime_INtick ());
	}
	double TestSysTimer(){
		double Sum = 0.0;
		for (int i = 0; i<10; i++){

			double t0 = get_curtime_INms(), t1, t2;
			do t1 = get_curtime_INms(); while (t1 == t0);
			do t2 = get_curtime_INms(); while (t2 == t1);
			Sum = Sum + t2-t1;
		}
		return Sum/10.0;
	}
#endif //SYSTIMER_H