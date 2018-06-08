#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <GL\glaux.h>
//#include "utilTextura.cpp"


/////////   VARI�VEIS GLOBAIS PARA OS ANGULOS////////////
float ang = 0;
float ang2 = 0;
float ang3 = 0;


void display();

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
////////////////////////////////////////////////////////////
class Dedo
{
public:
    Dedo(float comprimento, float largura);
    void desenha() {a.desenha();}
    void setCurvatura(float curvatura);
    float getCurvatura() {return a.getAngulo()*100/90;}

protected:
    Osso a,b,c;
};

Dedo::Dedo(float comprimento, float largura)
  : a(comprimento*0.4,largura), b(comprimento*0.35,largura), c(comprimento*0.25,largura)
{
    a.setConexcao(&b,0.0);
    b.setConexcao(&c,0.0);
}

void Dedo::setCurvatura(float curvatura)
{
    a.setAngulo(curvatura*0.9);
    b.setAngulo(curvatura*0.9);
}
////////////////////////////////////////////////////////////
class Dedao
{
public:
    Dedao(float comprimento, float largura);
    void desenha() {a.desenha();}
    void setCurvatura(float curvatura);
    float getCurvatura() {return a.getAngulo()*100/90;}

protected:
    Osso a,b;
};

Dedao::Dedao(float comprimento, float largura)
  : a(comprimento*0.5,largura), b(comprimento*0.5,largura)
{
    a.setConexcao(&b,0.0);
}

void Dedao::setCurvatura(float curvatura)
{
    a.setAngulo(curvatura*0.9);
}
////////////////////////////////////////////////////

class Mao
{
public:
    Mao(float grossura);
    void desenha();
    void setCurvatura(int dedo,float curv);
    float getCurvatura(int dedo) {return curvatura[dedo];}
    void abrir(bool tudoJunto = false);
    void fechar(bool tudoJunto = false);
    void tchau();
    void fuck();
    void hangloose();
    void dedoDuro();
    void positivo();
    void vemProPau();
    void home();
protected:
    float grossura;

    Dedo mindinho;
    Dedo anelar;
    Dedo maior;
    Dedo indicador;
    Dedao dedao;
    float curvatura[5];
};

Mao::Mao(float gros)
  : grossura(gros),
    mindinho(4*grossura,grossura),
    anelar(6*grossura,grossura),
    maior(7*grossura,grossura),
    indicador(6*grossura,grossura),
    dedao(4*grossura,grossura)
{
    for (int i=0;i<5;i++)
        curvatura[i] = 0;
}

void Mao::desenha()
{
    glPushMatrix();
      glTranslatef(0.0,6.0*grossura,0.0);
      glPushMatrix();
        glTranslatef(-3*grossura,0.0,0.0);
        glutSolidSphere(grossura,8,8);
        glRotatef(curvatura[0]*0.9,1.0,0.0,0.0);
        mindinho.desenha();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-1.5*grossura,0.0,0.0);
        glutSolidSphere(grossura,8,8);
        glRotatef(curvatura[1]*0.9,1.0,0.0,0.0);
        anelar.desenha();
      glPopMatrix();
      glPushMatrix();
        glutSolidSphere(grossura,8,8);
        glRotatef(curvatura[2]*0.9,1.0,0.0,0.0);
        maior.desenha();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(1.5*grossura,0.0,0.0);
        glutSolidSphere(grossura,8,8);
        glRotatef(curvatura[3]*0.9,1.0,0.0,0.0);
        indicador.desenha();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(2*grossura,-4*grossura,0.0);
        glRotatef(-80,0.0,0.0,1.0);
        glRotatef(-20,0.0,1.0,0.0);
        glRotatef(curvatura[4]*0.5,1.0,0.0,0.0);
        glScalef(1.5,1,1);
        glutSolidSphere(grossura,8,8);
        dedao.desenha();
      glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.75*grossura,3.0*grossura,0.0);
        glScalef(5.5*grossura,6.0*grossura,1.25*grossura);
        glutSolidCube(1.0);
    glPopMatrix();
}

