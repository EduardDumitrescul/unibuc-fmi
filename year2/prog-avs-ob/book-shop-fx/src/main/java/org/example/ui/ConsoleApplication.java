package org.example.ui;

import org.example.services.UserService;

import static org.example.ui.ConsoleWriter.writeLine;

public class ConsoleApplication {
    private static boolean isRunning = false;
    private static final UserService userService = UserService.getInstance();

    private ConsoleApplication() {}

    public static void show() {
        if (userService.isLoggedIn()) {
            writeLine("You are logged in");
        } else {
            LoginScreen.show();
        }
    }
}
