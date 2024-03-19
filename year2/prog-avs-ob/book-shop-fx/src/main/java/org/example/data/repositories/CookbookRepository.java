package org.example.data.repositories;

import org.example.data.entities.CookbookEntity;

public class CookbookRepository extends Repository<CookbookEntity> {


    private CookbookRepository() {
        super();
    }
    private static CookbookRepository instance = null;

    public static CookbookRepository getInstance() {
        if(instance == null) {
            instance = new CookbookRepository();
        }
        return instance;
    }
}
