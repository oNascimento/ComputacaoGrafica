#ifndef SHAPECUBE_H
#define SHAPECUBE_H

#include "shape.h"

class ShapeCube : public Shape
{
protected:
  void polygon(int a, int b, int c, int d, int facenum);
public:
  virtual void draw();
};

#endif
