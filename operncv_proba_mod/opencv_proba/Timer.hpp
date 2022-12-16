//
// Created by ghuno
//

#ifndef SYSTIMER_H
#define SYSTIMER_H

#include <ctime>
class Timer{
public:
    typedef std::clock_t Ticks;
private:
    Ticks STRT;
    Ticks LSTP;
    Ticks HSTP;
public:

    Timer(bool start_now = false){if (start_now) STRT = GetTicks(); }
    static Ticks GetTicks()
    {
        return std::clock();
    }
    static double ms(Ticks ticks)
    {
        return ticks * 1000.0 / CLOCKS_PER_SEC;
    }
    Ticks Start()
    {   return STRT = GetTicks();  }
    Ticks Stop()
    {   return LSTP = GetTicks();  }
    Ticks Lap()
    {   HSTP = GetTicks();
        HSTP = HSTP - LSTP;
        LSTP = HSTP + LSTP;
        return HSTP;}
    Ticks Time()
    {   LSTP = GetTicks();
        return LSTP - STRT; }
    Ticks NSTime()
    {   return GetTicks()  - STRT; }
    double ms()
    {
        return ms(LSTP - STRT);
    }

};

#endif //SYSTIMER_H