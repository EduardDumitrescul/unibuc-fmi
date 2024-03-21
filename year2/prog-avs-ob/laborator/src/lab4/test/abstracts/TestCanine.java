package lab4.test.abstracts;

import lab4.abstracts.Canine;
import lab4.abstracts.Wolf;

public class TestCanine {
    public static void main(String[] args) {
        //Canine canine = new Canine(); // 'Canine' is abstract; cannot be instantiated
        Canine canine = new Wolf(); // initialisation through subclass constructor
        canine.makeSound();
    }
}
