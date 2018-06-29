#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include "skeleton.h"

class Framer;

class Animation
{
public:
  typedef std::map<std::string, SkelDOF> angles_t;
public:
  class Actor
  {
  public:
    Skeleton* skeleton_;
    Framer* framer_;
    angles_t angles_;
  public:
    Actor(Skeleton* skeleton, Framer* framer) : skeleton_(skeleton), framer_(framer) { }
  };
  typedef std::vector<Actor*> actors_t;
protected:
  class ActorInitializer : public Skeleton::ArcVisitor
  {
  protected:
    Actor* a_;
  public:
    ActorInitializer(Animation::Actor* a) : a_(a) { }
    virtual void operator()(SkelArc* arc)
    {
      a_->angles_.insert(std::make_pair(arc->getName(), *arc->getRotationAngle()));
    }
  };
protected:
  class ActorUpdater : public Skeleton::ArcVisitor
  {
  protected:
    Actor* a_;
  public:
    ActorUpdater(Actor* a) : a_(a) { }
    virtual void operator()(SkelArc* arc)
    {
      angles_t::const_iterator iter = a_->angles_.find(arc->getName());
      if(iter != a_->angles_.end())
        arc->setRotationAngle(iter->second);
    }
  };
protected:
  // The actors
  actors_t actors_;
public:
  Animation() { }

  void addActor(Skeleton* skeleton, Framer* framer);

  // update the frame
  void update();

  // draw the current frame
  void draw();

  actors_t::iterator begin() { return actors_.begin(); }
  actors_t::const_iterator begin() const { return actors_.begin(); }
  actors_t::iterator end() { return actors_.end(); }
  actors_t::const_iterator end() const { return actors_.end(); }

  virtual ~Animation();
};

#endif
