#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define fin std::cin
#define fout std::cout

// std::ifstream fin("in.txt");

const int mil = 1000000;

struct Segment {
    int x1, y1, x2, y2;
};

bool sortByX(Segment a, Segment b) {
    return a.x1 < b.x1;
}
bool sortByY(Segment a, Segment b) {
    return a.y1 < b.y1;
}
std::vector <Segment> vertical, horizontal;
std::vector <std::tuple <int, int, int>> ev;


int bit[2*mil+5];

int sum(int pos) {
    if(pos < 0) {
        return 0;
    }
    int s = 0;
    while(pos >= 0) {
        s += bit[pos];
        pos = (pos & (pos + 1)) - 1;
    }
    return s;
}

int sum(int left, int right) {
    return sum(right) - sum(left-1);
}


void add(int pos, int val) {
    while(pos < 2000001) {
        bit[pos] += val;
        pos = pos | (pos + 1);
    }
}


int main() {
    int n;
    fin >> n;
    for(int i = 0; i < n; i ++) {
        int x1, x2, y1, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        x1 += mil;
        x2 += mil;
        y1 += mil;
        y2 += mil;

        if(x1 == x2) {
            vertical.push_back({x1, y1, x2, y2});
        }
        else {
            ev.push_back({x1, y1, 1});
            ev.push_back({x2, y1, -1});
        }
    }

    std::sort(vertical.begin(), vertical.end(), sortByX);
    std::sort(ev.begin(), ev.end());
    
    int index = 0;
    long long count = 0; 

    for(auto v: vertical) {
        while(index < ev.size() and v.x1 > std::get<0>(ev[index])) {
            if(std::get<2>(ev[index]) == 1) {
                add(std::get<1>(ev[index]), 1);
            }
            else {
                add(std::get<1>(ev[index]), -1);
            }
            index ++;
        }

        count += sum(std::min(v.y1, v.y2), std::max(v.y1, v.y2));

    }
    fout << count << '\n';



    return 0;
}