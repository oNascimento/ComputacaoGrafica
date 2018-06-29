#include "fkframer.h"

#ifndef M_PI_2
#define M_PI_2 1.5707963267948966192313216916398
#endif

FKFramer::FKFramer()
: currentFrame_(0),
  totalFrames_(0),
  frameStart_(-1.0)
{
  setupFrames();
}

#define FRAMEDURATION 1.0
void FKFramer::setupFrames()
{
  // This animation has 8 evenly spaced frames created from the forward kinematics motion scripts
  // from Advanced Animation and Rendering Techniques, Watt & Watt,  p391
  FKFrame frame1;
  frame1.setDuration(FRAMEDURATION);
  frame1.addAngle("RHipX", 0.0);
  frame1.addAngle("RKnee", 0.0);
  frame1.addAngle("RAnkle", 0.0);
  frame1.addAngle("LHipX", 0.0);
  frame1.addAngle("LKnee", 0.0);
  frame1.addAngle("LAnkle", 0.0);
  frame1.addAngle("RShoulderX", 0.0);
  frame1.addAngle("RElbow", 0.0);
  frame1.addAngle("LShoulderX", 0.0);
  frame1.addAngle("LElbow", 0.0);
  frames_.push_back(frame1);

  FKFrame frame2;
  frame2.setDuration(FRAMEDURATION);
  frame2.addAngle("RHipX", 22.5);
  frame2.addAngle("RKnee", -17.5);
  frame2.addAngle("RAnkle", -17.5);
  frame2.addAngle("LHipX", -17.5);
  frame2.addAngle("LKnee", 0.0);
  frame2.addAngle("LAnkle", 10.0);
  frame2.addAngle("RShoulderX", -22.5);
  frame2.addAngle("RElbow", 17.5);
  frame2.addAngle("LShoulderX", 17.5);
  frame2.addAngle("LElbow", 0.0);
  frames_.push_back(frame2);

  FKFrame frame3;
  frame3.setDuration(FRAMEDURATION);
  frame3.addAngle("RHipX", 45.0);
  frame3.addAngle("RKnee", -35.0);
  frame3.addAngle("RAnkle", -35.0);
  frame3.addAngle("LHipX", -35.0);
  frame3.addAngle("LKnee", -30.0);
  frame3.addAngle("LAnkle", -8.0);
  frame3.addAngle("RShoulderX", -45.0);
  frame3.addAngle("RElbow", 35.0);
  frame3.addAngle("LShoulderX", 35.0);
  frame3.addAngle("LElbow", 30.0);
  frames_.push_back(frame3);

  FKFrame frame4;
  frame4.setDuration(FRAMEDURATION);
  frame4.addAngle("RHipX", 22.5);
  frame4.addAngle("RKnee", 0.0);
  frame4.addAngle("RAnkle", 0.0);
  frame4.addAngle("LHipX", -17.5);
  frame4.addAngle("LKnee", -15.0);
  frame4.addAngle("LAnkle", -5.0);
  frame4.addAngle("RShoulderX", -22.5);
  frame4.addAngle("RElbow", 0.0);
  frame4.addAngle("LShoulderX", 17.5);
  frame4.addAngle("LElbow", 15.0);
  frames_.push_back(frame4);

  FKFrame frame5;
  frame5.setDuration(FRAMEDURATION);
  frame5.addAngle("RHipX", 0.0);
  frame5.addAngle("RKnee", 0.0);
  frame5.addAngle("RAnkle", 0.0);
  frame5.addAngle("LHipX", 0.0);
  frame5.addAngle("LKnee", 0.0);
  frame5.addAngle("LAnkle", 0.0);
  frame5.addAngle("RShoulderX", 0.0);
  frame5.addAngle("RElbow", 0.0);
  frame5.addAngle("LShoulderX", 0.0);
  frame5.addAngle("LElbow", 0.0);
  frames_.push_back(frame5);

  FKFrame frame6;
  frame6.setDuration(FRAMEDURATION);
  frame6.addAngle("RHipX", -17.5);
  frame6.addAngle("RKnee", 0.0);
  frame6.addAngle("RAnkle", 10.0);
  frame6.addAngle("LHipX", 22.5);
  frame6.addAngle("LKnee", -17.5);
  frame6.addAngle("LAnkle", -17.5);
  frame6.addAngle("RShoulderX", 17.5);
  frame6.addAngle("RElbow", 0.0);
  frame6.addAngle("LShoulderX", -22.5);
  frame6.addAngle("LElbow", 17.5);
  frames_.push_back(frame6);

  FKFrame frame7;
  frame7.setDuration(FRAMEDURATION);
  frame7.addAngle("RHipX", -35.0);
  frame7.addAngle("RKnee", -30.0);
  frame7.addAngle("RAnkle", -8.0);
  frame7.addAngle("LHipX", 45.0);
  frame7.addAngle("LKnee", -35.0);
  frame7.addAngle("LAnkle", -35.0);
  frame7.addAngle("RShoulderX", 35.0);
  frame7.addAngle("RElbow", 30.0);
  frame7.addAngle("LShoulderX", -45.0);
  frame7.addAngle("LElbow", 35.0);
  frames_.push_back(frame7);

  FKFrame frame8;
  frame8.setDuration(FRAMEDURATION);
  frame8.addAngle("RHipX", -17.5);
  frame8.addAngle("RKnee", -15.0);
  frame8.addAngle("RAnkle", -5.0);
  frame8.addAngle("LHipX", 22.5);
  frame8.addAngle("LKnee", 0.0);
  frame8.addAngle("LAnkle", 0.0);
  frame8.addAngle("RShoulderX", 17.5);
  frame8.addAngle("RElbow", 15.0);
  frame8.addAngle("LShoulderX", -22.5);
  frame8.addAngle("LElbow", 0.0);
  frames_.push_back(frame8);

  // Adding frame 1 to end for cyclic animation
  frames_.push_back(frame1);

  totalFrames_ = 8;
}

void FKFramer::update(Animation::angles_t& angles)
{
  // Has the timer been initialized?
  if(frameStart_ < 0.0)
    frameStart_ = timer_.getTime();

  // Get time elapsed since start of frame
  double t = timer_.getTime() - frameStart_;

  t *= rate_;

  if(t > frames_[currentFrame_].getDuration())
  {
    currentFrame_ = (currentFrame_ + 1) % totalFrames_;
    frameStart_ = timer_.getTime();
    t = 0.0;
  }

  // Interpolate for current values - moving along sine curve
//  double a = sin((t / frames_[currentFrame_].getDuration()) * M_PI_2);
  double a = t / frames_[currentFrame_].getDuration();

  FKFrame::frameAngles_t::const_iterator iter;
  for(iter = frames_[currentFrame_].begin(); iter != frames_[currentFrame_].end(); ++iter)
  {
    angles[iter->first].setValue(iter->second + ((frames_[currentFrame_ + 1][iter->first] - iter->second) * a));
//    angles[iter->first] = iter->second + ((frames_[currentFrame_ + 1][iter->first] - iter->second) * a);
  }
}
