package lab5.interfaces.ex2.persoane;

public interface Adult extends Persoana {
    @Override
    default boolean eMajor() {
        return true;
    }
}
