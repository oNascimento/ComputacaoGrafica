#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Wing
{
protected:
	float size;
	float MovA;
	float MovB;
public:
	Wing(float size);
	void Draw(int lado);
	void Bater(float ang);
	void Fechar();
	void Abrir();
};

Wing::Wing(float size):size(size), MovA(0), MovB(0){};

void Wing::Draw(int lado)
{
	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.8);
		glVertex3f(0.1, 0.0, 0.8);
		
		glVertex3f(0.1 + MovA, 1.0*lado + MovB, 1.0);
		glVertex3f(0.0 + MovA, 1.0*lado + MovB, 1.0);

		glVertex3f(0.0 + MovA, 1.0*lado + MovB, -0.8);
		glVertex3f(0.1 + MovA, 1.0*lado + MovB, -0.8);
		
	glEnd();
	
	glPushMatrix();
		glTranslatef(0.0 + MovA, 1.0*lado + MovB, 1.0);
		glutSolidSphere(0.1,50,50);
	glPopMatrix();

	glBegin(GL_POLYGON);
		glVertex3f(0.1 + MovA, 1.0*lado + MovB, 1.0);
		glVertex3f(0.0 + MovA, 1.0*lado + MovB, 1.0);

		glVertex3f(0.1 + MovA*2, 1.5*lado + MovB, 1.0);
		glVertex3f(0.0 + MovA*2, 1.5*lado + MovB, 1.0);

		glVertex3f(0.0 + MovA*2, 2.5*lado + MovB, -1.0);
		glVertex3f(0.1 + MovA*2, 2.5*lado + MovB, -1.0);

		glVertex3f(0.0 + MovA, 1.0*lado + MovB, -0.8);
		glVertex3f(0.1 + MovA, 1.0*lado + MovB, -0.8);
		
	glEnd();
	
	glPushMatrix();
		glTranslatef(0.0 + MovA*2, 1.5*lado + MovB, 1.0);
		glutSolidSphere(0.1,50,50);
	glPopMatrix();

	glBegin(GL_POLYGON);
		glVertex3f(0.1 + MovA*2, 1.5*lado + MovB, 1.0);
		glVertex3f(0.0 + MovA*2, 1.5*lado + MovB, 1.0);

		glVertex3f(0.1 + MovA, 2.5*lado + MovB, 1.0);
		glVertex3f(0.0 + MovA, 2.5*lado + MovB, 1.0);

		glVertex3f(0.1 + MovA, 2.75*lado + MovB, 0.9);
		glVertex3f(0.0 + MovA, 2.75*lado + MovB, 0.9);

		glVertex3f(0.1 + MovA, 3.7*lado + MovB, -1.5);
		glVertex3f(0.0 + MovA, 3.7*lado + MovB, -1.5);

		glVertex3f(0.0 + MovA*2, 2.5*lado + MovB, -1.0);
		glVertex3f(0.1 + MovA*2, 2.5*lado + MovB, -1.0);
	glEnd();
};

void Wing::Bater(float ang){
	this->MovA = ang;
}

void Wing::Fechar(){
	this->MovA -= 0.2;
	this->MovB -= 0.1;
}

void Wing::Abrir(){
	this->MovA += 0.2;
	this->MovB += 0.1;
}