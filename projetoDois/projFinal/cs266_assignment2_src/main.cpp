#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/timeb.h>
#include <time.h>
#include <GL/glut.h>

#include "shapecube.h"
#include "animation.h"
#include "humanskeleton.h"
#include "skeleton.h"
#include "fkframer.h"
#include "ikframer.h"

#define DEG_TO_RAD 0.0174532925

GLsizei wh = 600, ww = 600;         /* Initial window size, this is used when window is created and opened */

GLfloat z = -15.0f;
GLfloat xrot = 0.0f;
GLfloat yrot = 0.0f;
GLfloat xspeed = 0.0f;
GLfloat yspeed = 0.0f;

GLfloat shift = -3.5f;
GLfloat track = 0.0f;
double rate = 2.5;

bool reflection = true;
bool shadow = true;

GLfloat LightPosition[]= { 25.0f, 25.0f, 1.0f, 1.0f };

Animation animator;
ShapeCube ground;

HumanSkeleton hskel1, hskel2;
FKFramer framer;
IKFramer ikframer;
bool inverse = true;

/* Shadow and reflection routines from Mark J Kilgard's dinoshade sample program */
enum { X = 0, Y, Z, W };
enum { A = 0, B, C, D };

/* Create a matrix that will project the desired shadow. */
void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4])
{
  GLfloat dot;

  /* Find dot product between light position vector and ground plane normal. */
  dot = groundplane[X] * lightpos[X] +
        groundplane[Y] * lightpos[Y] +
        groundplane[Z] * lightpos[Z] +
        groundplane[W] * lightpos[W];

  shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
  shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
  shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
  shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

  shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
  shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
  shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
  shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

  shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
  shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
  shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
  shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

  shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
  shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
  shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
  shadowMat[3][3] = dot - lightpos[W] * groundplane[W];
}

