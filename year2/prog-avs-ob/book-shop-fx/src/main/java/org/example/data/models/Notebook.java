package org.example.data.models;


public class Notebook extends Item {
    private String type;
    private int numberOfPages;
    private int numberOfPagesWritten;

    public Notebook(int id, int price, String type, int numberOfPages, int numberOfPagesWritten) {
        super(id, price);
        this.type = type;
        this.numberOfPages = numberOfPages;
        this.numberOfPagesWritten = numberOfPagesWritten;
    }

    public Notebook(Notebook obj) {
        super(obj);
        this.type = obj.type;
        this.numberOfPages = obj.numberOfPages;
        this.numberOfPagesWritten = obj.numberOfPagesWritten;
    }

    public void write() throws Exception {
        if(numberOfPagesWritten >= numberOfPages) {
            throw new Exception("This notebook is already full");
        }
        numberOfPagesWritten += 1;
    }

    @Override
    public Item clone() {
        return new Notebook(this);
    }
}
