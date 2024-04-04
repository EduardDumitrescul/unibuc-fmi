package lab6.test.enums;


import lab6.enums.DayTime;

public class TestDayTime {
    public static void main(String[] args) {

        for(DayTime dayTime : DayTime.values()) {
            System.out.println(dayTime.name() + ": " + dayTime.getHours());
        }

    }
}
