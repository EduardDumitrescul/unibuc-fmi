#include <iostream>
#include <vector>
#include <algorithm>
#include <valarray>

void geneticiMutatie() {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;
    for(int i = 0; i < k; i ++) {
        int pos;
        std::cin >> pos;
        s[pos] = 1 - s[pos] + 2 * '0';
    }
    std::cout << s << '\n';
}

int main() {
    geneticiMutatie();
    return 0;
}
