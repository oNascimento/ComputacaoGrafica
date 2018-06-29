#ifndef SHAPE_H
#define SHAPE_H

#include "vector3.h"

class Shape
{
protected:
  Vector3 scale_;
  double rotAngle_;
  Vector3 rotAxis_;
  Vector3 trans_;
public:
  Shape() : rotAngle_(0.0) { }
  virtual ~Shape() { }

  virtual void draw() = 0;

  Vector3* getScale() const { return (Vector3*)&scale_; }
  double getRotationAngle() const { return rotAngle_; }
  Vector3* getRotationAxis() const { return (Vector3*)&rotAxis_; }
  Vector3* getTranslation() const { return (Vector3*)&trans_; }

  void setScale(double x, double y, double z) { scale_.set(x, y, z); }
  void setScale(const Vector3& scale) { scale_ = scale; }
  void setRotationAngle(double angle) { rotAngle_ = angle; }
  void setRotationAxis(double x, double y, double z) { rotAxis_.set(x, y, z); }
  void setRotationAxis(const Vector3& rot) { rotAxis_ = rot; }
  void setTranslation(double x, double y, double z) { trans_.set(x, y, z); }
  void setTranslation(const Vector3& trans) { trans_ = trans; }
};

#endif
