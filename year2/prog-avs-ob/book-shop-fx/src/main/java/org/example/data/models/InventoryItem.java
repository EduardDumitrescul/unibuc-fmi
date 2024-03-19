package org.example.data.models;

public class InventoryItem implements Cloneable {
    private Item item;
    private int count;

    public InventoryItem(Item item, int count) {
        this.item = new Item(item);
        this.count = count;
    }

    public InventoryItem(InventoryItem obj) {
        this.item = new Item(obj.item);
        this.count = obj.count;
    }


    @Override
    public Cloneable clone() {
        return new InventoryItem(this);
    }
}
