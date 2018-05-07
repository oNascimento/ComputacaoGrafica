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
    public int z;

    public Ponto3D() {
        super.setX(0);
        super.setY(0);
        z = 0;
    }

    public void setZ(int z) {
        this.z = z;
    }
}
