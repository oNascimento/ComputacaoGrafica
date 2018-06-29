#ifndef FRAMER_H
#define FRAMER_H

#include "animation.h"

class Framer
{
protected:
  double rate_;
public:
  double getRate() const { return rate_; }
  void setRate(double rate) { rate_ = rate; }
  virtual void update(Animation::angles_t& angles) = 0;
  virtual ~Framer() { }
};

#endif
