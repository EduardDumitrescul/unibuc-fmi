#include <iostream>
#include <fstream>

#define fin std::cin
#define fout std::cout

// std::ifstream fin("in.txt");

struct Point {
    int x, y;
};

long criteria(Point a, Point b, Point c, Point d){
    double M[4][4] = {
        {a.x, a.y, a.x * a.x + a.y * a.y, 1},
        {b.x, b.y, b.x * b.x + b.y * b.y, 1},
        {c.x, c.y, c.x * c.x + c.y * c.y, 1},
        {d.x, d.y, d.x * d.x + d.y * d.y, 1}
    };

    double detM11 = M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                    M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) +
                    M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]);

    double detM12 = M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                    M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                    M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]);

    double detM13 = M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                    M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                    M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]);

    double detM14 = M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                    M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]) +
                    M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]);

    double det = M[0][0] * detM11 -
                 M[0][1] * detM12 +
                 M[0][2] * detM13 -
                 M[0][3] * detM14;

    return det;
}

int main() {
    Point a, b, c;
    fin >> a.x >> a.y;
    fin >> b.x >> b.y;
    fin >> c.x >> c.y;

    int Q;
    fin >> Q;
    while(Q --) {
        Point p;
        fin >> p.x >> p.y;
        
        long crit = criteria(a, b, c, p);
        if(crit == 0) {
            fout << "BOUNDARY\n";
        }
        else if(crit > 0) {
            fout << "INSIDE\n";
        }
        else {
            fout << "OUTSIDE\n";
        }
    }

    return 0;
}