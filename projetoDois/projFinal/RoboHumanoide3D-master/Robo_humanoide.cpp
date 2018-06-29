#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PASSO_TEMPO 50  // Passo do tempo
#define GRAU_RAD 0.017453292519943   //  Define a constante de conversão de Graus para Radianos

// Enumera as ações do robô
enum ACAO {PARAR, ANDAR} acao = PARAR;

//  Angulos de visualização do observador
float obsteta = 0.79, obsfi = 1.5, distancia = 800.0;
// Ângulo do tronco
float TR = 0;
// Ângulos do ombro, cotovelo, mão, pé, perna, perna1, joelho, tornozelo esquerdo
float OE = 0.0, CE = 0.0, ME = 0.0, PE = 0.0, PE1 = 0.0, JE = 0.0, TE = 0.0;
// Ângulos do ombro, cotovelo, mão, pé, perna, perna1, joelho, tornozelo direito
float OD = 0.0, CD = 0.0, MD = 0.0, PD = 0.0, PD1 = 0.0, JD = 0.0, TD = 0.0;


// Cria Paralelepípedos
void Paralelo(float comp, float lar, float alt)
{
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(lar, 0.0, 0.0);
        glVertex3f(lar, comp, 0.0); glVertex3f(0.0, comp, 0.0);
        glNormal3f(0,0,1);
        glVertex3f(0.0, 0.0, alt);  glVertex3f(lar, 0.0, alt);
        glVertex3f(lar, comp, alt); glVertex3f(0.0, comp, alt);
        glNormal3f(-1,0,0);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, alt);
        glVertex3f(0.0, comp, alt); glVertex3f(0.0, comp, 0.0);
        glNormal3f(0,-1,0);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, alt);
        glVertex3f(lar, 0.0, alt);  glVertex3f(lar, 0.0, 0.0);
        glNormal3f(1,0,0);
        glVertex3f(lar, 0.0, 0.0);  glVertex3f(lar, 0.0, alt);
        glVertex3f(lar, comp, alt); glVertex3f(lar, comp, 0.0);
        glNormal3f(0,1,0);
        glVertex3f(0.0, comp, 0.0); glVertex3f(0.0, comp, alt);
        glVertex3f(lar, comp, alt); glVertex3f(lar, comp, 0.0);
    glEnd();
}

void Tronco(){
    glColor3f(1.0, 0.0, 0.0);
    glRotatef(TR, 0.0, 0.0, 1.0);
    Paralelo(25.0, 15.0, 25.0);
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(7.0, 12.5, -6.0);
    glutSolidSphere(7.0,  20.0,  20.0);
}

void PernaEsquerda(){
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 6, -8.0);
    glRotatef(PE, 0.0, 1.0, 0.0);
    glRotatef(PE1, 0.0, 0.0, 1.0);
    glutSolidSphere(4.0,  20.0,  20.0);  //  Articulação da Perna Esquerda
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-4.0, -4.0, -28.0);
    Paralelo(8.0, 8.0, 25.0);          //  Perna Esquerda
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 4.0, -3.0);
        glRotatef(JE, 0.0, 1.0, 0.0);
        glutSolidSphere(4.0,  20.0,  20.0);  //  Joelho
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-4.0, -4.0, -28.0);
        Paralelo(8.0, 8.0, 25.0);   //  Canela
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 4.0, -3.0);
        glRotatef(TE, 0.0, 1.0, 0.0);
        glutSolidSphere(4.0,  20.0,  20.0);  //  Tornozelo
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-6.0, -5.0, -8.0);
        Paralelo(10.0, 18.0, 5.0);  //  Pé
    glPopMatrix();
}

void PernaDireita(){
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, -6.0, -8.0);
    glRotatef(PD, 0.0, 1.0, 0.0);
    glRotatef(PD1, 0.0, 0.0, 1.0);
    glutSolidSphere(4.0,  20.0,  20.0); //  Articulação da Perna direita
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-4.0, -4.0, -28.0);
    Paralelo(8.0, 8.0, 25.0);          //  Perna Direita
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 4.0, -3.0);
        glRotatef(JD, 0.0, 1.0, 0.0);
        glutSolidSphere(4.0,  20.0,  20.0);  //  Joelho Direito
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-4.0, -4.0, -28.0);
        Paralelo(8.0, 8.0, 25.0);       //  Canela
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 4.0, -3.0);
        glRotatef(TD, 0.0, 1.0, 0.0);
        glutSolidSphere(4.0,  20.0,  20.0);  //  Tornozelo
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-6.0, -5.0, -8.0);
        Paralelo(10.0, 18.0, 5.0);      //  Pé
    glPopMatrix();
}

void BracoDireito(){
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, -17.0, 27.0);
    glRotatef(OD, 0.0, 1.0, 0.0);
    glutSolidSphere(5.0,  20.0,  20.0);    //Ombro Direito
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-4.0, -4.0, -20.0);
    Paralelo(7.0, 7.0, 16);     //  Anti-braço
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 3.0, -3.0);
        glRotatef(CD, 0.0, 1.0, 0.0);
        glutSolidSphere(4.0,  20.0,  20.0);  //  Cotovelo
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-4.0, -4.0, -19.0);
        Paralelo(8.0, 8.0, 16.0);        //  Braço
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 4.0, -2.0);
        glRotatef(MD, 0.0, 1.0, 0.0);
        glutSolidSphere(3.0, 20.0, 20.0);  //  Monheca
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-4.0, -2.0, -12.0);
        Paralelo(4.0, 8.0, 10.0);       //  Mão
    glPopMatrix();
}

