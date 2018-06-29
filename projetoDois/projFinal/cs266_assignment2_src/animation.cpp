#include "framer.h"
#include "animation.h"

void Animation::addActor(Skeleton* skeleton, Framer* framer)
{
  actors_.push_back(new Actor(skeleton, framer));

  ActorInitializer ao(actors_.back());
  skeleton->visitArcs(ao);
}

// update the frame
void Animation::update()
{
  actors_t::iterator iter;
  for(iter = actors_.begin(); iter != actors_.end(); ++iter)
  {
    if((*iter)->framer_)
      (*iter)->framer_->update((*iter)->angles_);

    // Traverse the skeleton
    ActorUpdater au(*iter);
    (*iter)->skeleton_->visitArcs(au);
  }
}

// draw the current frame
void Animation::draw()
{
  actors_t::iterator iter;
  for(iter = actors_.begin(); iter != actors_.end(); ++iter)
  {
    (*iter)->skeleton_->evaluate();
  }
}

Animation::~Animation()
{
  actors_t::iterator iter;
  for(iter = actors_.begin(); iter != actors_.end(); ++iter)
  {
    delete (*iter);
  }
}