void Mao::setCurvatura(int dedo,float curv)
{
    curvatura[dedo] = curv;

    switch(dedo)
    {
        case 0: mindinho.setCurvatura(curv); break;
        case 1: anelar.setCurvatura(curv); break;
        case 2: maior.setCurvatura(curv); break;
        case 3: indicador.setCurvatura(curv); break;
        case 4: dedao.setCurvatura(curv); break;
    }
}

void Mao::abrir(bool tudoJunto)
{
    if (tudoJunto)
        for (int j=getCurvatura(1);j>=0;j-=5)
        {
            for (int i=4;i>=0;i--)
            {
                setCurvatura(i,j);

            }
            display();
        }
    else
        for (int i=4;i>=0;i--)
        {
            for (int j=getCurvatura(i);j>=0;j-=5)
            {
                setCurvatura(i,j);
                display();
            }
        }

}

void Mao::fechar(bool tudoJunto)
{
    if (tudoJunto)
    for (int j=getCurvatura(1);j<=100;j+=5)
    {
        for (int i=0;i<5;i++)
        {
            setCurvatura(i,j);
        }
        display();
    }
    else
    for (int i=0;i<5;i++)
    {
        for (int j=getCurvatura(i);j<=100;j+=5)
        {
            setCurvatura(i,j);
            display();
        }
    }
}

void Mao::tchau()
{
    abrir(true);
    for(int j = 0 ;j < 3 ; j++)
    {
        ang3 += 5;
        display();
    }
    for(int i = 0; i< 3; i++)
    {
        for(int j = 0 ;j < 6 ; j++)
        {
            ang3 -= 5;
            display();
        }
        for(int j = 0 ;j < 6 ; j++)
        {
            ang3 += 5;
            display();
        }
    }
    for(int j = 0 ;j < 3 ; j++)
    {
        ang3 -= 5;
        display();
    }
}

void Mao::fuck()
{
    for(int i = 0 ; i < 180; i+=20)
    {
        ang += 20;
        display();
    }

    fechar(true);
    for (int j=getCurvatura(2);j>=0;j-=20)
    {
        setCurvatura(2,j);
        display();
    }
}

void Mao::hangloose()
{
    fechar(true);
    for (int j=getCurvatura(2);j>=0;j-=20)
    {
        setCurvatura(0,j);
        setCurvatura(4,j);
        ang3 += 3;
        display();
    }
    for(int j = 0 ;j < 3 ; j++)
    {
        ang += 5;
        display();
    }
    for(int i = 0; i< 3; i++)
    {
        for(int j = 0 ;j < 6 ; j++)
        {
            ang -= 5;
            display();
        }
        for(int j = 0 ;j < 6 ; j++)
        {
            ang += 5;
            display();
        }
    }
    for(int j = 0 ;j < 3 ; j++)
    {
        ang -= 5;
        display();
    }
    for(int j = 0 ;j < 6 ; j++)
    {
        ang3 -= 3;
        display();
    }
}
void Mao::vemProPau()
{
    abrir(true);
    for(int i = 0 ; i < 180; i+=20)
    {
        ang += 20;
        ang2 -=10;
        display();
    }
    for (int j=getCurvatura(1);j<=30;j+=10)
    {
        for (int i=0;i<4;i++)
        {
            setCurvatura(i,j);
        }
        display();
    }
    for (int j=30;j>=0;j-=10)
    {
        for (int i=0;i<4;i++)
        {
            setCurvatura(i,j);
        }
        display();
    }
//////////////
    for (int j=getCurvatura(1);j<=30;j+=10)
    {
        for (int i=0;i<4;i++)
        {
            setCurvatura(i,j);
        }
        display();
    }
    for (int j=30;j>=0;j-=10)
    {
        for (int i=0;i<4;i++)
        {
            setCurvatura(i,j);
        }
        display();
    }


}

void Mao::home()
{
    abrir(true);

    if (ang < 0)
        ang += 360;
    if (ang2< 0)
        ang2+= 360;
    if (ang3< 0)
        ang3+= 360;


    while (ang > 0)
    {
        ang-= 10;
        display();
    }
    ang = 0;
    while (ang2 > 0)
    {
        ang2-= 10;
        display();
    }
    ang2 = 0;
    while (ang3 > 0)
    {
        ang3-= 10;
        display();
    }
    ang3 = 0;
    display();

}