/* Find the plane equation given 3 points. */
void findPlane(GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3])
{
  GLfloat vec0[3], vec1[3];

  /* Need 2 vectors to find cross product. */
  vec0[X] = v1[X] - v0[X];
  vec0[Y] = v1[Y] - v0[Y];
  vec0[Z] = v1[Z] - v0[Z];

  vec1[X] = v2[X] - v0[X];
  vec1[Y] = v2[Y] - v0[Y];
  vec1[Z] = v2[Z] - v0[Z];

  /* find cross product to get A, B, and C of plane equation */
  plane[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
  plane[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
  plane[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];

  plane[D] = -(plane[A] * v0[X] + plane[B] * v0[Y] + plane[C] * v0[Z]);
}

void reflect()
{
  /* Don't update color or depth. */
  glDisable(GL_DEPTH_TEST);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

  /* Draw 1 into the stencil buffer. */
  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
  glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

  /* Now render floor; floor pixels just get their stencil set to 1. */
  ShapeCube stencil;
  stencil.setScale(5.0, 0.0, 10.0);
  stencil.setTranslation(0.0, -1.5, 0.0);
  stencil.draw();

  /* Re-enable update of color and depth. */ 
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glEnable(GL_DEPTH_TEST);

  /* Now, only render where stencil is set to 1. */
  glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if ==1 */
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

  glPushMatrix();

  /* The critical reflection step: Reflect dinosaur through the floor
     (the Y=0 plane) to make a relection. */
  glTranslated(0.0, -3.0, 0.0);
  glScalef(1.0, -1.0, 1.0);

  /* Reflect the light position. */
  glPushMatrix();
  glLoadIdentity();
  glScalef(1.0, -1.0, 1.0);
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
  glPopMatrix();

  /* To avoid our normals getting reversed and hence botched lighting
     on the reflection, turn on normalize.  */
  glCullFace(GL_FRONT);


  glPushMatrix();
  glRotatef(track, 0.0f, 1.0f, 0.0f);
  glTranslatef(shift, 0.0f, 0.0f);
  glColor3f(1.0, 1.0, 0.0);
  Animation::actors_t::iterator iter = animator.begin();
  (*iter)->skeleton_->evaluate();
  glPopMatrix();

  if(inverse)
  {
    iter++;
     glColor3f(0.0, 1.0, 1.0);
    (*iter)->skeleton_->evaluate();
  }


  glCullFace(GL_BACK);

  glPopMatrix();

  /* Switch back to the unreflected light position. */
  glPushMatrix();
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
  glPopMatrix();

  glDisable(GL_STENCIL_TEST);
}

void shade()
{
  GLfloat floorPlane[4] = {0.0, 1.0, 0.0, 1.0};
  GLfloat floorShadow[4][4];

  GLfloat floorVertices[4][3] = 
  {
    { -5.0, -1.5, 10.0 },
    { 5.0, -1.5, 10.0 },
    { 5.0, -1.5, -10.0 },
    { -5.0, -1.5, -10.0 },
  };

  /* Setup floor plane for projected shadow calculations. */
  findPlane(floorPlane, floorVertices[1], floorVertices[2], floorVertices[3]);
  shadowMatrix(floorShadow, floorPlane, LightPosition);

  /* Don't update color or depth. */
  glDisable(GL_DEPTH_TEST);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

  /* Draw the floor with stencil value 3.  This helps us only 
     draw the shadow once per floor pixel (and only on the
     floor pixels). */
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 3, 0xffffffff);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  /* Now render floor; floor pixels just get their stencil set to 1. */
  ShapeCube stencil;
  stencil.setScale(5.0, 0.0, 10.0);
  stencil.setTranslation(0.0, -1.5, 0.0);
  stencil.draw();

  /* Re-enable update of color and depth. */ 
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glEnable(GL_DEPTH_TEST);

  /* Now, only render where stencil is set above 2 (ie, 3 where
      the top floor is).  Update stencil with 2 where the shadow
      gets drawn so we don't redraw (and accidently reblend) the
      shadow). */
  glStencilFunc(GL_LESS, 2, 0xffffffff);  /* draw if ==1 */
  glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

  /* To eliminate depth buffer artifacts, we use polygon offset
     to raise the depth of the projected shadow slightly so
     that it does not depth buffer alias with the floor. */
  glEnable(GL_POLYGON_OFFSET_FILL);

  /* Render 50% black shadow color on top of whatever the
     floor appareance is. */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_LIGHTING);  /* Force the 50% black. */
  glColor4f(0.0, 0.0, 0.0, 0.5);


  glPushMatrix();
  /* Project the shadow. */
  glMultMatrixf((GLfloat *) floorShadow);

  glPushMatrix();
  glRotatef(track, 0.0f, 1.0f, 0.0f);
  glTranslatef(shift, 0.0f, 0.0f);
  Animation::actors_t::iterator iter = animator.begin();
  (*iter)->skeleton_->evaluate();
  glPopMatrix();

  if(inverse)
  {
    iter++;
    (*iter)->skeleton_->evaluate();
  }

  glPopMatrix();


  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);

  glDisable(GL_POLYGON_OFFSET_FILL);
  glDisable(GL_STENCIL_TEST);
}

void mydisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

  glPushMatrix();

  glTranslatef(0.0, 0.0, z);
  glRotatef(xrot,1.0,0.0,0.0);
  glRotatef(yrot,0.0,1.0,0.0);

  if(reflection)
    reflect();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.0, 1.0, 1.0, 0.5);
  ground.draw();
  glDisable(GL_BLEND);

  if(shadow)
    shade();

  glPushMatrix();
  glRotatef(track, 0.0f, 1.0f, 0.0f);
  glTranslatef(shift, 0.0f, 0.0f);
  glColor3f(1.0, 1.0, 0.0);
  Animation::actors_t::iterator iter = animator.begin();
  (*iter)->skeleton_->evaluate();
  glPopMatrix();

  if(inverse)
  {
    glColor3f(0.0, 1.0, 1.0);
    iter++;
    (*iter)->skeleton_->evaluate();
  }

  glPopMatrix();

  glFlush();
  glutSwapBuffers();		        /* Swap draw and display buffers */
}

void animate()
{
  xrot += xspeed;
  if (xrot > 360.0)
    xrot -= 360.0;

  yrot += yspeed;
  if (yrot > 360.0)
    yrot -= 360.0;

  track += 0.125 * rate;
  if (track > 360.0)
    track -= 360.0;

  animator.update();

  glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
  glutPostRedisplay();
}

