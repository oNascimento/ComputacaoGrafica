#ifndef FKFRAMER_H
#define FKFRAMER_H

#include <map>
#include <vector>
#include <string>
#include "animation.h"
#include "timer.h"
#include "framer.h"

class FKFrame
{
public:
  typedef std::map<std::string, double> frameAngles_t;
protected:
  double duration_;
  frameAngles_t frameAngles_;
public:
  FKFrame() : duration_(0.0) { }

  double getDuration() const { return duration_; }

  void setDuration(double duration) { duration_ = duration; }

  void addAngle(const std::string& name, double angle) { frameAngles_.insert(std::make_pair(name, angle)); }

  frameAngles_t::iterator begin() { return frameAngles_.begin(); }
  frameAngles_t::const_iterator begin() const { return frameAngles_.begin(); }

  frameAngles_t::iterator end() { return frameAngles_.end(); }
  frameAngles_t::const_iterator end() const { return frameAngles_.end(); }

  double operator[](const std::string& s) { return frameAngles_[s]; }
};

class FKFramer : public Framer
{
public:
  typedef std::vector<FKFrame> frames_t;
protected:
  frames_t frames_;
protected:
  unsigned int currentFrame_;
  unsigned int totalFrames_;
  double       frameStart_;
  Timer        timer_;
protected:
  void setupFrames();
public:
  FKFramer();
  virtual void update(Animation::angles_t& angles);
};

#endif
