//*****************************************************
//
// ObjetoComTransformacoesHierarquicas.cpp
// Um programa OpenGL simples que abre uma janela GLUT,
// desenha e permite interagir com um objeto que �
// modelado atrav�s da utiliza��o de transforma��es
// hier�rquicas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

// Declara��o de vari�veis globais
GLfloat tx = 0;
GLfloat ang1 = 0, ang2 = -90;
GLfloat win = 25;

// Fun��o para desenhar um "bra�o" do objeto
void DesenhaBraco()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.0,4.6);
		glVertex2f(1.0,-0.8);
		glVertex2f(-1.0,-0.8);
		glVertex2f(-1.0,4.6);
	glEnd();
	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2i(0,0);
	glEnd();
}

// Fun��o para desenhar a base do objeto
void DesenhaBase()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.8,1);
		glVertex2f(1.8,-1.5);
		glVertex2f(1.0,-1.5);
		glVertex2f(1.0,-1);
		glVertex2f(-1.0,-1);
		glVertex2f(-1.0,-1.5);
		glVertex2f(-1.8,-1.5);
		glVertex2f(-1.8,1);
	glEnd();
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	// Desenha o "ch�o"
	glColor3f(0.0f,0.0f,0.0f);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-win,-3.9);
		glVertex2f(win,-3.9);
	glEnd();
	glPushMatrix();
	glTranslatef(tx,0.0f,0.0f);
	glPushMatrix();
	glScalef(2.5f,2.5f,1.0f);
	glColor3f(1.0f,0.0f,0.0f);
	DesenhaBase();
	glPopMatrix();
	glTranslatef(0.0f,1.5f,0.0f);
	glRotatef(ang1,0.0f,0.0f,1.0f);
	glScalef(1.4f,1.4f,1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	DesenhaBraco();
	glTranslatef(0.4f,2.6f,0.0f);
	glRotatef(ang2,0.0f,0.0f,1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	DesenhaBraco();
	glPopMatrix();

	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura)
	{
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}
	else
	{
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;
	}
}

// Fun��o callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		tx-=2;
		if ( tx < -win )
			tx = -win;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=2;
		if ( tx > win )
			tx = win;
	}

	// Rotaciona braco1
	if(key == GLUT_KEY_HOME)
		ang1-=5;
	if(key == GLUT_KEY_END)
		ang1+=5;

	// Rotaciona braco2
	if(key == GLUT_KEY_PAGE_UP)
		ang2-=5;
	if(key == GLUT_KEY_PAGE_DOWN)
		ang2+=5;

	glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Exibe mensagem que avisa como interagir
	printf(" Setas para esquerda e para direita movimentam a base (vermelha)");
	printf("\n Home e End rotacionam o braco 1 (verde)");
	printf("\n PageUP e PageDn rotacionam o braco 2 (azul)");
}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,300);
	glutCreateWindow("Desenho de objeto modelado com transforma��es hier�rquicas");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}