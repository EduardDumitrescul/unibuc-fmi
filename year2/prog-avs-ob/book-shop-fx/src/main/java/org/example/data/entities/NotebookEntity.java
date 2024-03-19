package org.example.data.entities;

public class NotebookEntity extends BaseEntity{
    public String type;
    public int numberOfPages;
    public int numberOfPagesWritten;

    public NotebookEntity(int id, String type, int numberOfPages, int numberOfPagesWritten) {
        super(id);
        this.type = type;
        this.numberOfPages = numberOfPages;
        this.numberOfPagesWritten = numberOfPagesWritten;
    }

    public NotebookEntity(NotebookEntity obj) {
        super(obj);
        this.type = obj.type;
        this.numberOfPages = obj.numberOfPages;
        this.numberOfPagesWritten = obj.numberOfPagesWritten;
    }

    @Override
    public NotebookEntity clone() {
        return new NotebookEntity(this);
    }
}
