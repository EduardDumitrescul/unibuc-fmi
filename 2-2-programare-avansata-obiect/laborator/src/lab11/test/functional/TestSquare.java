package lab11.test.functional;

import lab11.functional.RectangleFI;
import lab11.functional.SquareFI;

import java.awt.*;

public class TestSquare {

    public static void main(String[] args) {
        int a = 5;

        SquareFI s1 = (int x) -> x * x;
        int area = s1.calculate(a);
        System.out.println("Area of square is: " + area);

        SquareFI s2 = (int x) -> 4 * x;
        int perimeter = s2.calculate(a);
        System.out.println("Perimeter of square is: " + perimeter);

        RectangleFI rectArea = (x, y) -> x*y;
        area = rectArea.calculate(4, 5);
        System.out.println(area);

        RectangleFI rectPerimeter = (int x, int y) -> 2*x+2*y;
        perimeter  = rectPerimeter.calculate(4, 5);
        System.out.println(perimeter);

    }
}
