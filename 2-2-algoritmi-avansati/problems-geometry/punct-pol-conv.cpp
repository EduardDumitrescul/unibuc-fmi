#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#pragma optimize("Ofast")

// std::ifstream fin("in.txt");

#define fin std::cin
#define fout std::cout 

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

void cycleLeftMostFirst() {
    std::vector <Point> points;
    int leftMostIndex = 0;
    for(int i = 1; i < polygon.size(); i ++) {
        if(polygon[i].cmpLeftMost(polygon[leftMostIndex])) {
            leftMostIndex = i;
        }
    }

    for(int i = leftMostIndex; i < polygon.size(); i ++) {
        points.push_back(polygon[i]);
    }
    for(int i = 0; i < leftMostIndex; i ++) {
        points.push_back(polygon[i]);
    }
    polygon = points;
}

void readPolygonVertices() {
    int n;
    fin >> n;
    polygon.resize(n);
    for(int i = 0; i < n; i ++) {
        fin >> polygon[i].x >> polygon[i].y;
    }


    cycleLeftMostFirst();
    polygon.push_back(polygon[0]);

}

int searchSplitPoint(const Point& p) {
    int left = 1, right = polygon.size() - 2;
    int ans = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        long long area = polygon[0].signedDoubleArea(polygon[mid], p);

        if(area >= 0) {
            ans = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return ans;
}

std::string getPositioning(Point p) {
    int index = searchSplitPoint(p);

    // if(p.isOnSegment(polygon[0], polygon[polygon.size() - 2])) {
    //     return "BOUNDARY";
    // }
    
    if(p.isOnSegment(polygon[0], polygon[1])) {
        return "BOUNDARY";
    }

    if(index == -1) {
        return "OUTSIDE";
    }

    if(p.isOnSegment(polygon[index], polygon[index + 1])) {
        return "BOUNDARY";
    }

    int ind2 = index;
    while(ind2 > 1 and polygon[ind2].isOnSegment(polygon[ind2-1], polygon[ind2+1])) {
        ind2 --;
        if(p.isOnSegment(polygon[ind2], polygon[ind2+1])) {
            return "BOUNDARY";
        }
    }


    if(index == polygon.size() - 2) {
        return "OUTSIDE";
    }
    long long a1 = std::labs(p.signedDoubleArea(polygon[0], polygon[index]));
    long long a2 = std::labs(p.signedDoubleArea(polygon[index], polygon[index + 1]));
    long long a3 = std::labs(p.signedDoubleArea(polygon[index + 1], polygon[0]));

    long long area = std::labs(polygon[0].signedDoubleArea(polygon[index], polygon[index + 1]));

    if(area == a1 + a2 + a3) {
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
       
        fout << getPositioning(p) << '\n';
    }
    
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    readPolygonVertices();
    solveQueries();

    return 0;
}