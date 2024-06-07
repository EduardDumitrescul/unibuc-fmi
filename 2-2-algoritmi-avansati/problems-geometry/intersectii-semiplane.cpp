#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

#define fin std::cin
#define fout std::cout

// std::ifstream fin("in.txt");

void solve() {
    int n;
    long double minl = 1e9, mind = 1e9;
    long double maxr = -1e9, maxu = -1e9;
    fin >> n;
    while(n --) {
        double a, b, c;
        fin >> a >> b >> c;
        if(a == 0 and b > 0) {
            mind = std::min(mind, (long double)-c/b);
        }
        else if(a == 0 and b < 0) {
            maxu = std::max(maxu, (long double)-c/b);
        }
        else if(b == 0 and a > 0) {
            minl = std::min(minl, (long double)-c/a);
        }
        else {
            maxr = std::max(maxr, (long double)-c/a);
        }
    }

    if((minl < 1e8 and maxr > -1e8 and minl < maxr) or (mind < 1e8 and maxu > -1e8 and mind < maxu)) {
        fout << "VOID\n";
        return;
    }
    if(minl > 1e8 or mind > 1e8 or maxu < -1e8 or maxr <- 1e8) {
        fout << "UNBOUNDED\n";
        return;
    }
    fout << "BOUNDED\n";

}



int main() {
    solve();

    return 0;
}