void key(unsigned char k, int xx, int yy)
{
  if (k=='q' || k=='Q') 
    exit (0);
  else if(k == '1')
  {
    z = -15.0f;
    xrot = 42.0f;
    yrot = 32.0f;
  }
  else if(k == '2')
  {
    z = -15.0f;
    xrot = 0.0f;
    yrot = 0.0f;
  }
  else if(k == '3')
  {
    z = -5.0f;
    xrot = 0.0f;
    yrot = 60.0f;
  }
  else if(k == 'z')
    z += 0.5f;
  else if(k == 'Z')
    z -= 0.5f;
  else if(k == 'x')
    xspeed += 0.05f;
  else if(k == 'X')
    xspeed -= 0.05f;
  else if(k == 'y')
    yspeed += 0.05f;
  else if(k == 'Y')
    yspeed -= 0.05f;
  else if(k == 'r')
  {
    rate += 0.125f;
    Animation::actors_t::iterator iter;
    for(iter = animator.begin(); iter != animator.end(); ++iter)
      (*iter)->framer_->setRate(rate);
  }
  else if(k == 'R')
  {
    rate -= 0.125f;
    Animation::actors_t::iterator iter;
    for(iter = animator.begin(); iter != animator.end(); ++iter)
      (*iter)->framer_->setRate(rate);
  }
  else if(k == 'a')
    reflection = !reflection;
  else if(k == 's')
    shadow = !shadow;
  else if(k == 'd')
    inverse = !inverse;
  else if(k == '6')
    ikframer.setGoal("RLeg", 0.0, -1.39, 0.139);
  else if(k == '7')
    ikframer.setGoal("RLeg", 0.0, -1.0, 0.0);
  else if(k == '8')
    ikframer.setGoal("RLeg", 0.0, -1.0, -0.35);
  else if(k == GLUT_KEY_UP || k == 'i')
    xrot += 0.25;
  else if(k == GLUT_KEY_DOWN || k == 'k')
    xrot -= 0.25;
  else if(k == GLUT_KEY_RIGHT || k == 'j')
    yrot += 0.25;
  else if(k == GLUT_KEY_LEFT || k == 'l')
    yrot -= 0.25;
}


/* rehaping routine called whenever window is resized or moved */
void myReshape(GLsizei w, GLsizei h)
{
  glViewport(0,0,w,h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* set global size for use by drawing routine */
  ww = w;
  wh = h;
}

void myinit(void)
{
  GLfloat LightAmbient[]= { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
  glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glPolygonOffset(-2.0, -1.0);
}

void print_usage()
{
  printf("Usage\n");
  printf("\tq\t\tQuit\n");
  printf("\t1\t\tSelect diagonal view\n");
  printf("\t2\t\tSelect initial view\n");
  printf("\t3\t\tSelect inverse kinematic skeleton view\n");
  printf("\tz/Z\t\tZoom in/out\n");
  printf("\tx/X\t\tIncrease/decrease x-axis rotation velocity\n");
  printf("\ty/Y\t\tIncrease/decrease y-axis rotation velocity\n");
  printf("\tr/R\t\tIncrease/decrease forward kinematic animation speed\n");
  printf("\ta\t\tToggle reflection\n");
  printf("\ta\t\tToggle shadows\n");
  printf("\td\t\tToggle inverse kinematic skeleton\n");
  printf("\t6\t\tSet IK goal to initial position\n");
  printf("\t7\t\tSet IK goal to forward position\n");
  printf("\t8\t\tSet IK goal to rear position\n");
  printf("\ti\t\tRotate view around positive x-axis\n");
  printf("\tk\t\tRotate view around negative x-axis\n");
  printf("\tj\t\tRotate view around positive y-axis\n");
  printf("\tl\t\tRotate view around negative y-axis\n");
}

int main(int argc, char** argv)
{
  print_usage();

  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL | GLUT_DEPTH);
  glutInitWindowSize(ww,wh);
  glutCreateWindow("Assignment 2");

  myinit();

  framer.setRate(rate);
  animator.addActor(&hskel1, &framer);

  ikframer.addChain("RLeg", &hskel2, "RHipX", "RAnkle");
  ikframer.setGoal("RLeg", 0.0, -1.39, 0.139);

  animator.addActor(&hskel2, &ikframer);

  ground.setScale(5.0, 0.1, 10.0);
  ground.setTranslation(0.0, -1.5 + -0.1, 0.0);

  glutReshapeFunc (myReshape);
  glutDisplayFunc(mydisplay);
  glutIdleFunc(animate);
  glutKeyboardFunc(key);
  glutMouseFunc (mouse);
  glutMainLoop();
  return 0;
}
