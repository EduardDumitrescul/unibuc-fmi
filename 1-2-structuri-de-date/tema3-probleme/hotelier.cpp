#include <bits/stdc++.h>
 
int main() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
 
 
    int x[10] = {};
 
    for(auto chr: s) {
        if(chr == 'L') {
            for(int i = 0; i < 10; i ++) {
                if(x[i] == 0) {
                    x[i] = 1;
                    break;
                }
            }
        }
        else if(chr == 'R') {
            for(int i = 9; i >= 0; i --) {
                if(x[i] == 0) {
                    x[i] = 1;
                    break;
                }
            }
        }
        else {
            x[chr - '0'] = 0;
        }
    }
    for(int i = 0; i < 10; i ++)
        std::cout << x[i];
    return 0;
}
