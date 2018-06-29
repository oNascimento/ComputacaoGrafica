#include <map>
#include <string>
#include "names.h"
#include "shapecube.h"
#include "humanskeleton.h"

HumanSkeleton::HumanSkeleton()
: Skeleton(NULL)
{
  buildSkeleton();
  initializeAngles();
}

void HumanSkeleton::initializeAngles()
{
  AngleInitializer ai;
  ai.angles.insert(std::make_pair(ROOT, SkelDOF(0.0, 0.0, 0.0)));
  ai.angles.insert(std::make_pair(NECKBASE, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(HEADBASE, SkelDOF(0.0, -45.0, 45.0)));
  ai.angles.insert(std::make_pair(RSHOULDERZ, SkelDOF(0.0, 0.0, 90.0)));
  ai.angles.insert(std::make_pair(RSHOULDERY, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(RSHOULDERX, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(RELBOW, SkelDOF(0.0, 0.0, 90.0)));
  ai.angles.insert(std::make_pair(LSHOULDERZ, SkelDOF(0.0, 0.0, 90.0)));
  ai.angles.insert(std::make_pair(LSHOULDERY, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(LSHOULDERX, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(LELBOW, SkelDOF(0.0, 0.0, 90.0)));
  ai.angles.insert(std::make_pair(RHIPZ, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(RHIPY, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(RHIPX, SkelDOF(10.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(RKNEE, SkelDOF(-10.0, -120.0, 0.0)));
  ai.angles.insert(std::make_pair(RANKLE, SkelDOF(0.0, -45.0, 45.0)));
  ai.angles.insert(std::make_pair(LHIPZ, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(LHIPY, SkelDOF(0.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(LHIPX, SkelDOF(10.0, -90.0, 90.0)));
  ai.angles.insert(std::make_pair(LKNEE, SkelDOF(-10.0, -120.0, 0.0)));
  ai.angles.insert(std::make_pair(LANKLE, SkelDOF(0.0, -45.0, 45.0)));
/*
  ai.angles.insert(std::make_pair(ROOT, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(NECKBASE, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(HEADBASE, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(RSHOULDER, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(RELBOW, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(LSHOULDER, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(LELBOW, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(RHIP, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(RKNEE, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(RANKLE, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(LHIP, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(LKNEE, SkelDOF(0.0)));
  ai.angles.insert(std::make_pair(LANKLE, SkelDOF(0.0)));
*/
  visitArcs(ai);
}

void HumanSkeleton::buildSkeleton()
{
  // Create the torso
  ShapeCube* cube = new ShapeCube();                  // Initial shape
  cube->setScale(0.25, 0.5, 0.10);                    // Shape the torso

  SkelNode* torso = new SkelNode("Torso", cube);

  SkelArc* root = new SkelArc("Root", torso);
  root->setTranslation(0.0, 0.5, 0.0);                // Position the torso
  setRootArc(root);

  // Create the neck
  cube = new ShapeCube();
  cube->setScale(0.05, 0.05, 0.05);
  cube->setTranslation(0.0, 0.05, 0.0);

  SkelNode* neck = new SkelNode("Neck", cube);

  SkelArc* neckBase = new SkelArc("NeckBase", neck);
  neckBase->setTranslation(0.0, 0.5, 0.0);
  neckBase->setRotationAxis(0.0, 1.0, 0.0);
  torso->addArc(neckBase);

  // Create the head
  cube = new ShapeCube();
  cube->setScale(0.1, 0.2, 0.2);
  cube->setTranslation(0.0, 0.2, 0.0);

  SkelNode* head = new SkelNode("Head", cube);

  SkelArc* headBase = new SkelArc("HeadBase", head);
  headBase->setTranslation(0.0, 0.05, 0.0);
  headBase->setRotationAxis(-1.0, 0.0, 0.0);
  neck->addArc(headBase);

  // Create upper right arm
  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* rupperarmx = new SkelNode("RupperArmX", cube);
  SkelArc* rshoulderx = new SkelArc("RShoulderX", rupperarmx);
  rshoulderx->setTranslation(-0.3, 0.5, 0.0);
  rshoulderx->setRotationAxis(-1.0, 0.0, 0.0);
  torso->addArc(rshoulderx);

  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* rupperarmy = new SkelNode("RupperArmY", cube);
  SkelArc* rshouldery = new SkelArc("RShoulderY", rupperarmy);
  rshouldery->setRotationAxis(0.0, -1.0, 0.0);
  rupperarmx->addArc(rshouldery);

  cube = new ShapeCube();
  cube->setScale(0.05, 0.25, 0.05);
  cube->setTranslation(0.0, -0.25, 0.0);

  SkelNode* rupperarmz = new SkelNode("RUpperArmZ", cube);

  SkelArc* rshoulderz = new SkelArc("RShoulderZ", rupperarmz);
  rshoulderz->setRotationAxis(0.0, 0.0, -1.0);
  rupperarmy->addArc(rshoulderz);

  // Create lower right arm
  cube = new ShapeCube();
  cube->setScale(0.05, 0.3, 0.05);
  cube->setTranslation(0.0, -0.3, 0.0);

  SkelNode* rlowerarm = new SkelNode("RLowerArm", cube);

  SkelArc* relbow = new SkelArc("RElbow", rlowerarm);
  relbow->setTranslation(0.0, -0.5, 0.0);
  relbow->setRotationAxis(-1.0, 0.0, 0.0);
  rupperarmz->addArc(relbow);

  // Create upper left arm
  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* lupperarmx = new SkelNode("LupperArmX", cube);
  SkelArc* lshoulderx = new SkelArc("LShoulderX", lupperarmx);
  lshoulderx->setTranslation(0.3, 0.5, 0.0);
  lshoulderx->setRotationAxis(-1.0, 0.0, 0.0);
  torso->addArc(lshoulderx);

  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* lupperarmy = new SkelNode("LupperArmY", cube);
  SkelArc* lshouldery = new SkelArc("LShoulderY", lupperarmy);
  lshouldery->setRotationAxis(0.0, -1.0, 0.0);
  lupperarmx->addArc(lshouldery);

  cube = new ShapeCube();
  cube->setScale(0.05, 0.25, 0.05);
  cube->setTranslation(0.0, -0.25, 0.0);

  SkelNode* lupperarmz = new SkelNode("LUpperArmZ", cube);

  SkelArc* lshoulderz = new SkelArc("LShoulderZ", lupperarmz);
  lshoulderz->setRotationAxis(0.0, 0.0, -1.0);
  lupperarmy->addArc(lshoulderz);

  // Create lower left arm
  cube = new ShapeCube();
  cube->setScale(0.05, 0.30, 0.05);
  cube->setTranslation(0.0, -0.30, 0.0);

  SkelNode* llowerarm = new SkelNode("LLowerArm", cube);

  SkelArc* lelbow = new SkelArc("LElbow", llowerarm);
  lelbow->setTranslation(0.0, -0.5, 0.0);
  lelbow->setRotationAxis(-1.0, 0.0, 0.0);
  lupperarmz->addArc(lelbow);

  // Create upper right leg
  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* rupperlegx = new SkelNode("RUpperLegX", cube);
  SkelArc* rhipx = new SkelArc("RHipX", rupperlegx);
  rhipx->setTranslation(-0.15, -0.5, 0.0);
  rhipx->setRotationAxis(-1.0, 0.0, 0.0);
  torso->addArc(rhipx);

  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* rupperlegy = new SkelNode("RUpperLegY", cube);
  SkelArc* rhipy = new SkelArc("RHipY", rupperlegy);
  rhipy->setRotationAxis(0.0, -1.0, 0.0);
  rupperlegx->addArc(rhipy);

  cube = new ShapeCube();
  cube->setScale(0.1, 0.4, 0.075);
  cube->setTranslation(0.0, -0.4, 0.0);

  SkelNode* rupperlegz = new SkelNode("RUpperLegZ", cube);

  SkelArc* rhipz = new SkelArc("RHipZ", rupperlegz);
  rhipz->setRotationAxis(-1.0, 0.0, 0.0);
  rupperlegy->addArc(rhipz);

  // Create lower right leg
  cube = new ShapeCube();
  cube->setScale(0.1, 0.3, 0.075);
  cube->setTranslation(0.0, -0.3, 0.0);

  SkelNode* rlowerleg = new SkelNode("RLowerLeg", cube);
  
  SkelArc* rknee = new SkelArc("RKnee", rlowerleg);
  rknee->setTranslation(0.0, -0.8, 0.0);
  rknee->setRotationAxis(-1.0, 0.0, 0.0);
  rupperlegz->addArc(rknee);

  // Create right foot
  cube = new ShapeCube();
  cube->setScale(0.1, 0.05, 0.2);
  cube->setTranslation(0.0, -0.05, 0.125);

  SkelNode* rfoot = new SkelNode("RFoot", cube);

  SkelArc* rankle = new SkelArc("RAnkle", rfoot);
  rankle->setTranslation(0.0, -0.6, 0.0);
  rankle->setRotationAxis(-1.0, 0.0, 0.0);
  rlowerleg->addArc(rankle);

  // Create upper left leg
  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* lupperlegx = new SkelNode("LUpperLegX", cube);
  SkelArc* lhipx = new SkelArc("LHipX", lupperlegx);
  lhipx->setTranslation(0.15, -0.5, 0.0);
  lhipx->setRotationAxis(-1.0, 0.0, 0.0);
  torso->addArc(lhipx);

  cube = new ShapeCube();
  cube->setScale(0.0, 0.0, 0.0);
  SkelNode* lupperlegy = new SkelNode("LUpperLegY", cube);
  SkelArc* lhipy = new SkelArc("LHipY", lupperlegy);
  lhipy->setRotationAxis(0.0, -1.0, 0.0);
  lupperlegx->addArc(lhipy);


  cube = new ShapeCube();
  cube->setScale(0.1, 0.4, 0.075);
  cube->setTranslation(0.0, -0.4, 0.0);

  SkelNode* lupperlegz = new SkelNode("LUpperLegZ", cube);

  SkelArc* lhipz = new SkelArc("LHipZ", lupperlegz);
  lhipz->setRotationAxis(0.0, 0.0, -1.0);
  lupperlegy->addArc(lhipz);

  // Create lower left leg
  cube = new ShapeCube();
  cube->setScale(0.1, 0.3, 0.075);
  cube->setTranslation(0.0, -0.3, 0.0);

  SkelNode* llowerleg = new SkelNode("LLowerLeg", cube);
  
  SkelArc* lknee = new SkelArc("LKnee", llowerleg);
  lknee->setTranslation(0.0, -0.8, 0.0);
  lknee->setRotationAxis(-1.0, 0.0, 0.0);
  lupperlegz->addArc(lknee);

  // Create left foot
  cube = new ShapeCube();
  cube->setScale(0.1, 0.05, 0.2);
  cube->setTranslation(0.0, -0.05, 0.125);

  SkelNode* lfoot = new SkelNode("LFoot", cube);

  SkelArc* lankle = new SkelArc("LAnkle", lfoot);
  lankle->setTranslation(0.0, -0.6, 0.0);
  lankle->setRotationAxis(-1.0, 0.0, 0.0);
  llowerleg->addArc(lankle);
}
