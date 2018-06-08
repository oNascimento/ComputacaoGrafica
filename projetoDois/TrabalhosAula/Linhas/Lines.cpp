/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: onascimento
 *
 * Created on 21 de Maio de 2018, 16:14
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
void Desenha(void){
    GLint width;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glPushAttrib(GL_LINE_BIT);
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(5);

    glBegin(GL_LINES);
        glVertex2f(-40.0f, -40.0f); glVertex2f(40.0f, -40.0f);
        glVertex2f(-40.0f, -30.0f); glVertex2f(40.0f, -30.0f);
    glEnd();

    glGetIntegerv(GL_LINE_WIDTH, &width);
    glPopAttrib();

    glBegin(GL_LINES);
        glVertex2f(-40.0f, -5.0f); glVertex2f(40.0f, -5.0f);
        glVertex2f(-40.0f, 5.0f); glVertex2f(40.0f, 5.0f);
    glEnd();

    glPopAttrib();

    glBegin(GL_LINES);
        glVertex2f(-40.0f, 30.0f); glVertex2f(40.0f, 30.0f);
        glVertex2f(-40.0f, 40.0f); glVertex2f(40.0f, 40.0f);
    glEnd();

    glFlush();
}

void Inicializa(void){
    glClearColor(0,0,0,1);
}

void AlteraTamanho(int w, int h){
    if(h==0)
        h=1;
    
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(w<=h)
        gluOrtho2D(-50.0f,50.0f,-50.0f*h/w,50.0f*h/w);
    else
        gluOrtho2D(-50.0f*w/h,50.0f*w/h,-50.0f,50.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Primeiro Programa");
    glutDisplayFunc(Desenha);
    
    Inicializa();
    glutReshapeFunc(AlteraTamanho);//Altera o tamanho da janela
    glutMainLoop();
    return 0;
}

