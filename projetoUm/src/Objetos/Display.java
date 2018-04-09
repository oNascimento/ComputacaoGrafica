/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Objetos;

import java.util.ArrayList;

/**
 *
 * @author ivofi
 */
public class Display{
    public ArrayList<Poligono> poligonos;

    public Display(ArrayList<Poligono> poligonos) {
        this.poligonos = poligonos;
    }
    
    @Override
    public String toString() {
        return "" + poligonos ;
    }
    
    public Display(){
        poligonos = new ArrayList<Poligono>();
    }

    public ArrayList<Poligono> getPoligonos() {
        return poligonos;
    }

    public void setPoligonos(ArrayList<Poligono> poligonos) {
        this.poligonos = poligonos;
    }
    
}
