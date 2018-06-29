#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Foot
{
protected:
	float size;
public:
	Foot(float size);
	void Draw(int lado);
};

Foot::Foot(float size):size(size*0.5){}

void Foot::Draw(int lado)
{
	glPushMatrix();
		if(lado == -1){
			glTranslatef(0.0,-size,0.0);
			glutSolidSphere(0.5*size, 50,50);
			
			glTranslatef(0.3,-size,-size);
			glRotatef(-45, 0, 1, 0);	
		}else{
			glTranslatef(0.0,-size,0.0);
			glutSolidSphere(0.5*size, 50,50);
			glTranslatef(0.3*size,-size,size);
			glRotatef(-135, 0, 1, 0);
		}
		glPushMatrix();
		
			glPushMatrix();
				glRotatef(-30, 1, 0, 0);
				glScalef(0.5, 0.5, 2);
				glutSolidCube(size);
			glPopMatrix();

			glTranslatef(0.0,-size,-size);
			glutSolidSphere(0.5*size, 50,50);

		glPopMatrix();
	glPopMatrix();
};