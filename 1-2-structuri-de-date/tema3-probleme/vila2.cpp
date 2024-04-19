#include <bits/stdc++.h>

std::ifstream fin("vila2.in");
std::ofstream fout("vila2.out");

int main() {
    int n, k;
    fin >> n >> k;
    k ++;

    std::deque <std::pair <int, int>> min, max;
    int result = 0;

    for(int i = 0; i < n; i ++) {
        int value;
        fin >> value;
        if(min.empty() == false and min.back().second == i - k) {
            min.pop_back();
        }
        if(max.empty() == false and max.back().second == i - k) {
            max.pop_back();
        }

        while(min.empty() == false and min.front().first > value) {
            min.pop_front();
        }
        min.push_front({value, i});
        while(max.empty() == false and max.front().first < value) {
            max.pop_front();
        }
        max.push_front({value, i});


        if(i >= k-1) {
            result = std::max(result, max.back().first - min.back().first);
        }
    }
    fout << result;
    return 0;
}
