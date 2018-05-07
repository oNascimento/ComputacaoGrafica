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
    public ArrayList<Ponto3D> pontos3D;
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
        setPontos(ponto);
    }
    
    public Poligono(Ponto3D ponto3D){}
    
    public Poligono() {
        pontos = new ArrayList<>();
        tipo = 1;
    }

    public Poligono(int tipo) {
        pontos = new ArrayList<>();
        this.tipo = tipo;
    }

    public ArrayList<Ponto> getPontos() {
        return pontos;
    }
    
    

    public void draw(Canvas c, Janela vP, Janela mundo) {
        //System.out.println("Tamanho vetor ponto: "+this.getPontos().size());
        Ponto aux = null;
        Graphics g = c.getGraphics();

        if (tipo == 4) {
            g.setColor(Color.YELLOW);
        } else {
            g.setColor(Color.WHITE);
        }

        for (Ponto p : pontos) {
            if (aux == null) {
                aux = p;
            } else {
                Ponto aux2 = new Ponto();
                g.drawLine(aux2.XwvP((int) aux.getX(), mundo, vP), aux2.YwvP((int) aux.getY(), mundo, vP),
                        aux2.XwvP((int) p.getX(), mundo, vP), aux2.YwvP((int) p.getY(), mundo, vP));
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

        if (tipo == 4) {
            g.setColor(Color.YELLOW);
        } else {
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

        if (tipo == 4) {
            g.setColor(Color.YELLOW);
        } else {
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

    public Poligono drawCirculo(Ponto p1, Ponto p2) {
        //Graphics g = c.getGraphics();
        Poligono auxPol = new Poligono();
        Ponto auxM[][] = new Ponto[8][CalculaRaio(p1, p2)];
        ArrayList<ArrayList<Ponto>> lista = new ArrayList<>();
        int x, y, p, r, i = 0;
        r = CalculaRaio(p1, p2);
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

    public int CalculaRaio(Ponto p1, Ponto p2) {
        int raio = (int) Math.sqrt(((p1.getX() - p2.getX()) * (p1.getX() - p2.getX())) + ((p1.getY() - p2.getY()) * (p1.getY() - p2.getY())));
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

    Ponto vertexAt(int i) {
        return pontos.get(i);
    }

    public void CalculaCurvaCasteljau() {
        Ponto a = this.getPontos().get(0);
        Ponto b = this.getPontos().get(1);
        Ponto c = this.getPontos().get(2);
        pontos.clear();
        Ponto meioAB, meioBC;
        meioAB = meioReta(a, b);
        meioBC = meioReta(b, c);
        pontos.add(ladoEsquerdo(a, meioAB, meioReta(meioAB, meioBC)));
        ladoDireito(meioReta(meioAB, meioBC), meioBC, c);
    }

    private Ponto meioReta(Ponto a, Ponto b) {
        return new Ponto((a.getX() + b.getX()) / 2, (a.getY() + b.getY()) / 2);
    }

    private Ponto ladoEsquerdo(Ponto a, Ponto b, Ponto c) {
        Ponto meioAB, meioBC;
        meioAB = meioReta(a, b);
        meioBC = meioReta(b, c);
        if ((c.getX() == a.getX()) && (c.getY() == a.getY())) {
            pontos.add(c);
            return c;
        } else {
            ladoEsquerdo(a, meioAB, meioReta(meioAB, meioBC));
        }
        pontos.add(c);
        return c;
    }

    private Ponto ladoDireito(Ponto a, Ponto b, Ponto c) {
        pontos.add(a);
        Ponto meioAB, meioBC;
        meioAB = meioReta(a, b);
        meioBC = meioReta(b, c);
        if ((c.getX() == a.getX()) && (c.getY() == a.getY())) {
            pontos.add(a);
            return a;
        } else {
            ladoDireito(meioReta(meioAB, meioBC), meioBC, c);
        }
        return a;
    }

    public float calculaPT(float p1, float p4, float r1, float r4, float m) {
        float x = p1 * (2 * m * m * m - 3 * m * m + 1) + p4 * (-2 * m * m * m + 3 * m * m) + r1 * (m * m * m - 2 * m * m + m) + r4 * (m * m * m - m * m);
        return x;
    }

    public Poligono curvaHermite() {
        Poligono auxPol = new Poligono();
        float p1X = (float) this.getPontos().get(0).getX();
        float p1Y = (float) this.getPontos().get(0).getY();
        float p4X = (float) this.getPontos().get(3).getX();
        float p4Y = (float) this.getPontos().get(3).getY();

        float r1X = (float) (this.getPontos().get(1).getX() - p1X);
        float r1Y = (float) (this.getPontos().get(1).getY() - p1Y);
        float r4X = (float) (p4X - this.getPontos().get(2).getX());
        float r4Y = (float) (p4Y - this.getPontos().get(2).getY());

        for (float m = 0; m < 1; m = (float) (m + 0.01)) {
            float x;
            float y;
            x = calculaPT(p1X, p4X, r1X, r4X, m);
            y = calculaPT(p1Y, p4Y, r1Y, r4Y, m);
            System.out.println(x + " " + y);
            Ponto auxP = new Ponto((double) x, (double) y);
            auxPol.getPontos().add(auxP);
        }

        return auxPol;
    }

    public float calculaPTB(float p1, float p2, float p3, float p4, float m) {
        float x = (float) (p1 * (Math.pow(1 - m, 3)) + p2 * 3 * m * (Math.pow(1 - m, 2)) + 3 * m * m * p3 * (1 - m) + m * m * m * p4);
        return x;
    }

    public Poligono curvaBezier() {
        Poligono auxPol = new Poligono();
        float p1X = (float) this.getPontos().get(0).getX();
        float p1Y = (float) this.getPontos().get(0).getY();
        float p2X = (float) this.getPontos().get(1).getX();
        float p2Y = (float) this.getPontos().get(1).getY();
        float p3X = (float) this.getPontos().get(2).getX();
        float p3Y = (float) this.getPontos().get(2).getY();
        float p4X = (float) this.getPontos().get(3).getX();
        float p4Y = (float) this.getPontos().get(3).getY();

        for (float m = 0; m < 1; m = (float) (m + 0.01)) {
            float x;
            float y;
            x = calculaPTB(p1X, p2X, p3X, p4X, m);
            y = calculaPTB(p1Y, p2Y, p3Y, p4Y, m);
            System.out.println(x + " " + y);
            Ponto auxP = new Ponto((double) x, (double) y);
            auxPol.getPontos().add(auxP);
        }

        return auxPol;
    }

    public double calculaBSpline(double p1, double p2, double p3, double p4, double m) {
        double x = Math.pow(m, 3) * (-p1 / 6 + p2 / 2 - p3 / 2 + p4 / 6) + Math.pow(m, 2) * (p1 / 2 - p2 + p3 / 2) + m * (-p1 / 2 + p3 / 2) + p1 / 4 + 4 * p2 / 6 + p3 / 6;
        return x;
    }

    public Poligono bSpline() {
        Poligono auxPol = new Poligono();
        int i = getPontos().size();
        double p1X = this.getPontos().get(i - 4).getX();
        double p1Y = this.getPontos().get(i - 4).getY();
        double p2X = this.getPontos().get(i - 3).getX();
        double p2Y = this.getPontos().get(i - 3).getY();
        double p3X = this.getPontos().get(i - 2).getX();
        double p3Y = this.getPontos().get(i - 2).getY();
        double p4X = this.getPontos().get(i - 1).getX();
        double p4Y = this.getPontos().get(i - 1).getY();
        for (double k = 0; k <= 1; k = k + 0.01) {
            double x = calculaBSpline(p1X, p2X, p3X, p4X, k);
            double y = calculaBSpline(p1Y, p2Y, p3Y, p4Y, k);
            Ponto aux = new Ponto(x, y);
            auxPol.getPontos().add(aux);
        }

        return auxPol;
    }

    public double[][] matrizTranslacao(double dX, double dY, double dZ) {
        double trans[][] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {dX, dY, dZ, 1}};
        return trans;
    }

    public double[][] matrizEscalonamento(double sX, double sY, double sZ) {
        double escal[][] = {{sX, 0, 0, 0}, {0, sY, 0, 0}, {0, 0, sZ, 0}, {0, 0, 0, 1}};
        return escal;
    }

    public double[][] matrizRotacaox(double g) {
        return null;
    }

    public double[][] calculoHomogenia(double dX, double dY, double dZ, double sX, double sY, double sZ, double g) {
        double auxMatriz[][] = null;
        //escalonamento
        if (auxMatriz == null) {
            auxMatriz = matrizEscalonamento(sX, sY, sZ);
        }
        //translação
        auxMatriz = multiplicaMatriz(auxMatriz, matrizTranslacao(dX, dY, dZ));
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                System.out.println(auxMatriz[i][j]);
            }
        }
        return auxMatriz;
    }

    public void calculoH(double[][] matrizPrincipal) {
        Ponto3D aux;
        for (int i = 0; i < this.pontos.size(); i++) {
            aux = (Ponto3D) this.pontos.get(i);
            System.out.println(aux);
            double matrizPonto[][] = {{aux.getX(), aux.getY(), aux.getZ()}};
            double matrizAuxiliar[][] = multiplicaMatriz(matrizPonto, matrizPrincipal);
            aux.setX(matrizAuxiliar[0][0]);
            aux.setY(matrizAuxiliar[0][1]);
            aux.setZ(matrizAuxiliar[0][2]);
            this.pontos.get(i).setX(aux.getX());
            this.pontos.get(i).setY(aux.getY());
            //this.pontos3d.get(i).setZ(aux.getZ());
        }
    }

    public double[][] multiplicaMatriz(double matrizA[][], double matrizB[][]) {
        double c[][] = new double[4][4];

        for (int i = 0; i < matrizA.length; i++) { //Linha
            double aux = 0;
            for (int j = 0; j < matrizB[i].length; j++) { //Coluna 
                int ax = 0, ay = 0;
                for (int x = 0; x < matrizA[0].length; x++) {
                    aux = aux + (matrizA[i][x] * matrizB[x][j]);
                }
                c[i][j] = aux;
            }
        }
        return c;
    }
}
