
#include <ctime>
    class Timer{
    public:
        typedef std::clock_t Ticks;
        Ticks t_;

        static Ticks GetTicks ()
        {
            return std::clock();
        }

        static double ms (Ticks ticks)
        {
            return ticks * 1000.0 / CLOCKS_PER_SEC;
        }

        Timer (bool start_now = false))  { if (start_now) t_ = GetTicks(); }

        Ticks Start ()  {  return t_ = GetTicks();  }
        Ticks Stop ()   {  return t_ = GetTicks() - t_;  }
        double ms () const {  return ms(t_);   }
    };

