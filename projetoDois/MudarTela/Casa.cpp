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

int ang=0;
int win=50;
float aspecto, largura, altura;

void DesenhaCasa(void){
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-15.0f, -15.0f);
        glVertex2f(-15.0f, 5.0f);
        glVertex2f(15.0f, 5.0f);
        glVertex2f(15.0f, -15.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-4.0f, -14.5f);
        glVertex2f(-4.0f, 0.0f);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(4.0f, -14.5f);
        glVertex2f(7.0f, -5.0f);
        glVertex2f(7.0f, -1.0f);
        glVertex2f(13.0f, -1.0f);
        glVertex2f(13.0f, -5.0f);
    glEnd();
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINES);
        glVertex2f(7.0f,-3.0f);
        glVertex2f(13.0f, -3.0f);
        glVertex2f(10.0f,-1.0f);
        glVertex2f(10.0f,-5.0f);
    glEnd();
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-15.0f, 5.0f);
        glVertex2f(0.0f,17.0f);
        glVertex2f(15.0f,5.0f);
    glEnd();
}

void FazMoldura(void){
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-win*aspecto,-win);
        glVertex2f(-win*aspecto, win);
        glVertex2f( win*aspecto, win);
        glVertex2f( win*aspecto,-win);
    glEnd();
    
    glLineWidth(1);
}

void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0, largura,altura);
    
    DesenhaCasa();
    FazMoldura();
    
    glViewport(largura,0, largura,altura);
    
    glRotatef(ang,0,0,1);
    DesenhaCasa();
    FazMoldura();
    
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
    //glLoadIdentity();
    
    gluOrtho2D(-win*aspecto,win*aspecto,-win,win);
}

void cliqueMouse(int botao, int estado, int x, int y){
    if(botao == GLUT_LEFT_BUTTON)
        ang+=10;
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Primeiro Programa");
    Inicializa();
    glutDisplayFunc(Desenha);
    glLoadIdentity();
    glutMouseFunc(cliqueMouse);
    glutReshapeFunc(AlteraTamanhoJanela);//Altera o tamanho da janela
    glutMainLoop();
    
    return 0;
}

