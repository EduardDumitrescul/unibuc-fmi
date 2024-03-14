package lab3.test;

import lab3.animal.Animal;
import lab3.animal.Ape;

public class TestInheritance {

    public static void main(String[] args) {
        Animal animal = new Animal("dog", 4);
        animal.move();

        Ape ape = new Ape(2, "gorilla", "big");
        ape.move();
    }

}