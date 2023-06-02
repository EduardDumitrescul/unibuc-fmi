#include <bits/stdc++.h>
#define maxn 250005
#define lg2 19


std::ifstream fin("stramosi.in");
std::ofstream fout("stramosi.out");

int parent[maxn][lg2];

int main() {
    int n, Q;
    fin >> n >> Q;

    for(int i = 1;i <= n; i ++) {
        fin >> parent[i][0];
    }

    for(int p = 1, p2 = 1; p2 <= n; p2 *= 2, p ++) {
        for(int i = 1; i <= n; i ++) {
            parent[i][p] = parent[parent[i][p-1]][p-1];
        }
    }

    int node, k;
    while(Q --) {
        fin >> node >> k;
        int p = 0;
        while(k and node) {
            if(k % 2 == 1)
                node = parent[node][p];
            k /= 2;
            p ++;
        }
        fout << node << '\n';
    }

    return 0;
}
