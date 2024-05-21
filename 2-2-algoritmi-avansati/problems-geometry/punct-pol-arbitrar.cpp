#include <iostream>
#include <vector>
#include <fstream>

#define fin std::cin
#define fout std::cout

// std::ifstream fin("in.txt");

struct Point {
    long long x,y;

    long long signedDoubleArea(const Point& a, const Point& b) const {
        return ((x - a.x) * (y - b.y) - (x - b.x) * (y - a.y));
    }

    bool isOnSegment(const Point& a, const Point& b) {
        return signedDoubleArea(a, b) == 0 && 
            std::min(a.x, b.x) <= x && x <= std::max(a.x, b.x) &&
            std::min(a.y, b.y) <= y && y <= std::max(a.y, b.y);
    }
};

std::vector <Point> polygon;

void readPolygon() {
    int n;
    fin >> n;
    polygon.resize(n);
    for(int i = 0; i < n; i ++) {
        fin >> polygon[i].x >> polygon[i].y;
    }

    polygon.push_back(polygon[0]);
}

Point chooseReferencePoint(Point p) {
    Point ref = {1000000001, 99999999};
    bool intersectVertex = true;
    while(intersectVertex) {
        ref.y = ref.y + 1;
        intersectVertex = false;
        for(auto vertex: polygon) {
            if(vertex.isOnSegment(p, ref)) {
                intersectVertex = true;
            }
        }
    }
    return ref;
}

long long sgn(long long value) {
    if(value == 0) {
        return 0;
    }
    if(value < 0) {
        return -1;
    }
    return 1;
}

bool segmIntersects(Point a, Point b, Point x, Point y) {
    long long axy = a.signedDoubleArea(x, y);
    long long bxy = b.signedDoubleArea(x, y);
    long long xab = x.signedDoubleArea(a, b);
    long long yab = y.signedDoubleArea(a, b);

    return sgn(axy) != sgn(bxy) and sgn(xab) != sgn(yab);

}

std::string getPosition(Point p) {
    for(int i = 1; i < polygon.size(); i ++) {
        if(p.isOnSegment(polygon[i-1], polygon[i])) {
            return "BOUNDARY";
        }
    }


    Point ref = chooseReferencePoint(p);
    int intersections = 0;
    for(int i = 0; i < polygon.size() - 1; i ++) {
        if(segmIntersects(p, ref, polygon[i], polygon[i+1])) {
            intersections += 1;
        }
    }

    if(intersections % 2 == 1) {
        return "INSIDE";
    }
    return "OUTSIDE";

}

void solveQueries() {
    int n;
    fin >> n;
    while(n--) {
        Point p;
        fin >> p.x >> p.y;

        fout << getPosition(p) << '\n';
    }
}


int main() {
    readPolygon();
    solveQueries();
    return 0;
}