package org.example.data.models;

public class User implements Cloneable {
    private int id;
    private String username;
    private String password;

    private UserInventory inventory;

    public User(int id, String username, String password, UserInventory inventory) {
        this.id = id;
        this.password = password;
        this.username = username;
        this.inventory = inventory;
    }

    public User(User obj) {
        this.id = obj.id;
        this.username = obj.username;
        this.password = obj.password;
        this.inventory = obj.inventory;
    }

    public int getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getPassword() {
        return password;
    }

    @Override
    public Cloneable clone() {
        return new User(this);
    }
}
