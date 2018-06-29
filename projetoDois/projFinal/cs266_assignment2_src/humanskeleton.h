#ifndef HUMANSKELETON_H
#define HUMANSKELETON_H

#include "skeleton.h"

class HumanSkeleton : public Skeleton
{
public:
  class AngleInitializer : public Skeleton::ArcVisitor
  {
  public:
    std::map<std::string, SkelDOF> angles;
  public:
    virtual void operator()(SkelArc* arc)
    {
      std::map<std::string, SkelDOF>::const_iterator iter = angles.find(arc->getName());
      if(iter != angles.end())
        arc->setRotationAngle(iter->second);
    }
  };
protected:
  void initializeAngles();
  void buildSkeleton();
public:
  HumanSkeleton();
  virtual ~HumanSkeleton() { }
};

#endif
