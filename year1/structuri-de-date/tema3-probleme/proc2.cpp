#include <bits/stdc++.h>

std::ifstream fin("proc2.in");
std::ofstream fout("proc2.out");

int main() {
    int n, k;
    fin >> n >> k;
    std::priority_queue <int, std::vector <int>, std::greater <int>> free;
    std::priority_queue <std::pair <int, int>, std::vector <std::pair <int, int>>, std::greater<std::pair<int, int>>> working;
    for(int i = 0; i < n; i ++) {
        free.push(i+1);
    }

    for(int i = 0; i < k; i ++) {
        int s, d;
        fin >> s >> d;
        while(working.empty() == false and working.top().first <= s) {
            free.push(working.top().second);
            working.pop();
        }
        fout << free.top() << '\n';
        working.push({s+d, free.top()});
        free.pop();
    }
    return 0;
}
