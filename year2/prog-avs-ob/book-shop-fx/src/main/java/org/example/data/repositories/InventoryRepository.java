package org.example.data.repositories;

import org.example.data.entities.InventoryEntity;

import java.util.ArrayList;
import java.util.List;

public class InventoryRepository {
    private List<InventoryEntity> inventories = new ArrayList<>();

    public int add(InventoryEntity entity) {
        generateId(entity);
        inventories.add(entity.clone());
        return entity.id;
    }


    public InventoryEntity getById(int id) {
        for(InventoryEntity entity: inventories) {
            if(entity.getId() == id) {
                return new InventoryEntity(entity);
            }
        }
        return null;
    }

    private static int idCount = 0;
    private void generateId(InventoryEntity entity) {
        idCount ++;
        entity.id = idCount;
    }


    private InventoryRepository() {}

    private static InventoryRepository instance = null;

    public static InventoryRepository getInstance() {
        if(instance == null) {
            instance = new InventoryRepository();
        }
        return instance;
    }
}

