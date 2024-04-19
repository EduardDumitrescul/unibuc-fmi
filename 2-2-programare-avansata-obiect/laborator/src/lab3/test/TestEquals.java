package lab3.test;

import lab3.animal.Duck;
import lab3.animal.Ape;

public class TestEquals {
    public static void main(String[] args) {

        //.equals() not overridden
        Ape ape1 = new Ape(2, "gorilla", "big");
        Ape ape2 = new Ape(2, "gorilla", "big");
        if (ape1.equals(ape2)) {
            System.out.println("Ape1 == Ape2");
        } else {
            System.out.println("Ape1 != Ape2");
        }

        //.equals() overridden
        Duck duck1 = new Duck(2, "Pekin", "white", 32);
        Duck duck2 = new Duck(2, "Pekin", "white", 32);
        if (duck1.equals(duck2)) {
            System.out.println("Duck1 == Duck2");
        } else {
            System.out.println("Duck1 != Duck2");
        }

        Ape ape3 = ape1;

        if (ape1.equals(ape3)) {
            System.out.println("Ape1 == Ape3");
        } else {
            System.out.println("Ape1 != Ape3");
        }

        if (ape1 == ape3) {
            System.out.println("Ape1 == Ape3");
        } else {
            System.out.println("Ape1 != Ape3");
        }

    }
}