package lab4.exercitii;

import java.util.*;

import static java.util.Arrays.stream;

public class Rezolvari {

    private static void ex1() {
        Scanner scanner = new Scanner(System.in);
        String s1 = scanner.nextLine();
        String s2 = scanner.nextLine();
        s1 = s1.toLowerCase(Locale.ROOT);
        s2 = s2.toLowerCase(Locale.ROOT);
        System.out.println(s1.compareTo(s2));
    }

    private static class Ex2Data {
        int vowels;
        int consonants;
        int digits;
        int spaces;

        void count(char chr) {
            checkVowel(chr);
            checkConsonant(chr);
            checkDigit(chr);
            checkSpaces(chr);
        }

        private void checkVowel(char chr) {
            if("aeiouAEUIO".indexOf(chr) > 0) {
                vowels += 1;
            }
        }
        private void checkConsonant(char chr) {
            if("aeiouAEUIO".indexOf(chr) == -1 && Character.isAlphabetic(chr)) {
                consonants += 1;
            }
        }
        private void checkDigit(char chr) {
            if(Character.isDigit(chr)) {
                digits += 1;
            }
        }
        private void checkSpaces(char chr) {
            if(chr == ' ') {
                spaces += 1;
            }
        }
    }

    private static void ex2() {
        Scanner scanner = new Scanner(System.in);
        String text = scanner.nextLine();
        Ex2Data result = new Ex2Data();
        text.chars().forEach(c->result.count((char) c));

        System.out.println(result.vowels + " vowels");
        System.out.println(result.consonants + " consonants");
        System.out.println(result.digits + " digits");
        System.out.println(result.spaces + " spaces");

    }

    private static void ex3() {
        Scanner scanner = new Scanner(System.in);
        String text = scanner.next();
        SortedMap<Character, Integer> map = new TreeMap<>();

        text.chars().forEach(e -> {
            Character chr = (char) e;
            if(!map.containsKey(chr)) {
                map.put(chr, 0);
            }
            map.put(chr, map.get(chr) + 1);
        });

       for(Map.Entry<Character, Integer> entry: map.entrySet()) {
           System.out.println(entry.getKey() + ": " + entry.getValue());
       }
    }

    private static void ex4() {
        Scanner scanner = new Scanner(System.in);

        String text = scanner.nextLine();
        List<String> list = List.of(text.split(" "));
        Set<String> set = new HashSet<>(list);
        System.out.println(set.size());
    }

    public static void main(String[] args) {
        ex4();
    }
}
