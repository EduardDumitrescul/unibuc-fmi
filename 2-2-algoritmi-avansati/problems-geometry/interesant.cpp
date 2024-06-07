#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

#define fin std::cin
#define fout std::cout

std::vector <long double> left, right, down, up;

// std::ifstream fin("in.txt");

void prepare() {
    int n;
    fin >> n;
    while(n --) {
        double a, b, c;
        fin >> a >> b >> c;
        if(a == 0 and b > 0) {
            down.push_back(-c/b);
        }
        else if(a == 0 and b < 0) {
            up.push_back(-c/b);
        }
        else if(b == 0 and a > 0) {
            left.push_back(-c/a);
        }
        else {
            right.push_back(-c/a);
        }
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    std::sort(down.begin(), down.end());
    std::sort(up.begin(), up.end());
}

long double eps = 1e-10;

int findGreater(std::vector <long double>& v, long double value) {
    int left = 0, right = v.size() - 1;
    int ans = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(v[mid] - value > eps) {
            ans = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return ans;
}

int findLess(std::vector <long double>& v, long double value) {
    int left = 0, right = v.size() - 1;
    int ans = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(v[mid] - value < -eps) {
            ans = mid;
            left = mid+ 1; 
        }
        else {
            right = mid - 1;
        }
    }
    return ans;
}

void solve() {
    fout << std::setprecision(6) << std::fixed;
    int Q;
    fin >> Q;
    while(Q --){
        long double x, y;
        fin >> x >> y;

        int l = findGreater(left, x);
        int r = findLess(right, x);
        int d = findGreater(down, y);
        int u = findLess(up, y);

        if(l != -1 and r != -1 and u != -1 and d != -1) {
            fout << "YES\n";    
            fout << (left[l]-right[r])*(down[d]-up[u]) << '\n';
        }
        else {
            fout << "NO\n";
        }
    }

}

int main() {
    prepare();
    solve();

    return 0;
}