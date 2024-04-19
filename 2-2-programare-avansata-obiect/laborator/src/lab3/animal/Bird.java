package lab3.animal;

public class Bird extends Animal {

    private String color;
    public Bird(String name, int noOfLegs, String color) {
        super(name, noOfLegs);
        this.color = color;
    }

    @Override
    public void move() {
        System.out.println("I can fly!");
    }

    public void sing() {
        System.out.println("I can sing");
    }
}
