#ifndef TIMER_H
#define TIMER_H

#include <sys/timeb.h>
#include <time.h>

class Timer
{
public:
  double getTime()
  {
    struct timeb tb;
    ftime(&tb);
    return (double)tb.time + ((double)tb.millitm / 1000.0f);
  }
};

#endif
