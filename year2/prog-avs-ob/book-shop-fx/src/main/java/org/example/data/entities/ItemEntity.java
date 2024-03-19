package org.example.data.entities;

import org.example.data.models.Item;

public class ItemEntity implements Cloneable {
    public int id;
    public int price;

    public ItemEntity(
            int id,
            int price
    ) {
        this.id  = id;
        this.price = price;
    }

    public ItemEntity(ItemEntity obj) {
        this.id = obj.id;
        this.price = obj.price;
    }

    public ItemEntity() {}

    @Override
    public ItemEntity clone() {
        return new ItemEntity(this);
    }

    public int getId() {
        return id;
    }

    public int getPrice() {
        return price;
    }

    public Item asItem() {
        return new Item(this.id, this.price);
    }


}
