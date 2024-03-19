package org.example.data.repositories;

import org.example.data.entities.BaseEntity;

import java.util.ArrayList;
import java.util.List;

public abstract class Repository<T extends BaseEntity> {
    private List<T> entities = new ArrayList<>();

    public int add(T entity) {
        generateId(entity);
        entities.add((T) entity.clone());
        return entity.id;
    }

    public boolean exists(int id) {
        for(T entity: entities) {
            if(entity.id == id) {
                return true;
            }
        }
        return false;
    }

    public T getById(int id) {
        for(T entity: entities) {
            if(entity.id == id) {
                return (T) entity.clone();
            }
        }
        return null;
    }

    public void update(T entity) {
        int index = entities.indexOf(entity);
        entities.set(index, (T) entity.clone());
    }

    public void delete(T entity) {
        entities.remove(entity);
    }

    private static int idCount = 0;
    private void generateId(T entity) {
        idCount ++;
        entity.id = idCount;
    }
    protected Repository() {}

    public static Repository getInstance() {
        return null;
    }
}
