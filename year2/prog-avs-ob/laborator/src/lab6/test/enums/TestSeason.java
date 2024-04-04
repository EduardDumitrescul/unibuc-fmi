package lab6.test.enums;


import lab6.enums.Season;

public class TestSeason {
    public static void main(String[] args) {
        Season winter = Season.WINTER;
        System.out.println(winter.name());
        winter.printExpectedVisitors();
    }
}
