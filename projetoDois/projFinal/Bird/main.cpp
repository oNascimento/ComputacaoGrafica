#include <math.h>
#include <unistd.h>
#include "SOIL/SOIL.h"
#include "Body.cpp"

#define GRAU_RAD 0.017453292519943 
#define PASSO_TEMPO 50

Body body(1.0);
float obsteta = 0.79, obsfi = 1.5, distancia = 50.0;
int tam = 0;
float Posicaox = 0.0; 
double passo = 0.0;
GLuint texture[1];


int LoadGLTextures()
{
    
    texture[0] = SOIL_load_OGL_texture("Images/Grama.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);

    if (texture[0] == 0){
        //printf("oi");
        return false;
    }
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return true;
}


void Piso(void)
{
    int i, j, c = 100;

    for(i = -20; i <= 20; i++)
    {
        for(j = -20; j <= 20; j++)
        {
             glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[0]);
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glTexCoord2f(0,0);glVertex3f(i * c, j * c, 0.0);
                glTexCoord2f(1,0);glVertex3f(i * c + c, j * c, 0.0);
                glTexCoord2f(1,1);glVertex3f(i * c + c, j * c + c, 0.0);
                glTexCoord2f(0,1);glVertex3f(i * c, j * c + c, 0.0);
            glEnd();
            glDisable(GL_TEXTURE_2D);

        }
    }
}

void display(void)
{
    GLfloat posicao_luz[] = {500.0, 500.0, 500.0, 1.0}; // Posição Luz
    double obsx, obsy, obsz;

    // Calcula a distância do observador
    obsx = Posicaox + distancia * sin(obsfi) * cos(obsteta);
    obsy = distancia * sin(obsfi) * sin(obsteta);
    obsz = distancia * cos(obsfi);

    // Posiciona a Câmera
    glLoadIdentity();
    gluLookAt(obsx, obsy, obsz, Posicaox, 0.0, 0.0, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Habilita a luz
    glLightfv (GL_LIGHT0, GL_POSITION, posicao_luz);
    glEnable(GL_LIGHTING);

    Piso();

    glTranslatef(Posicaox, 0.0, 5.0); 

    glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        body.Draw();
    glPopMatrix();
    
    glutSwapBuffers();
}

void Iluminacao(void)
{
    GLfloat ambiente[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat difusa[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat especular[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, especular);

    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void Ajustedimensao(GLsizei w, GLsizei h)
{
    // Não deixa a largura da janela ser menor que 700
    if(w < 700) glutReshapeWindow(700, h);

    // Não deixa a altura da janela ser menor que 700
    if(h < 500) glutReshapeWindow(w, 500);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(24.0f, (GLfloat)w / (GLfloat)h, 0.5f, 10000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void MoveMouse(int x, int y)
{
    float passo = 0.04;
    float r = 0.0f, q = 0.0f;
    static int Xo = 0, Yo = 0;

    if(x > Xo) r = -passo;
    if(x < Xo) r = passo;
    if(y > Yo && obsfi > 0.02) q = -passo;
    if(y < Yo && obsfi < 3.13) q = passo;

    obsteta += r;
    obsfi += q;

    Xo = x;
    Yo = y;
}

void Timer(int w)
{
    glutPostRedisplay();
    //Movimento(acao);
    glutTimerFunc(PASSO_TEMPO,Timer,1);
}

void MovFly(){
    float Mov[8] = {0.5,1,0.5,0,-0.5,-1,-0.5,0};
    
    for(int i = 0; i < 5; i++){
        
        for (int j = 0; j < 8; j++)
        {
            Posicaox += fabs(3.0 * sin((70 + passo) * GRAU_RAD));  //  Calcula a posição do Passaro
            passo = fmod(passo + 0.5, 360.0);
            body.Voar(Mov[j]);
            sleep(0.1);
            display();
        }
    }
}

void Stop(){
    float MovY[5] = {0, 0.1, 0.2, 0.3, 0.35};

    for (int j = 0; j < 5; j++)
    {
        body.BodyDown(MovY[j],MovY[j]);
        body.FecharAsa();
        display();
    }
    sleep(3);
    for (int j = 5; j > 0; j--)
    {
        body.BodyDown(MovY[j],MovY[j]);
        body.AbrirAsa();
        display();
    }
}



void MovimentaTeclado(unsigned char tecla, int x, int y)
{
    switch(tecla){
        case 'a':
            MovFly();
            break;
        case 's':
            Stop();
            break;
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 50);
    glutCreateWindow ("Passarinho Que Som e Esse");

    if(!LoadGLTextures()){
        return 0;
    }

    glutDisplayFunc(display);
    glutReshapeFunc(Ajustedimensao);
    glutMotionFunc(MoveMouse);
    Iluminacao();
    Timer(1);
    glutKeyboardFunc(MovimentaTeclado);
    glutMainLoop();
	return 0;
}
