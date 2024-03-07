package lab2;

import java.util.List;
import java.util.Scanner;

public class ReadFromKeyboard {
    private boolean running = true;
    private final Scanner input = new Scanner(System.in);
    public void run() {
        running = true;
        while(running) {
            System.out.print("Enter Command >>> ");
            String command = input.next();
            System.out.println("Command received: " + command);

            switch(command) {
                case "read" -> read();
                case "quit" -> quit();
                case "help" -> help();
                case "update" -> update();
                case "get" -> get();
                case "delete" -> delete();
                default -> System.out.println("Unknown Command!");
            }
        }
    }

    private void read() {
        List<Person> persoane  = DataStorage.getAll();
        for(Person p: persoane) {
            System.out.println(p.getUsername() + " " + p.getSold());
        }
    }

    private void get() {
        String username = requireUsername();
        Person p = DataStorage.get(username);
        if (p == null) {
            System.out.println("User " + username + " does not exist");
        }
        else {
            System.out.println("User " + username + " has sold" + p.getSold());
        }
    }

    private String requireUsername() {
        System.out.print("Username: >>> ");
        return input.next();
    }

    private void delete() {
        String username = requireUsername();
        DataStorage.delete(username);
        System.out.println("Deleted info for user " + username);
    }

    private void update() {
        String username = requireUsername();
        System.out.print("Sold: >>> ");
        int sold = input.nextInt();

        DataStorage.update(username, sold);
        System.out.println("The sold was updated for user " + username + " " + sold);
    }

    private void help() {
        System.out.println("""
                Accepted commands:
                \t\thelp: Instructions on how to use the application
                \t\tget: Get sold. Receives username as parameter.
                \t\tupdate: Update data. Can receive two parameters: username and sold.
                \t\tdelete: Delete the user's data.  Receive the username.
                \t\tquit: Close the application.""");
    }

    private void quit() {
        running = false;
        System.out.println("Closing the application");
    }
}
