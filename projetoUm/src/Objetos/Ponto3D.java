/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Objetos;

/**
 *
 * @author onascimento
 */
public class Ponto3D extends Ponto{
    public double z;

    public Ponto3D() {
        super.setX(0);
        super.setY(0);
        z = 0;
    }

    public Ponto3D(double z) {
        this.z = z;
    }

    public Ponto3D(Ponto p, double z) {
        super(p.getX(), p.getY());
        this.z = z;
    }

    public void setZ(double z) {
        this.z = z;
    }

    public double getZ() {
        return z;
    }
}
