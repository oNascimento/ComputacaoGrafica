/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Objetos;

import Componentes.Janela;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

/**
 *
 * @author onascimento
 */
public class Poligono {
    public ArrayList<Ponto> pontos;

    public void setPontos(ArrayList<Ponto> pontos) {
        this.pontos = pontos;
    }
    
    private Poligono(ArrayList<Ponto> ponto) {
        setPontos(ponto);
    }

    public Poligono() {
        pontos = new ArrayList<Ponto>();
    }

    public ArrayList<Ponto> getPontos() {
        return pontos;
    }

    public void draw(Canvas c, Janela vP, Janela mundo) {
        //System.out.println("Tamanho vetor ponto: "+this.getPontos().size());
        Ponto aux = null;
        Graphics g = c.getGraphics();
        
        g.setColor(Color.WHITE);
        
        for(Ponto p : pontos){
            if(aux == null){
                aux = p;
            }else{
                Ponto aux2 = new Ponto();
                g.drawLine(aux2.XwvP((int) aux.getX(), mundo, vP),aux2.YwvP((int) aux.getY(), mundo, vP), 
                           aux2.XwvP((int) p.getX(), mundo, vP),aux2.YwvP((int) p.getY(), mundo, vP));
                aux = p;
            }
        }
    }

    public Ponto pontoMedio() {
        Ponto aux = new Ponto();
        for(Ponto p: pontos){
            aux.x += p.getX();
            aux.y += p.getY();
        }
        aux.x = aux.getX()/pontos.size();
        aux.y = aux.getY()/pontos.size();
        
        return aux;
    }

    public void transladar(double xD, double yD) {
        int i = this.getPontos().size();
        for (int j = 0; j < i; j++) {
            this.pontos.get(j).translacao(xD, yD);
        }
    }

    public void escalonar(double xD, double yD) {
        int i = this.getPontos().size();
        for (int j = 0; j < i; j++) {
            this.pontos.get(j).escalonar(xD, yD);
        }
    }

    public void reflexao(int op) {
        int i = this.getPontos().size();
        if (op == 0) {
            for (int j = 0; j < i; j++) {
                this.pontos.get(j).reflexãoY();
            }
        }
        if (op == 1) {
            for (int j = 0; j < i; j++) {
                this.pontos.get(j).reflexãoX();
            }
        }
        if (op == 2) {
            for (int j = 0; j < i; j++) {
                this.pontos.get(j).reflexãoXY();
            }
        }
    }

    public void rotacionar(double g) {
        //g = (g/180)*Math.PI;
        double i = this.pontos.size();
        double xP = 0, yP = 0;
        for (int j = 0; j < i; j++) {
            xP = xP + this.pontos.get(j).getX();
            yP = yP + this.pontos.get(j).getY();
        }
        System.out.println(xP + "" + yP);
        xP = xP / i;
        yP = yP / i;
        for (int j = 0; j < i; j++) {
            this.pontos.get(j).setX(this.pontos.get(j).getX() - xP);
            this.pontos.get(j).setY(this.pontos.get(j).getY() - yP);
        }
        for (int j = 0; j < i; j++) {
            this.pontos.get(j).rotacao(g);
        }
        for (int j = 0; j < i; j++) {
            this.pontos.get(j).setX(this.pontos.get(j).getX() + xP);
            this.pontos.get(j).setY(this.pontos.get(j).getY() + yP);
        }
    }

    public void drawDda(Canvas c, Janela vP, Janela mundo) {
        double dX, dY, tamanho;
        Graphics g = c.getGraphics();
        int i = this.getPontos().size();
        if (i > 1) {
            for (int j = 0; j < i - 1; j++) {
                Ponto pI = new Ponto(this.getPontos().get(j).getX(), this.getPontos().get(j).getY());
                Ponto pF = new Ponto(this.getPontos().get(j + 1).getX(), this.getPontos().get(j + 1).getY());
                if (Math.abs(pF.getX() - pI.getX()) == 0) {
                    g.drawLine((int) this.pontos.get(j).XvpM((int) this.pontos.get(j).x, vP, mundo), (int) this.pontos.get(j).YvpM((int) this.pontos.get(j).y, vP, mundo), (int) this.pontos.get(j + 1).XvpM((int) this.pontos.get(j + 1).x, vP, mundo), (int) this.pontos.get(j + 1).YvpM((int) this.pontos.get(j + 1).y, vP, mundo));
                } else {
                    if (Math.abs(pF.getX() - pI.getX()) > Math.abs(pF.getY() - pI.getY())) {
                        tamanho = Math.abs(pF.getX() - pI.getX());
                    } else {
                        tamanho = Math.abs(pF.getY() - pI.getY());
                    }
                    dX = (pF.getX() - pI.getX()) / tamanho;
                    dY = (pF.getY() - pI.getY()) / tamanho;
                    Ponto pAux = new Ponto(pI.getX() + (0.5 * Math.signum(dX)), pI.getY() + (0.5 * Math.signum(dY)));
                    //Ponto pAnterior = new Ponto(pI.getX() + (0.5 * Math.signum(dX)), pI.getY() + (0.5 * Math.signum(dY)));
                    //g.drawLine((int) this.pontos.get(j).XvpM((int) this.pontos.get(j).x, vP, mundo), (int) this.pontos.get(j).YvpM((int) this.pontos.get(j).y, vP, mundo), (int) this.pontos.get(j).XvpM((int) this.pontos.get(j).x, vP, mundo), (int) this.pontos.get(j).YvpM((int) this.pontos.get(j).y, mundo, vP));
                    for (int k = 0; k < tamanho; k++) {
                        g.drawLine(pAux.XvpM((int) pAux.getX(), vP, mundo), pAux.YvpM((int) pAux.getY(), vP, mundo), pAux.XvpM((int) ((int) pAux.getX()), vP, mundo), pAux.YvpM((int) ((int) pAux.getY()), vP, mundo));
                        pAux.setX(pAux.getX() + dX);
                        pAux.setY(pAux.getY() + dY);
                    }
                }
            }
        }
    }

