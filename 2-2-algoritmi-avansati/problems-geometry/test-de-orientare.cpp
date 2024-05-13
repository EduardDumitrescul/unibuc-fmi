    #include <iostream>

    struct Point {
        long long x, y;
    };

    std::string runOrientationTest(Point a, Point b, Point c) {
        long long doubleArea = a.x * b.y + a.y * c.x + b.x * c.y - a.x * c.y - a.y * b.x - b.y * c.x;
        std::string output;
        if(doubleArea == 0) {
            output = "TOUCH";
        }   
        else if(doubleArea > 0) {
            output = "LEFT";
        }
        else {
            output = "RIGHT";
        }
        return output;
    }

    int main() {
        int tests;
        std::cin >> tests;
        while(tests --) {
            Point a, b, c;
            std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
            std::cout << runOrientationTest(a, b, c) << '\n';
        }
        
        return 0;
    }