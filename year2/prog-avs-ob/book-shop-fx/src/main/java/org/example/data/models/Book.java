package org.example.data.models;

public class Book extends Item implements Cloneable {
    private String title;
    private String author;
    private int numberOfPages;
    private int numberOfPagesRead;


    public Book(int id, int price, String title, String author, int numberOfPages, int numberOfPagesRead) {
        super(id, price);
        this.title = title;
        this.author = author;
        this.numberOfPages = numberOfPages;
        this.numberOfPagesRead = numberOfPagesRead;
    }

    public Book(Book obj) {
        super(obj);
        this.title = obj.title;
        this.author = obj.author;
        this.numberOfPages = obj.numberOfPages;
        this.numberOfPagesRead = obj.numberOfPagesRead;
    }

    void read() throws Exception {
        if(numberOfPagesRead >= numberOfPages) {
            throw new Exception("You've already read this book");
        }
        numberOfPagesRead ++;
    }

    @Override
    public Book clone() {
        return new Book(this);
    }
}
