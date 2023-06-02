#include <bits/stdc++.h>
#define maxn 30005
std::ifstream fin ("order.in");
std::ofstream fout ("order.out");

int BIT[maxn];
void update (int pos, int val){
    while (pos < maxn){
        BIT[pos] += val;
        pos = (pos | (pos+1));
    }
}
int queryBIT (int pos){
    int ans = 0;
    while (pos >= 0){
        ans += BIT[pos];
        pos = (pos & (pos+1)) - 1;
    }
    return ans;
}
int query (int start, int stop, int k){
    int mid, left = start, right = stop, qm, qs = queryBIT(start);
    while (left <= right){
        mid = (left + right) / 2;
        //std::cout << queryBIT(mid)-queryBIT(start) << '\n';
        qm = queryBIT(mid);
        if (qm-qs == k and qm != queryBIT(mid-1))
            return mid;
        if (qm-qs < k)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

int main()
{
    int n, i, left, pos, moves, av;
    fin >> n;
    for (i=0; i<n; i++)
        update (i, 1);

    for (i=1, left=n, pos=0; i<=n; i++, left--){
        moves = i;
        moves = (moves - 1) % left + 1;
        av = queryBIT (n) - queryBIT (pos);
        if (av < moves){
            moves -= av;
            pos = -1;
        }

        pos = query (pos, n-1, moves);
        fout << pos + 1<< ' ';
        update (pos, -1);
    }
    return 0;
}
