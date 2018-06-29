#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Tail
{
protected:
	float size;
public:
	Tail(float size);
	void Draw();
};

Tail::Tail(float size):size(size){}

void Tail::Draw(){
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.5, 0.1, 0.1);

		glVertex3f(-3.0, 0.0, 0.1);
		glVertex3f(-3.0, 0.1, 0.0);

		glVertex3f(-3.0, 0.6, 0.0);
		glVertex3f(-3.0, 0.7, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.0, 0.1);
		glVertex3f(0.5, -0.1, 0.0);

		glVertex3f(-3.0, 0.0, 0.0);
		glVertex3f(-3.0, -0.1, 0.1);

		glVertex3f(-3.0, -0.6, 0.1);
		glVertex3f(-3.0, -0.7, 0.0);
	glEnd();
}
