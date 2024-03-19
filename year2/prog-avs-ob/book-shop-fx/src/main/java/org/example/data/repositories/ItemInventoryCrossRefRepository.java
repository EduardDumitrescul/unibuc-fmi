package org.example.data.repositories;

import org.example.data.entities.InventoryItemCrossRef;

import java.util.ArrayList;
import java.util.List;

public class ItemInventoryCrossRefRepository {
    private List<InventoryItemCrossRef> crossRefs = new ArrayList<>();

    public InventoryItemCrossRef getInventoryItem(int inventoryId, int itemId) {
        for(InventoryItemCrossRef entity: crossRefs) {
            if(entity.equals(new InventoryItemCrossRef(inventoryId, itemId, 0))) {
                return entity.clone();
            }
        }
        return null;
    }

    public void update(InventoryItemCrossRef inventoryItemCrossRef) {
        int index = crossRefs.indexOf(inventoryItemCrossRef);
        crossRefs.set(index, new InventoryItemCrossRef(inventoryItemCrossRef));
    }

    public List<InventoryItemCrossRef> getItemsByInventoryId(int inventoryId) {
        List<InventoryItemCrossRef> list = new ArrayList<>();
        for(InventoryItemCrossRef entity: crossRefs) {
            if(entity.getInventoryId() == inventoryId) {
                list.add(entity.clone());
            }
        }
        return list;
    }

    public void add(InventoryItemCrossRef inventoryItemCrossRef) {
        crossRefs.add(new InventoryItemCrossRef(inventoryItemCrossRef));
    }

    public void delete(InventoryItemCrossRef inventoryItemCrossRef) {
        crossRefs.remove(inventoryItemCrossRef);
    }

    private ItemInventoryCrossRefRepository() {}
    private static ItemInventoryCrossRefRepository instance;

    public static ItemInventoryCrossRefRepository getInstance() {
        if(instance == null) {
            instance = new ItemInventoryCrossRefRepository();
        }
        return instance;
    }
}
