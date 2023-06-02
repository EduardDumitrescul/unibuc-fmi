#include <bits/stdc++.h>

std::ifstream fin ("matrice3.in");
std::ofstream fout ("matrice3.out");

char a[255][255];
short int dp[255][255];
short int rmq[8][8][255][255];

bool found (short int x1, short int y1, short int x2, short int y2, short int size){
    if (x2 < x1 or y2 < y1) return false;
    short int lx = x2 - x1 + 1;
    short int ly = y2 - y1 + 1;
    short int px = log2 (lx);
    short int py = log2 (ly);

    if (rmq[px][py][x1][y1] >= size)
        return true;

    if (rmq[px][py][x2-(1<<px)+1][y1] >= size)
        return true;

    if (rmq[px][py][x1][y2-(1<<py)+1] >= size)
        return true;

    if (rmq[px][py][x2-(1<<px)+1][y2-(1<<py)+1] >= size)
        return true;

    return false;
}

int main(){

    short int n, m, i, j ,p;
    int Q;
    fin >> n >> m >> Q;
    for (i=0; i<n; i++)
    for (j=0; j<m; j++){
        fin >> a[i][j];
        if (a[i][j] == '1')
            dp[i][j] = 0;
        else{
            if (i == 0 or j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = std::min (dp[i-1][j],
                                    std::min (dp[i-1][j-1], dp[i][j-1])) + 1;
        }
    }

    for (i=0; i<n; i++)
        for (j=0; j<m; j++)
            rmq[0][0][i][j] = dp[i][j];




    for (int pi=0; pi<=7; pi++)
    for (int pj=0; pj<=7; pj++){
        if (pi == 0 and pj == 0)
            continue;
        for (i=0; i<n-(1<<(pi))+1; i++)
        for (j=0; j<m-(1<<(pj))+1; j++){
            if (pi > 0)
                rmq[pi][pj][i][j] = std::max (rmq[pi-1][pj][i][j], rmq[pi-1][pj][i+(1<<(pi-1))][j]);
            else
                rmq[pi][pj][i][j] = std::max (rmq[pi][pj-1][i][j], rmq[pi][pj-1][i][j+(1<<(pj-1))]);
        }
    }
    /*
    for (i=0; i<n; i++, fout << '\n')
        for (j=0; j<m; j++)
        fout << rmq[0][2][i][j] << ' ';
        */

    /*
    for (i=0; i<n; i++, fout << '\n')
        for (j=0; j<m; j++)
        fout << rmq[1][i][j] << ' ';
    */


    while (Q--){
        short int x1, x2, y1, y2, lx, ly;
        fin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        lx = x2 - x1 + 1;
        ly = y2 - y1 + 1;

        short int st=1, dr=std::min (lx, ly), mij, ans=0;
        while (st < dr){
            mij = (st + dr) / 2;
            if (found (x1+mij-1, y1+mij-1, x2, y2, mij)){
                ans = mij;
                st = mij + 1;
            }
            else
                dr = mij - 1;

        }
        mij = st;
        if (found (x1+mij-1, y1+mij-1, x2, y2, mij))
            ans = mij;

        fout << ans << '\n';

    }


    return 0;
}
