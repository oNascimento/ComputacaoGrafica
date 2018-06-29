#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Pecker
{
protected:
	float size;
	float angZ;
public:
	Pecker(float size);
	void Draw();
	void BicoCima();
	void BicoBaixo();
};

Pecker::Pecker(float size)
	:size(size),angZ(30){}

void Pecker::BicoCima(){
	// Pecker Cima
		glBegin(GL_TRIANGLES);
			//Face Direita
			glVertex3f( 0.0, 0.2, 0.0);
			glVertex3f(-0.2, 0.0, 0.2);
			glVertex3f(0.0, 0.0, 0.2);
			
			//Face Esquerda
			glVertex3f( 0.0, 0.2, 0.0);
			glVertex3f(-0.2, 0.0, 0.2);
			glVertex3f(0.0, 0.0, -0.2);

			//Face Abaixo
			glVertex3f(0.0, 0.0, 0.2);
			glVertex3f(-0.2, 0.0, 0.2);
			glVertex3f(0.0, 0.0, -0.2);
		glEnd();
}

void Pecker::BicoBaixo(){
	// Pecker Baixo
		glBegin(GL_TRIANGLES);
			//Face Direita
			glColor3f(0.0,0.0,1.0);
			glVertex3f( 0.0, -0.2, 0.0);
			glVertex3f(-0.2, 0.0, 0.2);
			glVertex3f(0.0, 0.0, 0.2);
			
			//Face Esquerda
			glColor3f(0,1.0,0);
			glVertex3f( 0.0, -0.2, 0.0);
			glVertex3f(-0.2, 0.0, 0.2);
			glVertex3f(0.0, 0.0, -0.2);

			//Face Abaixo
			glVertex3f(0.0, 0.0, 0.2);
			glVertex3f(-0.2, 0.0, 0.2);
			glVertex3f(0.0, 0.0, -0.2);
		glEnd();
}

void Pecker::Draw(){
		//BicoCima();
		//BicoBaixo();
}