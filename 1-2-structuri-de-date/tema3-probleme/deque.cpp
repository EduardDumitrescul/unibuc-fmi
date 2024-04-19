#include <bits/stdc++.h>
#define maxn 5000005
std::ifstream fin("deque.in");
std::ofstream fout("deque.out");

int dq[maxn];
int v[maxn];
int front = -1, back = 0;



int main() {
    int n, k;
    long long sum = 0;
    fin >> n >> k;
    for(int i = 0; i < n; i ++) {
        if(front >= back and i - dq[back] >= k) {
            back ++;
        }
        long long value;
        fin >> value;
        v[i] = value;

        while(back <= front and v[dq[front]] >= value) {
            front --;
        }
        dq[++front] = i;

        if(i >= k-1)
            sum += v[dq[back]];
    }
    fout << sum << '\n';
    return 0;
}
