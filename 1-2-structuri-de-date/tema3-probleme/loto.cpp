#include <bits/stdc++.h>
#define maxn 105

std::ifstream fin("loto.in");
std::ofstream fout("loto.out");


int v[maxn];
std::vector <std::pair <int, int>> sums;

int main() {
    int n, s;
    fin >> n >> s;

    for(int i = 0; i < n; i ++) {
        fin >> v[i];
    }

    for(int i = 0; i < n; i ++) {
        for(int j = i; j < n; j ++) {
            for(int k = j; k <= n; k ++) {
                sums.push_back({v[i] + v[j] + v[k], i * 10000 + j * 100 + k});
            }
        }
    }

    std::sort(sums.begin(), sums.end());

    for(auto it: sums) {

        int left = 0 , right = sums.size()-1, mid, pos = -1;
        while(left <= right) {
            mid = (left + right) / 2;
            if(sums[mid].first == s - it.first) {
                pos = sums[mid].second;
                break;
            }
            else if(sums[mid].first < s - it.first) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        if(pos != -1) {
            std::vector <int> res;
            res.push_back(v[it.second / 10000]);
            res.push_back(v[it.second / 100 % 100]);
            res.push_back(v[it.second % 100]);

            res.push_back(v[pos / 10000]);
            res.push_back(v[pos / 100 % 100]);
            res.push_back(v[pos % 100]);

            std::sort(res.begin(), res.end());

            for(auto i: res)
                fout << i << ' ';
            return 0;
        }
    }
    fout << "-1\n";

    return 0;
}
