#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

int matrixBumblebee[5][5] = {
	{180, 120, 120, 90, 60, 0};
	{180, 100, 50, 0, 0, 0};
	{180, 180, 120, 60, 0, 0};
	{180, 180, 120, 60, 0, 0};
	
}

float ang = 90;
float ang2 = 90;
float ang3 = 90;

class Osso
{
public:
    Osso(float a, float l): largura(l), altura(a), conexcao(0) {}
    void desenha();

    void setConexcao(Osso *osso, float ang) {conexcao = osso, angulo = ang;}

    void setAngulo(float ang){angulo = ang;}
    float getAngulo(){return angulo;}

protected:
    float largura;
    float altura;

    float angulo;
    Osso *conexcao;
};

void Osso::desenha()
{
    glPushMatrix();  //salva o contexto(1)

      glTranslatef (0.0, altura/2.0, 0.0); //vai para o meio do osso

      glPushMatrix();   //salva o contexto(2)
        glScalef (largura, altura, largura);  //escala para o tamanho do osso

        glutSolidCube (largura);    //desenha o osso
      glPopMatrix();    //restaura o contexto(2)

      glTranslatef (0.0, altura/2.0, 0.0); // vai para a ponta do osso

      glutSolidSphere(0.85*largura,8,8);        //desenha a bolinha

      if (conexcao)
      {
          glRotatef(angulo, 1.0, 0.0, 0.0); //rotaciona para o angulo da conexcao
          conexcao->desenha();              //desenha recursivamente
      }

    glPopMatrix();  //restaura o contexto(1)
};

class Braco{
protected:
	Osso a,b,c;

public:
	Braco(float comprimento, float largura);
    void desenha() {a.desenha();}
    //void setCurvatura(float curvatura);
    //void setCurvaturaMedio(float curvatura);
    //void setCurvaturaMenor(float curvatura);
    //float getCurvatura() {return a.getAngulo()*100/90;}
};

Braco::Braco(float comprimento, float largura)
  : a(comprimento*0.45,largura), b(comprimento*0.35,largura), c(comprimento*0.2,largura)
{
    a.setConexcao(&b,0.0);
    b.setConexcao(&c,0.0);
}

class Corpo{
protected:
	Braco bracos[2];
	float grossura;
	float curvatura[5];

public:
	Corpo(float grossura);
	void desenha();
}