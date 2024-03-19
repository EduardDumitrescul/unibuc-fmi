package org.example.data.models;

public class Shop implements Cloneable {
    private int id;
    private int openingHour;
    private int closingHour;
    private String location;
    private int itemsSold;
    private int dollarsReceived;

    private ShopInventory inventory;

    public Shop(
            int id,
            int openingHour,
            int closingHour,
            String location,
            int itemsSold,
            int dollarsReceived,
            ShopInventory inventory
    ) {
        this.id = id;
        this.closingHour = closingHour;
        this.openingHour = openingHour;
        this.location = location;
        this.itemsSold = itemsSold;
        this.dollarsReceived = dollarsReceived;
        this.inventory = new ShopInventory(inventory);
    }

    public Shop(Shop obj) {
        this.id = obj.id;
        this.location = obj.location;
        this.itemsSold = obj.itemsSold;
        this.openingHour = obj.openingHour;
        this.dollarsReceived = obj.dollarsReceived;
        this.closingHour = obj.closingHour;
        this.inventory = new ShopInventory(obj.inventory);
    }

    public int getId() {
        return id;
    }

    public int getClosingHour() {
        return closingHour;
    }

    public int getDollarsReceived() {
        return dollarsReceived;
    }

    public int getItemsSold() {
        return itemsSold;
    }

    public int getOpeningHour() {
        return openingHour;
    }

    public ShopInventory getInventory() {
        return new ShopInventory(inventory);
    }

    public String getLocation() {
        return location;
    }

    @Override
    public Shop clone() {
        return new Shop(this);
    }
}
