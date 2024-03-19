package org.example.data.repositories;

import org.example.data.entities.BookEntity;

public class BookRepository extends Repository<BookEntity> {

    private BookRepository() {}

    private static BookRepository instance = null;
    public static BookRepository getInstance() {
        if(instance == null) {
            instance = new BookRepository();
        }
        return instance;
    }
}
