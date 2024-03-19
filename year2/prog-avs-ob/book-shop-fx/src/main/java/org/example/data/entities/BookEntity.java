package org.example.data.entities;

public class BookEntity extends BaseEntity implements Cloneable {
    public String title;
    public String author;

    public int numberOfPages;
    public int numberOfPagesRead;

    public BookEntity(int id, String title, String author, int numberOfPages, int numberOfPagesRead) {
        super(id);
        this.title = title;
        this.author = author;
        this.numberOfPages = numberOfPages;
        this.numberOfPagesRead = numberOfPagesRead;
    }

    public BookEntity(BookEntity obj) {
        super(obj.id);
        this.title = obj.title;
        this.author = obj.author;
        this.numberOfPages = obj.numberOfPages;
        this.numberOfPagesRead = obj.numberOfPagesRead;
    }

    @Override
    public BookEntity clone() {
        return new BookEntity(this);
    }
}
