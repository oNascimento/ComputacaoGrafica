#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "Head.cpp"
#include "Wing.cpp"
#include "Tail.cpp"
#include "Foot.cpp"

class Body
{
protected:
	float size;
	Head head;
	Wing wingL,wingR;
	Tail tail;
	Foot foot;
	
public:
	Body(float pSize);
	void Draw();
};

Body::Body(float pSize): size(pSize), head(pSize), wingL(pSize), wingR(pSize),tail(pSize), foot(pSize){}

void Body::Draw(){
	glPushMatrix();
		glScalef(1.5*size,1,1);
		glutSolidSphere(size,50,50);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1*size,0.0,-0.3);
		glRotatef(90,1,0,0);
		foot.Draw(-1);
	glPushMatrix();
		glTranslatef(-2*size,0.0,0.0);
		tail.Draw();
	glPopMatrix();
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(0.0,0.5*size,0.0);
		wingL.Draw(1);
		glTranslatef(0.0,-size,0.0);
		wingR.Draw(-1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2*size,0.0,0.0);
		head.Draw();
	glPopMatrix();
};