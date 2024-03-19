package org.example.data.entities;

import java.util.Objects;

public class InventoryItemCrossRef implements Cloneable {
    public int itemId;
    public int inventoryId;

    public int count;

    public InventoryItemCrossRef(
            int inventoryId,
            int itemId,
            int count
    ) {
        this.inventoryId = inventoryId;
        this.itemId = itemId;
        this.count = count;
    }

    public InventoryItemCrossRef(InventoryItemCrossRef obj) {
        this.itemId = obj.itemId;
        this.inventoryId = obj.inventoryId;
        this.count = obj.count;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        InventoryItemCrossRef that = (InventoryItemCrossRef) o;
        return itemId == that.itemId && inventoryId == that.inventoryId;
    }

    @Override
    public int hashCode() {
        return Objects.hash(itemId, inventoryId);
    }

    @Override
    public InventoryItemCrossRef clone() {
        return new InventoryItemCrossRef(this);
    }

    public int getInventoryId() {
        return inventoryId;
    }

    public int getItemId() {
        return itemId;
    }
}
