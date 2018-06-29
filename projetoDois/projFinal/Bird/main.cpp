#include <math.h>
#include "Body.cpp"
#define PASSO_TEMPO 50

Body body(1.0);
float obsteta = 0.79, obsfi = 1.5, distancia = 50.0;
int tam = 0;

void init(void)
{
    //LoadGLTextures();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
}

void Piso(void)
{
    int i, j, c = 100;

    for(i = -20; i <= 20; i++)
    {
        for(j = -20; j <= 20; j++)
        {
            if((i + j) % 2 == 0) glColor3f(0.0, 1.0, 0.0);
            else glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f(i * c, j * c, 0.0);
                glVertex3f(i * c + c, j * c, 0.0);
                glVertex3f(i * c + c, j * c + c, 0.0);
                glVertex3f(i * c, j * c + c, 0.0);
            glEnd();
        }
    }
}

void display(void)
{
    GLfloat posicao_luz[] = {500.0, 500.0, 500.0, 1.0}; // Posição Luz
    double obsx, obsy, obsz;
    static float Posicaox = 0.0;  //  Posicao do Robô
    static double passo = 0.0;

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

    glTranslatef(0,0,10);

    glPushMatrix();
      glColor3f(1.0,1.0,1.0);
      body.Draw();
      //body.Draw();
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

void MovimentaTeclado(unsigned char tecla, int x, int y)
{}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 50);
    glutCreateWindow (argv[0]);
    //init();
    //printf("FullScreen?(y/n) ");
    //if (getchar() == 'y')
        //glutFullScreen();

    //glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(Ajustedimensao);
    glutMotionFunc(MoveMouse);
    Iluminacao();
    Timer(1);
    glutKeyboardFunc(MovimentaTeclado);
    glutMainLoop();
	return 0;
}