    public void drawBresenham(Canvas c, Janela vP, Janela mundo) {
        int dx, dy, erro;
        Ponto aux;
        Graphics g = c.getGraphics();
        int i = this.pontos.size();
        if (i > 1) {
            erro = 0;
            aux = new Ponto();
            for (int j = 0; j < i - 1; j++) {
                aux.setX(this.getPontos().get(j).getX());
                aux.setY(this.getPontos().get(j).getY());
                dx = (int) (this.getPontos().get(j + 1).getX() - this.getPontos().get(j).getX());
                dy = (int) (this.getPontos().get(j + 1).getY() - this.getPontos().get(j).getY());
                if ((Math.abs(dy) >= Math.abs(dx) && this.getPontos().get(j).getY() > this.getPontos().get(j + 1).getY()) || (Math.abs(dy) < Math.abs(dx) && dy < 0)) {
                    aux.setX(this.getPontos().get(j + 1).getX());
                    aux.setY(this.getPontos().get(j + 1).getY());
                    dx = (int) (this.getPontos().get(j).getX() - this.getPontos().get(j + 1).getX());
                    dy = (int) (this.getPontos().get(j).getY() - this.getPontos().get(j + 1).getY());
                }
                g.drawLine((int) this.pontos.get(j).XvpM((int) this.pontos.get(j).x, vP, mundo), (int) this.pontos.get(j).YvpM((int) this.pontos.get(j).y, vP, mundo), (int) this.pontos.get(j).XvpM((int) this.pontos.get(j).x, vP, mundo), (int) this.pontos.get(j).YvpM((int) this.pontos.get(j).y, vP, mundo));
                if (dx > 0) {
                    if (Math.abs(dx) >= Math.abs(dy)) {
                        for (int k = 1; k < Math.abs(dx); k++) {
                            if (erro < 0) {
                                aux.setX(aux.getX() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + dy;
                            } else {
                                aux.setX(aux.getX() + 1);
                                aux.setY(aux.getY() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + (dy - dx);
                            }
                        }
                    } else {
                        for (int k = 1; k < Math.abs(dy); k++) {
                            if (erro < 0) {
                                aux.setX(aux.getX() + 1);
                                aux.setY(aux.getY() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + (dy - dx);
                            } else {
                                aux.setY(aux.getY() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro - dx;
                            }
                        }
                    }
                } else {
                    if (Math.abs(dx) >= Math.abs(dy)) {
                        for (int k = 1; k < Math.abs(dx); k++) {
                            if (erro < 0) {
                                aux.setX(aux.getX() - 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + dy;
                            } else {
                                aux.setX(aux.getX() - 1);
                                aux.setY(aux.getY() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + (dy + dx);
                            }
                        }
                    } else {
                        for (int k = 1; k < Math.abs(dy); k++) {
                            if (erro < 0) {
                                aux.setX(aux.getX() - 1);
                                aux.setY(aux.getY() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + (dy + dx);
                            } else {
                                aux.setY(aux.getY() + 1);
                                //System.out.print(aux);
                                g.drawLine(aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo), aux.XvpM((int) aux.getX(), vP, mundo), aux.YvpM((int) aux.getY(), vP, mundo));
                                erro = erro + dx;
                            }
                        }
                    }
                }
            }
        }
    }

//    public Ponto pontosCirculo(int x, int y) {
////        /Graphics g = c.getGraphics();
//        x = (int) (x + this.getPontos().get(0).getX());
//        y = (int) (y + this.getPontos().get(0).getY());
//        Ponto auxP = new Ponto(x, y);
//        return auxP;
//
//    }

//    public Poligono drawCirculo() {
//        //Graphics g = c.getGraphics();
//        Poligono auxPol = new Poligono();
//        Ponto auxM[][] = new Ponto[8][this.getRaio()];
//        ArrayList<ArrayList<Ponto>> lista = new ArrayList<>();
//        int x, y, p, r, i = 0;
//        r = this.getRaio();
//        x = 0;
//        //y = Integer.parseInt(JOptionPane.showInputDialog("Informe o raio", r));
//        y = r;
//        //this.pontosCirculo(x, y, c, viewPort, mundo);
//        p = 1 - r;
//        while (x < y) {
//            if (p < 0) {
//                x++;
//            } else {
//                x++;
//                y--;
//            }
//            if (p < 0) {
//                p += 2 * x + 1;
//            } else {
//                p += 2 * (x - y) + 1;
//            }
//            auxM[0][i] = this.pontosCirculo(x, y);
//            auxM[1][i] = this.pontosCirculo(y, x);
//            auxM[2][i] = this.pontosCirculo(y, -x);
//            auxM[3][i] = this.pontosCirculo(x, -y);
//            auxM[4][i] = this.pontosCirculo(-x, -y);
//            auxM[5][i] = this.pontosCirculo(-y, -x);
//            auxM[6][i] = this.pontosCirculo(-y, x);
//            auxM[7][i] = this.pontosCirculo(-x, y);
//            i++;
//        }
////        System.out.println(auxM[0][0]+","+lista.get(0).get(0));
//        
//        for (int j = 0; j < 8; j++) {
//            for (int k = 0; k < i; k++) {
//                auxPol.getPontos().add(auxM[j][k]);
//            }
//        }
//        auxPol.setTypeD(this.getTypeD());
//        //auxPol.setTypeF(0);
//        //auxPol.draw(c, viewPort, mundo);
//        return auxPol;
//    }
}
