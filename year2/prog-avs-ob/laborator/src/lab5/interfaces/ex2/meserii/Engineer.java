package lab5.interfaces.ex2.meserii;

public interface Engineer extends Worker {
    default void work() {
        System.out.println("Coding...");
    }
}
