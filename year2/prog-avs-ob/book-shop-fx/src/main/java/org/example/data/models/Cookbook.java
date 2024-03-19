package org.example.data.models;

public class Cookbook extends Item implements Cloneable {
    private String skillLevel;
    private int numberOfRecipes;
    private int numberOfRecipesTried;


    public Cookbook(int id, int price, String skillLevel, int numberOfRecipes, int numberOfRecipesTried) {
        super(id, price);
        this.skillLevel = skillLevel;
        this.numberOfRecipes = numberOfRecipes;
        this.numberOfRecipesTried = numberOfRecipesTried;
    }

    public Cookbook(Cookbook obj) {
        super(obj);
        this.skillLevel = obj.skillLevel;
        this.numberOfRecipes = obj.numberOfRecipes;
        this.numberOfRecipesTried = obj.numberOfRecipesTried;
    }

    public void cook() throws Exception {
        if(numberOfRecipesTried >= numberOfRecipes) {
            throw new Exception("You have tried all the recipes in this cookbook");
        }
        numberOfRecipesTried += 1;
    }

    @Override
    public Cookbook clone() {
        return new Cookbook(this);
    }
}
