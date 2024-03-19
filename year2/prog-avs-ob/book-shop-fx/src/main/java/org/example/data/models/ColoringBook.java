package org.example.data.models;

public class ColoringBook extends Item implements Cloneable {
    private String theme;
    private int numberOfDrawings;
    private int numberOfDrawingsCompleted;


    public ColoringBook(int id, int price, String theme, int numberOfDrawings, int numberOfDrawingsCompleted) {
        super(id, price);
        this.theme = theme;
        this.numberOfDrawings = numberOfDrawings;
        this.numberOfDrawingsCompleted = numberOfDrawingsCompleted;
    }

    public ColoringBook(ColoringBook obj) {
        super(obj);
        this.theme = obj.theme;
        this.numberOfDrawings = obj.numberOfDrawings;
        this.numberOfDrawingsCompleted = obj.numberOfDrawingsCompleted;
    }

    void draw() throws Exception {
        if(numberOfDrawingsCompleted >= numberOfDrawings) {
            throw new Exception("You have drawn all the drawings in this drawing book");
        }
        numberOfDrawingsCompleted += 1;
    }

    @Override
    public ColoringBook clone() {
        return new ColoringBook(this);
    }
}
