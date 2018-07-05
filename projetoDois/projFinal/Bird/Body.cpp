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
	float ang,angY;
	Head head;
	Wing wingL,wingR;
	Tail tail;
	Foot foot;
	
public:
	Body(float pSize);
	void Draw();
	void Voar(float ang);
	void BodyDown(float ang, float angY);
	void FecharAsa();
	void AbrirAsa();
};

Body::Body(float pSize): size(pSize), head(pSize), wingL(pSize), wingR(pSize),tail(pSize), foot(pSize){}

void Body::Draw(){
	glPushMatrix();
		glTranslatef(0,0,angY*(-10));
		glRotatef(-ang*45,0,1,0);
		glPushMatrix();
			glTranslatef(2*size,0.0,0.0);
			head.Draw();
		glPopMatrix();
		glPushMatrix();
			//PEEEEEEEEEEEEEEEEEE
			glTranslatef(-1*size,0.4,-0.2);
			glRotatef(90,1,0,0);
			foot.Draw(-1);
			glTranslatef(0.0,0.0,0.8);
			foot.Draw(1);
			//FIM PEEEEEEEEEEEEEEEEEEEEEEE
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2*size,0.0,0.0);
			glRotatef(ang*45,0,1,0);
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
		glScalef(1.5*size,1,1);
			glutSolidSphere(size,50,50);
		glPopMatrix();
	glPopMatrix();
};

void Body::Voar(float ang){
	//Aqui Delegar para as asas baterem
	wingL.Bater(ang);
	wingR.Bater(ang);
	tail.OnFly(ang);	
}

void Body::BodyDown(float ang, float angY){
	this->ang = ang;
	this->angY = angY;
}

void Body::FecharAsa(){
	//Aqui delegar para a asa Fechar
	wingR.Fechar();
	wingL.Fechar();
}

void Body::AbrirAsa(){
	//Aqui delegar para a asa Fechar
	wingR.Abrir();
	wingL.Abrir();
}