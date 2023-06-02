#include <bits/stdc++.h>

const long long mod = 666013;

std::ifstream fin("permheap.in");
std::ofstream fout("permheap.out");

long long fastpow(long long base, long long p) {
    long long res = 1;
    while(p) {
        if(p % 2 == 1) 
            res = res * base % mod;
        base = base * base % mod;
        p /= 2;
    }
    return res;
}

int main() {
    int n;
    fin >> n;
    long long cnt[n+1] = {}, fact[n+1];
    cnt[0] = 1;
    cnt[1] = 1;
    fact[0] = 1;
    for(int i = 1; i <= n; i ++)
        fact[i] = fact[i-1] * i % mod;

    int left = 0, right = 0, add = 0, remain = 1, p2 = 1;

    for(int i = 2; i <= n; i ++) {
        if(add == 0) {
            left ++;
            remain --;
            if(remain == 0) {
                remain = p2;
                add = 1;
            }
        }
        else{
            right ++;
            remain --;
            if(remain == 0) {
                p2 *= 2;
                add = 0;
                remain = p2;
            }
        }

        //std::cout << i << ' ' << p2 << ' ' << ' ' << left << ' ' << right << '\n';

        long long comb = fact[i-1] * fastpow(fact[left], mod-2) % mod * fastpow(fact[right], mod-2) % mod;
        cnt[i] = comb * cnt[left] % mod * cnt[right] % mod;
    }

    fout << cnt[n] << '\n';

    return 0;
}
