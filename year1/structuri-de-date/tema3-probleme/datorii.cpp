#include <bits/stdc++.h>
#define maxn 16005

std::ifstream fin ("datorii.in");
std::ofstream fout ("datorii.out");

int bit[maxn];
int x[maxn];

void update (int pos, int val){
    while (pos < maxn){
        bit[pos] += val;
        pos = (pos | (pos+1));
    }
}

int query (int pos){
    int ans = 0;
    while (pos >= 0){
        ans += bit[pos];
        pos = (pos & (pos+1)) - 1;
    }
    return ans;
}



int main(){
    int n, i, Q, type, left, right, pos, val;
    fin >> n >> Q;
    for (i=0; i<n; i++){
        fin >> x[i];
        update (i, x[i]);
    }
    while (Q --){
        fin >> type;
        if (type == 1){
            fin >> left >> right;
            left --; right --;
            fout << query (right) - query (left-1) << '\n';
        }
        else{
            fin >> pos >> val;
            pos --;
            update (pos, -val);
        }
    }
    return 0;
}