void BracoEsquerdo(){
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 17.0, 27.0);
    glRotatef(OE, 0.0, 1.0, 0.0);
    glutSolidSphere(5.0,  20.0,  20.0);    //Ombro Esquerdo
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-4.0, -3.0, -20.0);
    Paralelo(7.0, 7.0, 16.0);       //  Anti-braço
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(4.0, 4.0, -3.0);
        glRotatef(CE, 0.0, 1.0, 0.0);
        glutSolidSphere(4.0,  20.0,  20.0);  //  Cotovelo
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-4.0, -4.0, -19.0);
        Paralelo(8.0, 8.0, 16.0);       //  Braço
        glColor3f(0.0, 0.0, 1);
        glTranslatef(4.0, 4.0, -2.0);
        glRotatef(ME, 0.0, 1.0, 0.0);
        glutSolidSphere(3.0,  20.0,  20.0);  //  Monheca
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-4.0, -2.0, -12.0);
        Paralelo(4.0, 8.0, 10.0);     //  Mão
    glPopMatrix();
}

void Cabeca(){
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 33.0);
    glutSolidSphere(4.0,  20.0,  20.0);    //Pescoço
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-6.0, -6.0, 3.0);
    Paralelo(12.0, 12.0, 12.0); 
}
// Cria o Robô
void Robo(void)
{
    glPushMatrix();
        Tronco();//     Tronco
        glPushMatrix();
            PernaEsquerda();            
        glPopMatrix();
        glPushMatrix();
            PernaDireita();
        glPopMatrix();
        glPushMatrix();
            BracoDireito();
        glPopMatrix();
        glPushMatrix();
            BracoEsquerdo();
        glPopMatrix();
        Cabeca();
    glPopMatrix();
}

// Cria o piso
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

// Desenha na tela
void Desenhar(void)
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

    Piso();      // Desenha o Piso

    if (acao == ANDAR)
    {
        Posicaox += fabs(3.0 * sin((70 + passo) * GRAU_RAD));  //  Calcula a posição do Robô
        passo = fmod(passo + 8.0, 360.0);
    }

    glTranslatef(Posicaox, 0.0, 85);    // Movimenta o Robô

    Robo();   // Desenha o Robô

////////////////////////////////////////////////////////////////////////////////////////
    glutSwapBuffers();
}

//   Função para iluminar o ambiente
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

// Movimenta o Robô
void Movimento(ACAO a)
{
    static double passo = 0.0;

    switch(a)
    {
        case ANDAR: // Faz o robô andar
            PD = 20.0 * sin(passo * GRAU_RAD); // Movimenta perna direita
            OD = -30.0 * sin(passo * GRAU_RAD); // Movimenta ombro direito
            PE = -20.0 * sin(passo * GRAU_RAD); // Movimenta perna esquerda
            OE = 30.0 * sin(passo * GRAU_RAD);  // Movimenta ombro direito
            CD = -10.0; // cotovelo direito
            CE = -10.0; // cotovelo esquerdo

            JE = -20.0 * sin(passo * GRAU_RAD); // Movimenta joelho esquerdo
            if(JE <= 0.0) JE = 0.0;

            JD = 20.0 * sin(passo * GRAU_RAD); // Movimenta joelho direito
            if(JD <= 0.0) JD = 0.0;

            passo = fmod(passo + 8.0, 360.0); // incrementa o passo na velocidade 8

            break;

        case PARAR: // Faz o robô parar
            if(passo == 0.0) break;

            PD = 20.0 * sin(passo * GRAU_RAD); // Movimenta perna direita
            OD = -30.0 * sin(passo * GRAU_RAD); // Movimenta ombro direito
            PE = -20.0 * sin(passo * GRAU_RAD); // Movimenta perna esquerda
            OE = 30.0 * sin(passo * GRAU_RAD);  // Movimenta ombro direito
            CD = -10.0; // cotovelo direito
            CE = -10.0; // cotovelo esquerdo

            JE = -20.0 * sin(passo * GRAU_RAD); // Movimenta joelho esquerdo
            if(JE <= 0.0) JE = 0.0;

            JD = 20.0 * sin(passo * GRAU_RAD); // Movimenta joelho direito
            if(JD <= 0.0) JD = 0.0;

            // continua a movimentar o robô até que passo seja 180º ou 360º (posição de repouso)
            if (passo < 180.0)
            {
                if ( (passo + 8) > 180.0) passo = 0.0;
                else passo += 8;
            }
            else
            {
                if ( (passo + 8) > 360.0) passo = 0.0;
                else passo += 8;
            }

            break;
    }
}

//  Redimensiona a Janela
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

//  Função para mudar a visualização do espaço pelo movimento do mouse
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

//  Função para movimentar o Braço
void teclado(unsigned char key, int a, int b)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case '+':
            break;
        case '-':
            break;
        case 'p':
            acao = PARAR;
            break;
        case 'a':
            acao = ANDAR;
            break;
    }
}

void Timer(int w)
{
    glutPostRedisplay();
    Movimento(acao);
    glutTimerFunc(PASSO_TEMPO,Timer,1);
}

// Programa Principal
int main(int argc, char*argv[])
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Robô em 3D");
    glutDisplayFunc(Desenhar);
    glutReshapeFunc(Ajustedimensao);
    glutMotionFunc(MoveMouse);
    glutKeyboardFunc(teclado);
    Iluminacao();
    Timer(1);
    glutMainLoop();
}
