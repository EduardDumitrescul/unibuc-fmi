//package org.example.model2024;
//
///*
//1. 3
//2. EX FIN END
//3. Progrmare
//4. 8
//5. DADBDC
// */
//
//// EX 2
///*
//Se consideră definită o clasă Automobil având datele membre marca, model, capacitate
//și pret. Clasa încapsulează constructori, metode de tip set/get pentru toate datele membre,
//precum și metodele toString(), equals() și hashCode(). Creați o lista care să conțină cel
//puțin 3 obiecte de tip Automobil și, folosind stream-uri bazate pe lista creată și lambda expresii,
//rezolvați următoarele cerințe:
//• afișați automobilele care costă cel puțin 5000€, în ordinea descrescătoare a prețurilor;
//• afișați mărcile distincte de automobile;
//• creați o listă formată din automobilele care au capacitatea cilindrică cuprinsă între 2000 și
//3000 cm3;
//• afișați prețul maxim al unui automobil marca "Audi".
// */
//
//import java.io.File;
//import java.sql.*;
//import java.util.List;
//import java.util.Objects;
//import java.util.Scanner;
//
//class EX2 {
//    public static void main(String[] args) {
//        // Afișați automobilele care costă cel puțin 5000€, în ordinea descrescătoare a prețurilor.
//        System.out.println("Automobile care costă cel puțin 5000€, în ordinea descrescătoare a prețurilor:");
//        list.stream()
//                .filter(a -> a.getPret() >= 5000)
//                .sorted((a, b) -> Double.compare(b.getPret(), a.getPret()))
//                .forEach(System.out::println);
//
//        // Afișați mărcile distincte de automobile.
//        System.out.println("\nMărcile distincte de automobile:");
//        list.stream()
//                .map(Automobil::getMarca)
//                .distinct()
//                .forEach(System.out::println);
//
//        // Creați o listă formată din automobilele care au capacitatea cilindrică cuprinsă între 2000 și 3000 cm3.
//        System.out.println("\nAutomobile cu capacitatea cilindrică între 2000 și 3000 cm3:");
//        List<Automobil> l3 = list.stream()
//                .filter(a -> a.getCapacitate() >= 2000 && a.getCapacitate() <= 3000)
//                .collect(Collectors.toList());
//        l3.forEach(System.out::println);
//
//        // Afișați prețul maxim al unui automobil marca "Audi".
//        System.out.println("\nPrețul maxim al unui automobil marca Audi:");
//        list.stream()
//                .filter(a -> "Audi".equals(a.getMarca()))
//                .max(Comparator.comparingDouble(Automobil::getPret))
//                .ifPresent(System.out::println);
//
//
//    }
//}
//
//
//class EX3 {
//    class Counter {
//        private int counter = 0;
//        synchronized public void increment() {
//            counter += 1;
//        }
//
//        public int getCounter() {
//            return counter;
//        }
//    }
//
//    class CounterThread extends Thread {
//        private String filename;
//        private String word;
//        private Counter counter = 0;
//
//        public int getCounter() {
//            return counter;
//        }
//
//        public CounterThread(String filename, String word, Counter counter) {
//            this.filename = filename;
//            this.word = word;
//            this.counter = counter;
//        }
//
//        @Override
//        public void run() {
//            File file = new File(filename);
//            Scanner scanner = new Scanner(file);
//            while(scanner.hasNextLine()) {
//                String line = scanner.nextLine();
//                String[] words = line.split("[ ,./;!?]");
//                for (String w : words) {
//                    if(Objects.equals(word, w)) {
//                        counter.increment();
//                    }
//                }
//            }
//        }
//    }
//
//    public static void main(String[] args) {
//        Counter counter = new Counter();
//        CounterThread t1 = new CounterThread("exemplu_1.txt", "cuvant", counter);
//        CounterThread t2 = new CounterThread("exemplu_2.txt", "cuvant", counter);
//        CounterThread t3 = new CounterThread("exemplu_3.txt", "cuvant", counter);
//
//        t1.start();
//        t2.start();
//        t3.start();
//
//        t1.join();
//        t2.join();
//        t3.join();
//
//        System.out.println(counter.getCounter());
//    }
//    /*
//    Scrieți o clasă Java care să calculeze de câte ori apare un cuvânt dat într-un fișier text, folosind un
//fir de executare. Scrieți un program care citește de la tastatură un cuvânt și, utilizând clasa definită
//anterior, afișează numărul total al aparițiilor cuvântului respectiv în fișierele text exemplu_1.txt,
//exemplu_2.txt și exemplu_3.txt. Cuvintele din fișierele text de intrare sunt despărțite între ele prin
//spații și semnele de punctuație uzuale.
//     */
//
//}
//
//
//class EX4 {
//    /*
//    Se consideră baza de date Angajati, având următorul URL: jdbc:derby://localhost:1527/Angajati.
//Baza de date conține tabela DateAngajati, având câmpurile CNP, Nume, Varsta și Salariu. Scrieți un
//program care să citească de la tastatură o valoare reală s și valoare întreagă v, după care afișează
//informațiile despre angajații având cel mult v ani și salariul cel puțin s RON.
//     */
//
//    public static void main(String[] args) {
//        Scanner scanner = new Scanner(System.in);
//        double s = scanner.nextDouble();
//        int v = scanner.nextInt();
//
//        Connection connection = DriverManager.getConnection("jdbc:derby://localhost:1527/Angajati");
//        PreparedStatement statement = connection.prepareStatement("select * from DateAngajati where Varsta<=? and salariu>=?");
//        statement.setInt(1, v);
//        statement.setDouble(2, d);
//        ResultSet rs = statement.executeQuery();
//        while (rs.next()) {
//            System.out.println(rs.getString("CNP") + ...);
//        }
//    }
//}