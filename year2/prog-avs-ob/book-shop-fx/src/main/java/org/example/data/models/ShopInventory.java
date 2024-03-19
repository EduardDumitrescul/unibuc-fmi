package org.example.data.models;

import java.util.ArrayList;
import java.util.List;

public class ShopInventory implements Cloneable {
    private int id;
    private List<InventoryItem> items;

    public ShopInventory(int id, List<InventoryItem>items) {
        this.items = cloneItemList(items);
        this.id = id;
    }

    public ShopInventory(ShopInventory obj) {
        this.items = cloneItemList(obj.getItems());
        this.id = obj.getId();
    }

    private List<InventoryItem> cloneItemList(List<InventoryItem>items) {
        List<InventoryItem> list = new ArrayList<>();
        for(InventoryItem item: items) {
            list.add(new InventoryItem(item));
        }
        return list;
    }

    public int getId() {
        return id;
    }

    public List<InventoryItem> getItems() {
        return items;
    }

    @Override
    public ShopInventory clone() {
        return new ShopInventory(this);
    }
}
