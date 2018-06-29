//*****************************************************
//
// ExemploTextura1D.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um plano com uma textura 1D
//
// � poss�vel ativar/desativar a repeti��o da textura
// usando a tecla "r" e controlar a quantidade de
// repeti��es com as teclas "+" e "-"
//
// Tamb�m � poss�vel ativar/desativar a interpola��o
// linear (GL_LINEAR) da textura usando a tecla 'f'
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>

// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Define uma textura 1D com 16 posi��es
#define TAM	16
GLubyte textura[] = { 0,0,0,0,64,64,64,64,128,128,128,128,192,192,192,192 };

// Desativa repeti��o da textura
char repete = 0;

// Desativa interpola��o linear da textura
GLint filtro = GL_NEAREST;

// Define valor final da coordenada de textura
float final = 1.0;

// Armazena identifica��o da textura
GLuint textura_id;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_1D);

	glBegin(GL_QUADS);
		glTexCoord1f(0);
		glVertex3f(-1,-1,0);
		glTexCoord1f(final);
		glVertex3f( 1,-1,0);
		glTexCoord1f(final);
		glVertex3f( 1, 1,0);
		glTexCoord1f(0);
		glVertex3f(-1, 1,0);
	glEnd();

	glDisable(GL_TEXTURE_1D);

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(90,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	PosicionaObservador();
}


// Fun��o callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{
	// Trata as diversas teclas
	switch(key)
	{
		case 27:	exit(0);
					break;
		case 'f':	if(filtro == GL_LINEAR) filtro = GL_NEAREST;
					else filtro = GL_LINEAR;
					break;
		case 'r':	repete = !repete;
					break;
		case '+':	if(final<=10.0) final += 0.1;
					break;
		case '-':	if(final>0) final -= 0.1;
					break;
	}

	// Ajusta os par�metros de repeti��o
	if(repete)
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	else
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	// Ajusta os filtros
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, filtro);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, filtro);

	glutPostRedisplay();
}

// Fun��o callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_HOME:	if(angle>=10)  angle -=5;
							break;
		case GLUT_KEY_END:	if(angle<=150) angle +=5;
							break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	100.0
#define SENS_TRANSL	100.0
void GerenciaMovim(int x, int y)
{
	// Bot�o esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica �ngulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Bot�o direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferen�a
		int deltaz = y_ini - y;
		// E modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Bot�o do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posi��es
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Gera um n�mero de identifica��o para a textura
	glGenTextures(1,&textura_id);

	// Associa a textura aos comandos seguintes
	glBindTexture(GL_TEXTURE_1D, textura_id);

	// Envia a textura para uso pela OpenGL
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, TAM, 0, GL_LUMINANCE,
	       	GL_UNSIGNED_BYTE, textura);

	// Define os filtros de magnifica��o e minifica��o
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Seleciona o modo de aplica��o da textura
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Inicializa as vari�veis usadas para alterar a posi��o do
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 1.5;
}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Texturas 1D");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de teclado
	glutKeyboardFunc(Teclado);

	// Registra a fun��o callback de teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a fun��o callback para eventos de bot�es do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a fun��o callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovim);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
