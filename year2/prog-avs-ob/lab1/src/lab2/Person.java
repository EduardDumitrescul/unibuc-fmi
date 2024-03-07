package lab2;

public class Person {
    private final String username;
    private int sold;

    Person(String username, int sold) {
        this.username = username;
        this.sold = sold;
    }

    public String getUsername() {
        return username;
    }

    public void setSold(int sold) {
        this.sold = sold;
    }

    public int getSold() {
        return sold;
    }
}
