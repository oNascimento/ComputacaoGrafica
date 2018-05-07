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
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author onascimento
 */
public class Poligono {
    public ArrayList<Ponto> pontos;
    public int tipo;
    /*
        1 - Linhas
        2 - Circunferencia
        3 - Curvas
        4 - Clipping
    */

    public void setPontos(ArrayList<Ponto> pontos) {
        this.pontos = pontos;
    }
    
    private Poligono(ArrayList<Ponto> ponto) {
        this.setPontos(ponto);
    }

    public Poligono() {
        pontos = new ArrayList<Ponto>();
        tipo = 1;
    }
    
    public Poligono(int tipo){
        pontos = new ArrayList<Ponto>();
        this.tipo = tipo;
    }

    public ArrayList<Ponto> getPontos() {
        return pontos;
    }

    public void draw(Canvas c, Janela vP, Janela mundo) {
        //System.out.println("Tamanho vetor ponto: "+this.getPontos().size());
        Ponto aux = null;
        Graphics g = c.getGraphics();
        
        
        if(tipo == 4){
            g.setColor(Color.YELLOW);
        }else{
            g.setColor(Color.WHITE);
        }
        
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

    public Ponto pontoMedio(Ponto p1, Ponto p2) {
        Ponto aux = new Ponto();
        aux.setX((p1.getX() + p2.getX()) / 2);
        aux.setY((p1.getY() + p2.getY()) / 2);
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
        
        
        if(tipo == 4){
            g.setColor(Color.YELLOW);
        }else{
            g.setColor(Color.BLACK);
        }
        
        
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
        
        
        if(tipo == 4){
            g.setColor(Color.YELLOW);
        }else{
            g.setColor(Color.BLUE);
        }
        
        
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

    public Ponto pontosCirculo(int x, int y) {
//        /Graphics g = c.getGraphics();
        x = (int) (x + this.getPontos().get(0).getX());
        y = (int) (y + this.getPontos().get(0).getY());
        Ponto auxP = new Ponto(x, y);
        return auxP;

    }

    public Poligono drawCirculo(Ponto p1,Ponto p2) {
        //Graphics g = c.getGraphics();
        Poligono auxPol = new Poligono();
        Ponto auxM[][] = new Ponto[8][CalculaRaio(p1,p2)];
        ArrayList<ArrayList<Ponto>> lista = new ArrayList<>();
        int x, y, p, r, i = 0;
        r = CalculaRaio(p1,p2);
        x = 0;
        //y = Integer.parseInt(JOptionPane.showInputDialog("Informe o raio", r));
        y = r;
        //this.pontosCirculo(x, y, c, viewPort, mundo);
        p = 1 - r;
        while (x < y) {
            if (p < 0) {
                x++;
            } else {
                x++;
                y--;
            }
            if (p < 0) {
                p += 2 * x + 1;
            } else {
                p += 2 * (x - y) + 1;
            }
            auxM[0][i] = this.pontosCirculo(x, y);
            auxM[1][i] = this.pontosCirculo(y, x);
            auxM[2][i] = this.pontosCirculo(y, -x);
            auxM[3][i] = this.pontosCirculo(x, -y);
            auxM[4][i] = this.pontosCirculo(-x, -y);
            auxM[5][i] = this.pontosCirculo(-y, -x);
            auxM[6][i] = this.pontosCirculo(-y, x);
            auxM[7][i] = this.pontosCirculo(-x, y);
            i++;
        }
        
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < i; k++) {
                auxPol.getPontos().add(auxM[j][k]);
            }
        }
        
        //auxPol.setTypeF(0);
        //auxPol.draw(c, viewPort, mundo);
        return auxPol;
    }
    
    public int CalculaRaio(Ponto p1, Ponto p2){
        int raio = (int) Math.sqrt(((p1.getX() - p2.getX())*(p1.getX() - p2.getX())) + ((p1.getY() - p2.getY())*(p1.getY() - p2.getY())));
        return raio;
    }
    
    public void clip(float xmin, float ymin, float xmax, float ymax) {
// Sutherland-Hodgman polygon clipping:
        Poligono poly1 = new Poligono();
        int n;
        Ponto a, b;
        boolean aIns, bIns;
        
        tipo = 4;
// Tells whether A or B is on the same side as the rectangle
// Clip against x == xmax:
        if ((n = pontos.size()) == 0) {
            return;
        }
        b = vertexAt(n - 1);
        for (int i = 0; i < n; i++) {
            a = b;
            b = vertexAt(i);
            aIns = a.x <= xmax;
            bIns = b.x <= xmax;
            if (aIns != bIns) {
                poly1.pontos.add(new Ponto(xmax,
                        a.y + (b.y - a.y) * (xmax - a.x) / (b.x - a.x)));
            }
            if (bIns) {
                poly1.pontos.add(b);
            }
        }
        pontos = poly1.pontos;
        poly1 = new Poligono();
// Clip against x == xmin:
        if ((n = pontos.size()) == 0) {
            return;
        }
        b = vertexAt(n - 1);
        for (int i = 0; i < n; i++) {
            a = b;
            b = vertexAt(i);
            aIns = a.x >= xmin;
            bIns = b.x >= xmin;

            if (aIns != bIns) {
                poly1.pontos.add(new Ponto(xmin,
                        a.y + (b.y - a.y) * (xmin - a.x) / (b.x - a.x)));
            }
            if (bIns) {
                poly1.pontos.add(b);
            }
        }
        pontos = poly1.pontos;
        poly1 = new Poligono();
// Clip against y == ymax:
        if ((n = pontos.size()) == 0) {
            return;
        }
        b = vertexAt(n - 1);
        for (int i = 0; i < n; i++) {
            a = b;
            b = vertexAt(i);
            aIns = a.y <= ymax;
            bIns = b.y <= ymax;
            if (aIns != bIns) {
                poly1.pontos.add(new Ponto(a.x
                        + (b.x - a.x) * (ymax - a.y) / (b.y - a.y), ymax));
            }
            if (bIns) {
                poly1.pontos.add(b);
            }
        }
        pontos = poly1.pontos;
        poly1 = new Poligono();
// Clip against y == ymin:
        if ((n = pontos.size()) == 0) {
            return;
        }
        b = vertexAt(n - 1);
        for (int i = 0; i < n; i++) {
            a = b;
            b = vertexAt(i);
            aIns = a.y >= ymin;
            bIns = b.y >= ymin;
            if (aIns != bIns) {
                poly1.pontos.add(new Ponto(a.x
                        + (b.x - a.x) * (ymin - a.y) / (b.y - a.y), ymin));
            }
            if (bIns) {
                poly1.pontos.add(b);
            }
        }
        pontos = poly1.pontos;
    }
    
    Ponto vertexAt(int i){
        return pontos.get(i);
    }
}
