#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Wing
{
protected:
	float size;
public:
	Wing(float size);
	void Draw(int lado);
};

Wing::Wing(float size):size(size){};

void Wing::Draw(int lado)
{
	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.8);
		glVertex3f(0.1, 0.0, 0.8);
		
		glVertex3f(0.1, 1.0*lado, 1.0);
		glVertex3f(0.0, 1.0*lado, 1.0);

		glVertex3f(0.0, 1.0*lado, -0.8);
		glVertex3f(0.1, 1.0*lado, -0.8);
		
	glEnd();
	
	glPushMatrix();
		glTranslatef(0.0, 1.0*lado, 1.0);
		glutSolidSphere(0.1,50,50);
	glPopMatrix();

	glBegin(GL_POLYGON);
		glVertex3f(0.1, 1.0*lado, 1.0);
		glVertex3f(0.0, 1.0*lado, 1.0);

		glVertex3f(0.1, 1.5*lado, 1.0);
		glVertex3f(0.0, 1.5*lado, 1.0);

		glVertex3f(0.0, 2.5*lado, -1.0);
		glVertex3f(0.1, 2.5*lado, -1.0);

		glVertex3f(0.0, 1.0*lado, -0.8);
		glVertex3f(0.1, 1.0*lado, -0.8);
		
	glEnd();
	
	glPushMatrix();
		glTranslatef(0.0, 1.5*lado, 1.0);
		glutSolidSphere(0.1,50,50);
	glPopMatrix();

	glBegin(GL_POLYGON);
		glVertex3f(0.1, 1.5*lado, 1.0);
		glVertex3f(0.0, 1.5*lado, 1.0);

		glVertex3f(0.1, 2.5*lado, 1.0);
		glVertex3f(0.0, 2.5*lado, 1.0);

		glVertex3f(0.1, 2.75*lado, 0.9);
		glVertex3f(0.0, 2.75*lado, 0.9);

		glVertex3f(0.1, 3.7*lado, -1.5);
		glVertex3f(0.0, 3.7*lado, -1.5);

		glVertex3f(0.0, 2.5*lado, -1.0);
		glVertex3f(0.1, 2.5*lado, -1.0);
	glEnd();
};