#ifndef IKFRAMER_H
#define IKFRAMER_H

#include <string>
#include <map>

#include "skeleton.h"
#include "matrix.h"
#include "matrix44.h"
#include "vector3.h"
#include "framer.h"

class IKSolver
{
public:
  class InfoGetter : public Skeleton::ArcVisitor
  {
  public:
    unsigned int total_;
    Matrix44 G_;
    std::vector<Vector3> positions_;
    std::vector<SkelDOF> angles_;
    std::vector<Vector3> axes_;
    std::vector<std::string> names_;
  public:
    InfoGetter();
    void reset();
    void operator()(SkelArc* arc);
  };
protected:
  Matrix J_;       // NxM Jacobian matrix
  Matrix JT_;      // NxM Jacobian matrix transpose
  Matrix JTJJTI_;  // JT(J.JT)^-1
  Vector3 goal_;
  Skeleton skel_;
  double stepScale_;
protected:
  void computeJacobian(const InfoGetter& ig);
public:
  IKSolver(const Skeleton* skel, const std::string& root, const std::string& endeffector);

  void setStepScale(double s) { stepScale_ = s; }

  void setGoal(double x, double y, double z) { goal_.set(x, y, z); }

  void solve(Animation::angles_t& angles);
};

class IKFramer : public Framer
{
public:
  typedef std::map<std::string, IKSolver> iksolvers_t;
protected:
  iksolvers_t iksolvers_;
public:
  IKFramer() { }

  void addChain(const std::string& name, const Skeleton* skel, const std::string& root, const std::string& endeffector);

  void setGoal(const std::string& name, double x, double y, double z);

  void update(Animation::angles_t& angles);
};

#endif
