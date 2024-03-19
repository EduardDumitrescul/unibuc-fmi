package org.example.data.entities;

public class CookbookEntity  extends BaseEntity{
    public String skillLevel;
    public int numberOfRecipes;
    public int numberOfRecopesTried;

    public CookbookEntity(int id, String skillLevel, int numberOfRecipes, int numberOfRecopesTried) {
        super(id);
        this.skillLevel = skillLevel;
        this.numberOfRecipes =numberOfRecipes;
        this.numberOfRecopesTried = numberOfRecopesTried;
    }

    public CookbookEntity(CookbookEntity obj) {
        super(obj);
        this.skillLevel = obj.skillLevel;
        this.numberOfRecipes =obj.numberOfRecipes;
        this.numberOfRecopesTried = obj.numberOfRecopesTried;
    }



    public CookbookEntity(BaseEntity obj) {
        super(obj);
    }


    @Override
    public CookbookEntity clone() {
        return new CookbookEntity(this);
    }
}
