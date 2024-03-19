package org.example.data.models;

public class Item implements Cloneable {
    private int id;
    private int price;

    public Item(int id, int price) {
        this.id = id;
        this.price = price;
    }

    public Item(Item obj) {
        this.id = obj.id;
        this.price = obj.price;
    }

    public int getId() {
        return id;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public Item clone() {
        return new Item(this);
    }
}