void Mao::dedoDuro()
{
}

void Mao::positivo()
{
}


/////////////////////////////////////////////////////////////
Mao m(1.0);

///////////////////////////////////////////////////
void init(void)
{
    //LoadGLTextures();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glBindTexture(GL_TEXTURE_2D, texture[0]);
   //////////////ISSO AQUI EH PRA LUZ///////////E EU AINDA N SEI COMO FUNCA/////
    GLfloat			diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0};
    GLfloat			ambientLight[] = { 0.2f, 0.2f, 0.4f, 1.0};
    GLfloat			lightPos[] = { 0.0f, 500.0f, 100.0f, 1.0f };
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f,1.0f,1.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, diffuseLight );
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    //////////////////////////////////////////////////////////////////////////

    glPushMatrix();

      glTranslatef (0.0, -5.0, -15.0);
      glRotatef (ang3, 0.0, 0.0, 1.0);
      glRotatef (ang, 0.0, 1.0, 0.0);
      glRotatef (ang2, 1.0, 0.0, 0.0);
      glColor3f(1.0,0.8,0);

      m.desenha();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(55.0, (GLfloat) w/(GLfloat) h, 1.0, 40.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -10.0);
}


void idle()
{
}

void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'q':
            if (m.getCurvatura(0) < 100)
                m.setCurvatura(0,m.getCurvatura(0)+5);
            break;
        case 'a':
            if (m.getCurvatura(0) > 0)
                m.setCurvatura(0,m.getCurvatura(0)-5);
            break;
        case 'w':
            if (m.getCurvatura(1) < 100)
                m.setCurvatura(1,m.getCurvatura(1)+5);
            break;
        case 's':
            if (m.getCurvatura(1) > 0)
                m.setCurvatura(1,m.getCurvatura(1)-5);
            break;
         case 'e':
            if (m.getCurvatura(2) < 100)
                m.setCurvatura(2,m.getCurvatura(2)+5);
            break;
        case 'd':
            if (m.getCurvatura(2) > 0)
                m.setCurvatura(2,m.getCurvatura(2)-5);
            break;
        case 'r':
            if (m.getCurvatura(3) < 100)
                m.setCurvatura(3,m.getCurvatura(3)+5);
            break;
        case 'f':
            if (m.getCurvatura(3) > 0)
                m.setCurvatura(3,m.getCurvatura(3)-5);
            break;
        case 't':
            if (m.getCurvatura(4) < 100)
                m.setCurvatura(4,m.getCurvatura(4)+5);
            break;
        case 'g':
            if (m.getCurvatura(4) > 0)
                m.setCurvatura(4,m.getCurvatura(4)-5);
            break;
        case '.': //>
            ang += 5;
            if (ang>360)
                ang -= 360;
            break;
        case ',': //<
            ang -= 5;
            if (ang<0)
                ang += 360;
            break;
        case ']':
            ang2 += 5;
            if (ang2>360)
                ang2 -= 360;
            break;
        case '[':
            ang2 -= 5;
            if (ang2<0)
                ang2 += 360;
            break;
        case '+':
            m.abrir();
            break;
        case '*' :
            m.abrir(true);
            break;
        case '/' :
            m.fechar(true);
            break;
        case '-':
            m.fechar();
            break;
        case 27: //ESC
            exit(0);
            break;
        case '9':
            ang3 += 5;
            if (ang3>360)
                ang3 -= 360;
            break;
        case '0':
            ang3 -= 5;
            if (ang3<0)
                ang3 += 360;
            break;
        case '1' :
            m.tchau();
            break;
        case '2' :
            m.fuck();
            break;
        case '3' :
            m.hangloose();
            break;
        case '4' :
            m.vemProPau();
            break;
        case 8 :
            m.home();
            break;

        default:
            return;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (300, 300);
    glutInitWindowPosition (200, 200);
    glutCreateWindow (argv[0]);
    init ();

    printf("FullScreen?(y/n) ");
    if (getchar() == 'y')
        glutFullScreen();

    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}