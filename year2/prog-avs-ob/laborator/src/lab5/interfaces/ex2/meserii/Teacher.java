package lab5.interfaces.ex2.meserii;

public interface Teacher extends Worker{
    default void work() {
        System.out.println("Teaching...");
    }
}
