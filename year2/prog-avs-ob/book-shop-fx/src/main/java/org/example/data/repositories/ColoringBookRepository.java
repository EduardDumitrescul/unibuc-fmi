package org.example.data.repositories;

import org.example.data.entities.ColoringBookEntity;

public class ColoringBookRepository extends Repository<ColoringBookEntity> {

    private ColoringBookRepository() {
        super();
    }

    private static ColoringBookRepository instance = null;
    public static ColoringBookRepository getInstance() {
        if(instance == null) {
            instance = new ColoringBookRepository();
        }
        return instance;
    }
}
