package lab3.animal;

public class Animal {
    public String name;
    private int noOfLegs;

    public Animal(String name, int noOfLegs) {
        this.name = name;
        this.noOfLegs = noOfLegs;
    }

    public Animal() {

    }

    public void move() {
        System.out.printf("I can move");
    }
    public void eat() {
        System.out.println("Animal eat()");
    }

    public void eat(String food) {
        System.out.println("Animal eat(" + food + ")");
    }

    public int getNoOfLegs() {
        return noOfLegs;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setNoOfLegs(int noOfLegs) {
        this.noOfLegs = noOfLegs;
    }
}

