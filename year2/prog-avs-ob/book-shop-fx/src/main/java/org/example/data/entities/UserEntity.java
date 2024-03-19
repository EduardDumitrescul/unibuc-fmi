package org.example.data.entities;

public class UserEntity implements Cloneable {
    public int id;
    public String username;
    public String password;

    public int inventoryId;

    public UserEntity(int id, String username, String password, int inventoryId) {
        this.id  = id;
        this.username = username;
        this.password = password;
        this.inventoryId = inventoryId;
    }

    public UserEntity(UserEntity obj) {
        this.id = obj.id;
        this.username = obj.username;
        this.password = obj.password;
        this.inventoryId = obj.inventoryId;
    }


    @Override
    public UserEntity clone() {
        return new UserEntity(this);
    }

    public void setId(int id) {
        this.id = id;
    }
}
