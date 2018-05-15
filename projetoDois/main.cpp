/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: onascimento
 *
 * Created on 14 de Maio de 2018, 23:05
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

void teclado(unsigned char tecla, int x, int y){
    int modificadores = glutGetModifiers();
    
    if(modificadores & GLUT_ACTIVE_ALT) 
        printf("alt\n");
    if(modificadores & GLUT_ACTIVE_SHIFT) 
        printf("shift\n");
    if(modificadores & GLUT_ACTIVE_CTRL) 
        printf("ctrl\n");
    
    switch(tecla){
        case 27 :
                    printf("Tchau");
                    exit(0);
        default:
                    printf("vc apertou [%c] = [%d]\n",tecla,tecla);
    }
}

void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void Inicializa(void){
    glClearColor(0,0,0,1);
}

void cliqueMouse(int botao, int estado, int x, int y){
    if(botao == GLUT_LEFT_BUTTON)
        printf("Mouse Esquerdo [%d] [%d]\n", x,y);
    if(botao == GLUT_RIGHT_BUTTON)
        printf("Mouse Direito [%d] [%d]\n", x,y);
}

void movimenta(int x, int y){
    printf("MousePressionado [%d] [%d]\n", x, y);
}

void movimentoMouse(int x, int y){
    printf("[%d] [%d]\n", x, y);
}

void ocioso(){
    printf(".");
}

void funcaoMenu(int opcao){
    switch(opcao){
        case 0: glClearColor(1,0,0,1);break;
        case 1: glClearColor(0,1,0,1);break;
        case 2: glClearColor(0,0,1,1);break;
        case 3: glClearColor(0,0,0,1);break;
        case 4: glClearColor(1,1,1,1);break;
    }
    
    glutPostRedisplay();
}

void criaMenu(){
    glutCreateMenu(funcaoMenu);
    glutAddMenuEntry("Vermelho", 0);
    glutAddMenuEntry("Verde", 1);
    glutAddMenuEntry("Azul", 2);
    glutAddMenuEntry("Preto", 3);
    glutAddMenuEntry("Branco", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    glutKeyboardFunc(teclado);
    Inicializa();
    glutMouseFunc(cliqueMouse);
    glutMotionFunc(movimenta);
    glutPassiveMotionFunc(movimentoMouse);
    glutReshapeFunc(AlteraTamanho);//Altera o tamanho da janela
    //glutIdleFunc(ocioso);
    criaMenu();
    glutMainLoop();
    
    return 0;
}

