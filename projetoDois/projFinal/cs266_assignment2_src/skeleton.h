#ifndef SKELETON_H
#define SKELETON_H

#include <vector>
#include <string>

#include "vector3.h"

class Shape;

// A single degree of freedom
class SkelDOF
{
protected:
  double min_;
  double max_;
  double value_;
public:
  SkelDOF(double value = 0.0, double min=-360.0, double max=360.0);
  SkelDOF(const SkelDOF& sdof) : min_(sdof.min_), max_(sdof.max_), value_(sdof.value_) { }

  double getValue() const { return value_; }
  void setValue(double value);

  double getMin() const { return min_; }
  double getMax() const { return max_; }

  void setMin(double min) { min_ = min; }
  void setMax(double max) { max_ = max; }
  void setMinMax(double min, double max) { min_ = min; max_ = max; }
};

class SkelArc;
typedef std::vector<SkelArc*> skelarcs_t;

// The skeleton link
class SkelNode
{
protected:
  std::string name_;
  Shape* shape_;
  skelarcs_t arcs_;
public:
  SkelNode(const std::string& name = "Link", Shape* shape = NULL) : name_(name), shape_(shape) { }

  std::string getName() const { return name_; }
  Shape* getShape() const { return shape_; }

  void setName(const std::string& name) { name_ = name; }
  void setShape(Shape* shape) { shape_ = shape; }

  void addArc(SkelArc* arc) { arcs_.push_back(arc); }

  skelarcs_t::iterator begin() { return arcs_.begin(); }
  skelarcs_t::const_iterator begin() const { return arcs_.begin(); }
  skelarcs_t::iterator end() { return arcs_.end(); }
  skelarcs_t::const_iterator end() const { return arcs_.end(); }
};

// The skeleton joint
class SkelArc
{
protected:
  std::string name_;
  SkelDOF rotAngle_;
  Vector3 rotAxis_;

  Vector3 trans_;

  SkelNode* node_;
public:
  SkelArc(const std::string& name = "Joint", SkelNode* node = NULL) : name_(name), node_(node) { }

  std::string getName() const { return name_; }
  SkelNode* getNode() const { return node_; }
  SkelDOF* getRotationAngle() const { return (SkelDOF*)&rotAngle_; }
  Vector3* getRotationAxis() const { return (Vector3*)&rotAxis_; }
  Vector3* getTranslation() const { return (Vector3*)&trans_; }

  void setName(const std::string& name) { name_ = name; }
  void setNode(SkelNode* node) { node_ = node; }
  void setRotationAngle(double angle) { rotAngle_.setValue(angle); }
  void setRotationAngle(const SkelDOF& rotAngle) { rotAngle_ = rotAngle; }
  void setRotationAxis(double x, double y, double z) { rotAxis_.set(x, y, z); }
  void setRotationAxis(const Vector3& rotAxis) { rotAxis_ = rotAxis; }
  void setTranslation(double x, double y, double z) { trans_.set(x, y, z); }
  void setTranslation(const Vector3& trans) { trans_ = trans; }
};

// The skeleton
class Skeleton
{
public:
  class NodeVisitor
  {
  public:
    virtual void operator()(SkelNode* node) = 0;
    virtual ~NodeVisitor() { }
  };
public:
  class ArcVisitor
  {
  public:
    virtual void operator()(SkelArc* arc) = 0;
    virtual ~ArcVisitor() { }
  };
protected:
  SkelArc* root_;
protected:
  SkelNode* findNextNode(SkelArc* arc, const std::string& name) const;
  SkelArc* findNextArc(SkelArc* arc, const std::string& name) const;
  void visitNextNode(SkelArc* arc, NodeVisitor& visitor);
  void visitNextArc(SkelArc* arc, ArcVisitor& visitor);
  void evalArc(const SkelArc* arc) const;
public:
  Skeleton(SkelArc* root = NULL) : root_(root) { }

  SkelArc* getRootArc() const { return root_; }

  void setRootArc(SkelArc* root) { root_ = root; }

  SkelNode* findNode(const std::string& name) const { return findNextNode(root_, name); }

  SkelArc* findArc(const std::string& name) const { return findNextArc(root_, name); }

  void visitNodes(NodeVisitor& visitor) { visitNextNode(root_, visitor); }

  void visitArcs(ArcVisitor& visitor) { visitNextArc(root_, visitor); }

  void evaluate() const { if(root_) evalArc(root_); }

  virtual ~Skeleton() { }
};

#endif
