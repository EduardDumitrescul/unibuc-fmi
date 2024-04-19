#include <bits/stdc++.h>

std::ifstream fin ("plantatie.in");
std::ofstream fout ("plantatie.out");

int a[500][500];
int rmq[9][500][500];

int main(){

    int n, Q, i, j, lenght;
    fin >> n >> Q;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        fin >> a[i][j];


    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        rmq[0][i][j] = a[i][j];
    int p2 = 1, crt = 1;
    while (p2 <= n){
        for (i=0; i<n-p2; i++)
        for (j=0; j<n-p2; j++)
            rmq[crt][i][j] = std::max (std::max (rmq[crt-1][i+p2][j], rmq[crt-1][i][j+p2]),
                                       std::max (rmq[crt-1][i][j], rmq[crt-1][i+p2][j+p2]));
        p2 = (p2 << 1);
        crt ++;
    }

    /*
    for (i=0; i<n; i++, fout << '\n')
    for (j=0; j<n; j++)
        fout << rmq[1][i][j] << ' ';
    */

    while (Q--){
        fin >> i >> j >> lenght;
        i--; j--;
        crt = log2 (lenght);
        p2 = (1 << crt);
        fout << std::max (std::max (rmq[crt][i][j], rmq[crt][i+lenght-p2][j+lenght-p2]),
                          std::max (rmq[crt][i+lenght-p2][j], rmq[crt][i][j+lenght-p2])) << '\n';
    }

    return 0;
}
