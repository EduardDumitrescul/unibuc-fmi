package org.example.data.entities;

public class ColoringBookEntity extends BaseEntity implements Cloneable {
    public String theme;
    public int numberOfDrawings;
    public int numberOfDrawingCompleted;

    public ColoringBookEntity(int id, String theme, int numberOfDrawings, int numberOfDrawingCompleted) {
        super(id);
        this.theme = theme;
        this.numberOfDrawings = numberOfDrawings;
        this.numberOfDrawingCompleted = numberOfDrawingCompleted;
    }

    public ColoringBookEntity(ColoringBookEntity obj) {
        super(obj.id);
        this.theme = obj.theme;
        this.numberOfDrawings = obj.numberOfDrawings;
        this.numberOfDrawingCompleted = obj.numberOfDrawingCompleted;
    }

    @Override
    public ColoringBookEntity clone() {
        return new ColoringBookEntity(this);
    }
}
