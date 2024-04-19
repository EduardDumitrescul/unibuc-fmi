package lab3.animal;

import java.util.Objects;

public class Duck extends Bird{
    private int length;
    public Duck(int noOfLegs, String name, String color, int length) {
        super(name, noOfLegs, color);
        this.length = length;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Duck duck = (Duck) o;
        return length == duck.length;
    }

    @Override
    public int hashCode() {
        return Objects.hash(length);
    }

    @Override
    public void move() {
        System.out.println("I can swim");
    }

    public void sing() {
        System.out.println("I can quack");
    }
}
