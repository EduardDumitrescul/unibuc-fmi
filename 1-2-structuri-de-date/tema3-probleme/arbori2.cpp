#include <bits/stdc++.h>
const long long mod = 9999991LL;

std::ifstream fin("arbori2.in");
std::ofstream fout("arbori2.out");

long long ct[205], v[205];

long long count(int left, int right) {

    if(left > right)
        return 0;
    if(left == right) {
        return 0;
    }
    long long cnt = 0;
    int root = v[left], len = right - left + 1;
    int mid = left;
    while(mid <= right and v[mid] <= root)
        mid ++;

    for(int i = 0; i <= right - mid; i ++) {    
        cnt += ct[i] * ct[len - i - 1];
        cnt %= mod;
    }
    long long result  = (cnt + count(left+1, mid-1) * ct[right - mid + 1] + count(mid, right)) % mod;
    //std::cout << left << ' ' << right << ' ' << result << '\n';
    return result;

}

void solve(int n) {
    for(int i = 0; i < n; i ++)
        fin >> v[i];


    fout << count(0, n-1) + 1 << '\n';

}

void precompute() {
    ct[0] = 1;
    ct[1] = 1;
    for(int i = 2; i <= 200; i ++) {
        for(int j = 0; j < i; j ++) {
            ct[i] = (ct[i] + ct[j] * ct[i-j-1]) % mod;
        }
    }
}

int main() {
    int Q;
    precompute();
    int n;
    for(int i = 1; fin >> n and n; i ++) {
        fout << i << ':';
        solve(n);
    }
    return 0;
}
