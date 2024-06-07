package org.example.examen2024seria25;

/*
1. D
2. C
3. B
4. A
5. C
 */

//interface Functie {
//    int f(double x);
//    default boolean eval(double x) {return f(x)==x;}
//}
//
//class Test {
//    Functie functie;
//    public Test(Functie functie) {
//        this.functie = functie;
//    }
//    public boolean eval(double x) {return functie.f(x) == x;}
//}
//
//public class Main {
//    public static void main(String[] args) {
//        boolean b = new Test(x -> 10).eval(10); // OK
//        boolean b2 = new Test(x -> x/100).eval(10); // ERR
//
//        boolean b3 = new Functie() {
//            @Override
//            public int f(double x) {
//                return (int)(x/10);
//            }
//        }.eval(10); // OK
//    }
//}

import org.w3c.dom.css.Counter;
import org.w3c.dom.ls.LSOutput;

import java.io.File;
import java.text.FieldPosition;
import java.util.Scanner;

class EX2 {
    public static void main(String[] args) {
        // Presupunem că lista 'list' este inițializată undeva în cod cu obiecte de tip 'Jucator'
        List<Jucator> list = new ArrayList<>();
        // Populare exemplificativă a listei
        list.add(new Jucator("Ion", "RO", 15, 3500));
        list.add(new Jucator("Maria", "US", 8, 5000));
        list.add(new Jucator("John", "UK", 12, 3000));
        list.add(new Jucator("Ana", "RO", 20, 1000));

        // 1. Afișați jucătorii de tenis care au participat la cel puțin 10 turnee, sortați alfabetic după nume
        System.out.println("Jucătorii care au participat la cel puțin 10 turnee, sortați alfabetic după nume:");
        list.stream()
                .filter(j -> j.getNrTurneeATP() >= 10)
                .sorted(Comparator.comparing(Jucator::getNume))
                .forEach(System.out::println);

        // 2. Afișați naționalitățile distincte
        System.out.println("\nNaționalitățile distincte:");
        list.stream()
                .map(Jucator::getNationalitate)
                .distinct()
                .forEach(System.out::println);

        // 3. Creați o colecție care să conțină jucătorii care au acumulat între 1000 și 4000 de puncte
        System.out.println("\nJucătorii care au acumulat între 1000 și 4000 de puncte:");
        List<Jucator> jucatoriPuncte = list.stream()
                .filter(j -> j.getPuncteATP() >= 1000 && j.getPuncteATP() <= 4000)
                .collect(Collectors.toList());
        jucatoriPuncte.forEach(System.out::println);

        // 4. Pentru fiecare naționalitate, să se afișeze numărul de jucători cu acea naționalitate
        System.out.println("\nNumărul de jucători pentru fiecare naționalitate:");
        Map<String, Long> numarJucatoriPeNationalitate = list.stream()
                .collect(Collectors.groupingBy(Jucator::getNationalitate, Collectors.counting()));

        numarJucatoriPeNationalitate.forEach((nationalitate, count) ->
                System.out.println(nationalitate + ": " + count));
    }
}

class EX3 {
    class Counter {
        int counter = 0;
        synchronized public void increment() {
            counter += 1;
        }

        public int getCounter() {
            return counter;
        }
    }

    class MyThread extends Thread {
        private Counter counter;
        private String filename;
        private String nationalitate;

        public MyThread(String filename, String nationalitate, Counter counter) {
            this.filename = filename;
            this.nationalitate = nationalitate;
            this.counter = counter;
        }

        @Override
        public void run() {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            while(scanner.hasNextLine()) {
                String[] s = scanner.nextLine().split(",");
                if(s[1].equals(nationalitate)) {
                    counter.increment();
                }
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("Nationalitate: ");
        Scanner scanner = new Scanner(System.in);
        String nationalitate = scanner.nextLine();

        Counter counter = new Counter();

        MyThread t1 = new MyThread("jucatori_1.txt", nationalitate, counter);
        MyThread t2 = new MyThread("jucatori_2.txt", nationalitate, counter);

        t1.start();
        t2.start();
        t1.join();
        t2.join();

        System.out.println(counter.getCounter());
    }
}