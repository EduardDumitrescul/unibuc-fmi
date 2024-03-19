package org.example.data.repositories;

import org.example.data.entities.ItemEntity;
import org.example.utils.ObjectCloningUtil;

import java.util.ArrayList;
import java.util.List;

public class ItemRepository {
    private List<ItemEntity> items = new ArrayList<>();

    public List<ItemEntity> getById(List<Integer> ids) {
        List<ItemEntity> list = new ArrayList<>();
        for(ItemEntity entity: items) {
            if(ids.contains(entity.getId())) {
                list.add(new ItemEntity(entity));
            }
        }
        return list;
    }

    public ItemEntity getById(int id) {
        for(ItemEntity entity: items) {
            if(entity.getId() == id) {
                return entity;
            }
        }
        return null;
    }

    public List<ItemEntity> getAll() {
        return ObjectCloningUtil.cloneList(items);
    }

    public int addItem(ItemEntity entity) {
        generateId(entity);
        items.add(new ItemEntity(entity));
        return entity.id;
    }

    private static int idCount = 0;
    private void generateId(ItemEntity entity) {
        idCount ++;
        entity.id = idCount;
    }

    private static ItemRepository instance = null;

    private ItemRepository() {}

    public static ItemRepository getInstance()   {
        if(instance == null) {
            instance = new ItemRepository();
        }
        return instance;
    }
}
