package org.example.services;

import org.example.data.Seeder;
import org.example.data.entities.UserEntity;
import org.example.data.models.User;
import org.example.data.repositories.UserRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class UserServiceTest {
    private UserRepository userRepository = UserRepository.getInstance();
    private UserService userService = UserService.getInstance();

    private String mockUsername = "account service test username";
    private String mockPassword = "account service test password";

    @BeforeEach
    public void setUp() {
        Seeder.seed();
    }

    @Test
    void isUnique() {
        UserEntity user = new UserEntity(1, "John", "Pass", 1);

        assertTrue(userService.isUnique(user.username));
        userRepository.add(user);
        assertFalse(userService.isUnique(user.username));
    }

    @Test
    void register(){
        String username = "register";
        String password = "pass";
        assertDoesNotThrow(() -> userService.register(username, password));
        assertThrows(Exception.class, () -> userService.register(username, password));

    }

    @Test
    void login() {
        UserEntity user = new UserEntity(0, "login", "login", 1);
        assertThrows(Exception.class, () -> userService.login(user.username, user.password));
        userRepository.add(user);
        assertDoesNotThrow(() -> userService.login(user.username, user.password));
        assertTrue(userService.isLoggedIn());
    }

    @Test
    void userLoggedAfterRegister() {
        assertDoesNotThrow(() -> userService.register(mockUsername, mockPassword));
        assertTrue(userService.isLoggedIn());
    }

    @Test
    void getUserTest() {
        User user = userService.getUserById(1);
        System.out.println(user.toString());
    }

}