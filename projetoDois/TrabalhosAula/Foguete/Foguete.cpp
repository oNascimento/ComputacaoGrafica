/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Casa.cpp
 * Author: onascimento
 *
 * Created on 21 de Maio de 2018, 16:35
 */

#include <cstdlib>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

using namespace std;

/*
 * 
 */

int ang = 0;
int tlargura = 0;
int taltura = 0;
int win =50;
float aspecto, largura, altura;


void Bico(void){
	//Bico
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    	glVertex2f(-5.0f, 25.0f);
        glVertex2f( 0.0f, 45.0f);
        glVertex2f(5.0f,  25.0f);
    glEnd();
}

void Corpo(void){
	//Corpo
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
        glVertex2f(-5.0f,-25.0f);
        glVertex2f(-5.0f, 25.0f);
        glVertex2f(5.0f,  25.0f);
        glVertex2f(5.0f, -25.0f);
    glEnd();
}

void AsaDireita(void){
	//AsaDireita
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    	glVertex2f(5.0f, -25.0f);
		glVertex2f(15.0f, -25.0f);
		glVertex2f(5.0f, -5.0f);
    glEnd();
}

void AsaEsquerda(void){
	//Asa Esquerda
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    	glVertex2f(-5.0f, -25.0f);
		glVertex2f(-15.0f, -25.0f);
		glVertex2f(-5.0f, -5.0f);
    glEnd();
}

void DesenhaFoguete(void){
	Corpo();
    Bico();
    AsaEsquerda();
    AsaDireita();
}

void Rotaciona(void){
	glRotatef(ang,0.0f,0.0f,1.0f);
}

void Transladar(void){
	glTranslatef(tlargura,taltura,0.0f);
}

void MovimentaTeclado(unsigned char tecla, int x, int y){
	//Transladar
	if(tecla == 'w'){
		taltura += 1;
		if(taltura > win){
			taltura = win;
		}
	}
	if(tecla == 'a'){
		tlargura -= 1;
		if(tlargura < -win){
			tlargura = -win;
		}
	}
	if(tecla == 'd'){
		tlargura += 1;
		if(tlargura > win){
			tlargura = win;
		}
	}
	if(tecla == 's'){
		taltura -= 1;
		if(taltura < -win){
			taltura = -win;
		}
	}

	//Rotacionar
	if(tecla == 'q'){
		ang += 1;
	}

	if(tecla == 'e'){
		ang -= 1;
	}

	glutPostRedisplay();
}

void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    	Rotaciona();//Rociona caso selecionado
    	Transladar();//Translada caso selecionado
    	DesenhaFoguete();
    glPopMatrix();
    glFlush();
}

void Inicializa(void){
    glClearColor(0,0,0,1);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){
    if(h==0) h=1;
    
    largura = w/2;
    altura = h;
    aspecto = (float) largura/altura;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(-win*aspecto,win*aspecto,-win,win);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Foguete");
    Inicializa();
    glutKeyboardFunc(MovimentaTeclado);
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);//Altera o tamanho da janela
    glutMainLoop();
    
    return 0;
}

