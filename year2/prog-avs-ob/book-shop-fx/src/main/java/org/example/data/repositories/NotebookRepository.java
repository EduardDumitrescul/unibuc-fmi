package org.example.data.repositories;

import org.example.data.entities.NotebookEntity;

public class NotebookRepository extends Repository<NotebookEntity> {

    private NotebookRepository() {}
    private static NotebookRepository instance = null;
    public static NotebookRepository getInstance() {
        if(instance == null) {
            instance = new NotebookRepository();
        }
        return instance;
    }
}
