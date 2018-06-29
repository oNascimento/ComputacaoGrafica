#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "Pecker.cpp"

class Head
{
public:
	Head(float size);
	void Draw();
	
protected:
	Pecker b;
	float size;
};

Head::Head(float size)
: size(size), b(size/2)
{}

void Head::Draw()
{
	glRotatef(-90,0.0,0.0,1.0);
	glPushMatrix();
		//Cabeca
		glutSolidSphere(0.75*size,50,50);
	glPopMatrix();
};