package lab5.test.ex1;

import lab5.interfaces.ex1.Animal;
import lab5.interfaces.ex1.Cat;
import lab5.interfaces.ex1.Chicken;

public class TestEx1 {

    public static void main(String[] args) {
        Cat cat = new Cat();
        System.out.println("I am a " + cat.getName());
        cat.eat();
        cat.printNoOfLegs();

        Chicken chicken = new Chicken();
        System.out.println("I am a " + chicken.getName());
        chicken.eat();
        chicken.printNoOfLegs();

        //static method from interface call
        Animal.makeNoise();
    }
}
