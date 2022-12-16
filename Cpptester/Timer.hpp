//
// Created by ghuno
//

#ifndef SYSTIMER_H
#define SYSTIMER_H
class Timer{
	public:
	clock_t get_curtime_INtick(){
		return clock();
	}

	double INms(clock_t ctime){
		return ticks * 1000.0 / CLOCKS_PER_SEC;
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
}
#endif //SYSTIMER_H