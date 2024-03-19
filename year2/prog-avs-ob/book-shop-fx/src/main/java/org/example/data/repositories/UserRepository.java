package org.example.data.repositories;

import org.example.data.entities.UserEntity;

import java.util.ArrayList;
import java.util.Objects;

public class UserRepository {
    private static UserRepository instance = null;
    private static int idCount = 0;
    private ArrayList <UserEntity> users = new ArrayList<>();

    private UserRepository() {}


    public UserEntity getUser(int id) {
        for(UserEntity entity: users) {
            if(entity.id == id) {
                return entity.clone();
            }
        }
        return null;
    }

    public boolean usernameExists(String username) {
        for(UserEntity user: users) {
            if(Objects.equals(user.username, username)) {
                return true;
            }
        }
        return false;
    }


    public int add(UserEntity user) {
        generateId(user);
        users.add(user);
        return user.id;
    }


    public UserEntity findUserByUsername(String username) {
        for(UserEntity user: users) {
            if(Objects.equals(user.username, username)) {
                return user;
            }
        }
        return null;
    }

    public void generateId(UserEntity user) {
        idCount ++;
        user.setId(idCount);
    }

    public static UserRepository getInstance() {
        if(instance == null) {
            instance = new UserRepository();
        }
        return instance;
    }
}
