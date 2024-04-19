package lab3.test;


import lab3.animal.Animal;
import lab3.animal.Bird;
import lab3.animal.Ape;

public class TestPolymorphism {
    public static void main(String[] args) {
        Animal a1 = new Animal();
        Animal a2 = new Ape(2, "gorilla", "big");
        Animal a3 = new Bird("sparrow", 2, "gray");

        moveAndEat(a1);
        moveAndEat(a2);
        moveAndEat(a3);
    }

    public static void moveAndEat(Animal animal) {
        animal.move();
        animal.eat();
    }
}