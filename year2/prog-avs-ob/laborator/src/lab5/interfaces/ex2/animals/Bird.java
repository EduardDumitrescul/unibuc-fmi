package lab5.interfaces.ex2.animals;

public interface Bird extends BaseAnimal {

    default boolean hasFeathers() {
        return true;
    }
}
