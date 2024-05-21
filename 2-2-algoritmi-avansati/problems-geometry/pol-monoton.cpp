#include <iostream>
#include <vector>
#include <fstream>

#define fin std::cin
#define fout std::cout

// std::ifstream fin("in.txt");


struct Point {
    long long x, y;

    bool cmpLeftMost(const Point& other){
        if(x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }

    long long signedDoubleArea(const Point& a, const Point& b) const {
        return ((x - a.x) * (y - b.y) - (x - b.x) * (y - a.y));
    }


    bool isOnSegment(const Point& a, const Point& b) {
        return signedDoubleArea(a, b) == 0 && 
            std::min(a.x, b.x) <= x && x <= std::max(a.x, b.x) &&
            std::min(a.y, b.y) <= y && y <= std::max(a.y, b.y);
    }
};


int sgn(long long value) {
    if(value == 0) {
        return 0;
    }
    if(value < 0) {
        return -1;
    }
    return 1;
}

std::vector <Point> polygon;

void read() {
    int n;
    fin >> n;
    polygon.resize(n);
    for(int i = 0; i < n; i ++) {
        fin >> polygon[i].x >> polygon[i].y;
    }
}

int main() {
    read();

    int minx=0, maxx=0, miny=0, maxy=0;
    for(int i = 0; i < polygon.size(); i ++) {
        if(polygon[minx].x > polygon[i].x) {
            minx = i;
        }
        if(polygon[maxx].x < polygon[i].x) {
            maxx = i;
        }
        if(polygon[miny].y > polygon[i].y) {
            miny = i;
        }
        if(polygon[maxy].y < polygon[i].y) {
            maxy = i;
        }
    }

    bool okx = true, oky = true;

    int prev = minx, current = (minx + 1) % polygon.size();
    while(current != maxx) {
        if(polygon[current].x < polygon[prev].x) {
            okx = false;
            break;
        }
        prev = current;
        current = (current + 1) % polygon.size();
    }

    prev = minx;
    current = (minx - 1 + polygon.size()) % polygon.size();
    while(current != maxx) {
        if(polygon[current].x < polygon[prev].x) {
            okx = false;
            break;
        }
        prev = current;
        current = (current - 1 + polygon.size()) % polygon.size();
    }

    prev = miny;
    current = (miny + 1) % polygon.size();
    while(current != maxy) {
        if(polygon[current].y < polygon[prev].y) {
            oky = false;
            break;
        }
        prev = current;
        current = (current + 1) % polygon.size();
    }

    prev = miny;
    current = (miny - 1 + polygon.size()) % polygon.size();
    while(current != maxy) {
        if(polygon[current].y < polygon[prev].y) {
            oky = false;
            break;
        }
        prev = current;
        current = (current - 1 + polygon.size()) % polygon.size();
    }

    if(okx) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }

     if(oky) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }

    return 0;
}