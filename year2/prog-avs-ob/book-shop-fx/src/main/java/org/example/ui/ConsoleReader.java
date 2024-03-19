package org.example.ui;

import java.util.Scanner;

abstract class ConsoleReader {
    private static final Scanner scanner = new Scanner(System.in);
    public static String readLine() {
        return scanner.nextLine();
    }
}
