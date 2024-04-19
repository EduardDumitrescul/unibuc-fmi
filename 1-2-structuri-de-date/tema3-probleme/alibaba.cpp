#include <bits/stdc++.h>

std::ifstream fin("alibaba.in");
std::ofstream fout("alibaba.out");

int main() {
    int n, k;
    fin >> n >> k;
    std::string s;
    fin >> s;

    std::deque <char> stack;

    for(auto i: s) {
        while(k and stack.empty() == false and stack.back() < i) {
            stack.pop_back();
            k--;
        }
        stack.push_back(i);
    }
    while(k--) {
        stack.pop_back();
    }
    for(auto i: stack)
    fout << i;
    return 0;
}
