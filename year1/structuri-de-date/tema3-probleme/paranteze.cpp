#include <bits/stdc++.h>

std::ifstream fin("paranteze.in");
std::ofstream fout("paranteze.out");

int main() {
    int n, result=0, current=0;

    fin >> n;
    std::string s;
    fin >> s;

    bool ok[n] = {};

    std::stack <int> stack;
    char temp;

    for(int i = 0; i < n; i ++) {
        temp = '*';
        if(s[i] == '}') temp = '{';
        if(s[i] == ']') temp = '[';
        if(s[i] == ')') temp = '(';

        if(temp == '*') {
            stack.push(i);
            continue;
        }

        if(stack.empty() == false and s[stack.top()] == temp) {
            ok[i] = ok[stack.top()] = true;
            stack.pop();
        }
        else {
            stack.push(i);
        }
    }

    for(int i = 0; i < n; i ++) {
        if(ok[i] == 1) {
            current ++;
            result = std::max(result, current);
        }
        else {
            current = 0;
        }
    }

    fout << result << '\n';

    return 0;
}
