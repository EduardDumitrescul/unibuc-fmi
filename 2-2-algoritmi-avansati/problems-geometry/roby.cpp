#include <iostream>
#include <vector>


struct Point {
    long long x, y;
};

int runOrientationTest(Point a, Point b, Point c) {
    long long doubleArea = a.x * b.y + a.y * c.x + b.x * c.y - a.x * c.y - a.y * b.x - b.y * c.x;
    int output;
    if(doubleArea == 0) {
        output = 0;
    }   
    else if(doubleArea > 0) {
        output = 1;
    }
    else {
        output = -1;
    }
    return output;
}

int main() {
    int n;
    std::cin >> n;
    std::vector <Point> v(n);
    for(int i = 0; i < n; i ++) {
        std::cin >> v[i].x >> v[i].y;
    }
    v.push_back(v[0]);

    int straight = 0, left = 0, right = 0;

    for(int i = 2; i < n + 1; i ++) {
        int direction = runOrientationTest(v[i-2], v[i-1], v[i]);

        switch (direction)
        {
            case 0:
                straight ++;
                break;
            case 1:
                left ++;
                break;
            case -1:
                right ++;
                break;
        }
    }

    std::cout << left << " " << right << " " << straight << '\n';


    return 0;
}