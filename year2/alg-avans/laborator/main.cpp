#include <iostream>
#include <vector>
#include <algorithm>

bool cmp(std::pair <int, int> a, std::pair <int, int> b) {
    if(a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}

void acoperireCuIntervale() {
    int left, right;
    std::cin >> left >> right;

    int n;
    std::cin >> n;
    std::vector <std::pair <int, int>> v(n);
    for(int i = 0; i < n; i ++) {
        std::cin >> v[i].first >> v[i].second;
    }

    std::sort(v.begin(), v.end(), cmp);

    std::vector <int> ans;
    int curr = left;
    int i = 0;

    while(curr < right and i < v.size()) {
        int max = -1e9, index;
        while(v[i].first <= curr) {
            if(max < v[i].second) {
                max = v[i].second;
                index = i;
            }
            i ++;
        }

        if(max == -1e9) {
            std::cout << 0 << '\n';
            return;
        }

        ans.push_back(index);
        curr = max;
    }

    if(curr < right) {
        std::cout << 0 << '\n';
    }
    else {
        std::cout << ans.size() << '\n';
        for(auto i: ans) {
            std::cout << i + 1 << ' ';
        }
    }
}

int main() {
    acoperireCuIntervale();
    return 0;
}
