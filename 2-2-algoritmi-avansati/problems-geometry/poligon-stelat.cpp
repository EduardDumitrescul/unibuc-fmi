#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include <cmath>

struct Point {
    long long x, y;

    bool operator < (const Point& other) const {
        if(x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

bool cmp(const Point& a, const Point& b) {
    return a.x < b.x;
}

long double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int orientationTest(Point a, Point b, Point c) {
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


    std::vector <Point> convexHull;
    std::sort(v.begin(), v.end());

    for(int i = 0; i < n; i ++) {
        while (convexHull.size() >= 2 
            && orientationTest(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1], v[i]) != 1)
        {
            convexHull.pop_back();
        }
        convexHull.push_back(v[i]);
    }
    for(int i = n-2; i >=0; i--){
        while (convexHull.size() >= 2 
            && orientationTest(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1], v[i]) != 1)
        {
            convexHull.pop_back();
        }
        convexHull.push_back(v[i]);
    }

    std::map <Point, bool> inConvexHull;

    for(auto p: convexHull) {
        inConvexHull[p] = true;
    }

    while(convexHull.size() < n + 1) {
        long double min = 1e18;
        int r, pos;
        for(int i = 0; i < n; i ++) {
            if(inConvexHull[v[i]] == false) {
                int prev = -1;
                long double d = 1e9;
                for(int j = 0; j < convexHull.size() - 1; j ++) {
                    long double currentDist = dist(convexHull[j], v[i]) + dist(v[i], convexHull[j+1]) - dist(convexHull[j], convexHull[j+1]);
                    if(d > currentDist) {
                        d = currentDist;
                        prev = j;
                    }
                }
                long double newMin = (dist(convexHull[prev], v[i]) + dist(v[i], convexHull[prev+1])) / dist(convexHull[prev], convexHull[prev+1]);
                if(min > newMin) {
                    min = newMin;
                    r = i;
                    pos = prev;
                }
            }
        }

        convexHull.insert(convexHull.begin() + pos + 1, v[r]);
        inConvexHull[v[r]] = true;
    }

    std::cout << '\n';
    for(auto p: convexHull) {
        std::cout << p.x << ' ' << p.y << '\n';
    }

    



    return 0;
}