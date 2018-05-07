/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Objetos;

import Componentes.Janela;

/**
 *
 * @author onascimento
 */
public class Ponto {
    double x;
    double y;

    public Ponto() {
        x = 0;
        y = 0;
    }

    public Ponto(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    @Override
    public String toString() {
        return ("("+(int)(this.getX())+","+(int)(this.getY())+")");
    }
    
    public int XwvP(int x, Janela mundo, Janela vP) {
        return (int) ((((x - mundo.getMinX()) / (mundo.getMaxX() - mundo.getMinX())) * (vP.getMaxX() - vP.getMinX())) + vP.getMinX());
    }

    public int YwvP(int y, Janela mundo, Janela vP) {
        return (int) ((((1 - (y - mundo.getMinY()) / (mundo.getMaxY() - mundo.getMinY()))) * (vP.getMaxY() - vP.getMinY())) + vP.getMinY());
    }

    public int YvpM(int y, Janela vP, Janela mundo) {
        return (int) ((int) (((1-(y - mundo.getMinY())/(mundo.getMaxY()-mundo.getMinY())))*(vP.getMaxY()-vP.getMinY()))+vP.getMinY());
    }

    public int XvpM(int x, Janela vP, Janela mundo) {
        return (int) ((int) (((x - mundo.getMinX())/(mundo.getMaxX()-mundo.getMinX()))*(vP.getMaxX()-vP.getMinX()))+vP.getMinX());
    }
    
    public void translacao(double xD, double yD){
        setX(getX()+xD);
        setY(getY()+yD);
    }
    
    public void escalonar(double sX, double sY){
        setX(getX()*sX);
        setY(getY()*sY);
    }
    
    public void reflexãoY(){
        setX((getX())*-1);
    }
    
    public void reflexãoX(){
        setY((getY())*-1);
    }
    
    public void reflexãoXY(){
        reflexãoY();
        reflexãoX();
    }
    
    public void rotacao(double g){
        g = (g/180)*Math.PI;
        double xG, yG;
        xG = getX()*(Math.cos(g)) - getY()*(Math.sin(g));
        yG = getX()*(Math.sin(g)) + getY()*(Math.cos(g));
        setX(xG);
        setY(yG);
    }
}
