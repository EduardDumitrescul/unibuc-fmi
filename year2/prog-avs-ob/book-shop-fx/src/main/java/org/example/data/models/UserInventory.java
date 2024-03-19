package org.example.data.models;

import java.util.List;

public class UserInventory implements Cloneable {
    private int id;

    private List<Item> items;

    public UserInventory(int id, List<Item> items) {
        this.id = id;
        this.items = items;
    }

    public UserInventory(UserInventory obj) {
        this.id = obj.id;
        this.items = obj.items;
    }


    @Override
    public Cloneable clone() {
        return new UserInventory(this);
    }
}
