package lab2;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class DataStorage {
    static List<Person> persoane = new ArrayList<>();

    static List<Person> getAll() {
        return persoane;
    }

    static Person get(String username) {
        for(Person p: persoane) {
            if(Objects.equals(p.getUsername(), username)) {
                return p;
            }
        }
        return null;
    }
    static void create(String username, int sold) {
        persoane.add(new Person(username, sold));
    }
    static void update(String username, int sold) {
        Person p = get(username);
        if(p == null) {
            create(username, sold);
        }
        else {
            p.setSold(sold);
        }
    }

    static void delete(String username) {
        persoane.remove(get(username));
    }
}
