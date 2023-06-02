#include <bits/stdc++.h>

std::ifstream fin("planeta.in");
std::ofstream fout("planeta.out");

int v[31];

long long ct[31];

void precompute() {
    ct[0] = ct[1] = 1;
    for(int i = 2; i <= 30; i ++) {
        for(int j = 0; j < i; j ++) {
            ct[i] = ct[i] + ct[j] * ct[i-j-1];
        }
    }
}

void solve(int left, int right, int min, int max, long long k) {
    if(left > right) {
        return;
    }
    if(left == right) {
        v[left] = min;
        return;
    }
    int len = right - left;
    long long temp = 0;
    int i;
    for(i = 0; temp + ct[i] * ct[len - i] <= k; i ++) {
        temp += ct[i] * ct[len - i];
    }

    v[left] = min + i;
    int l = i, r = max - min - i;
    
    solve(left+1, left+l, min, min+l-1, (k - temp   ) / ct[r]);
    solve(left+l+1, right, min+i+1, max, (k - temp) % ct[r]);


}

int main() {
    int n;
    long long k;
    fin >> n >> k;
    precompute();
    solve(0, n-1, 1, n, k - 1);

    for(int i = 0; i < n;i ++)
    fout << v[i] << ' ';
    return 0;
}
