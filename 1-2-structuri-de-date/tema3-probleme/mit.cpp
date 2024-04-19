#include <bits/stdc++.h>
#define maxn 100005

std::ifstream fin ("mit.in");
std::ofstream fout ("mit.out");

int x[maxn];
int tree[4*maxn];
int lazy[4*maxn];

void buildTree (int node, int left, int right){
    if (left == right){
        tree[node] = x[left];
        return;
    }
    int mid = (left + right) / 2;
    buildTree (2*node+1, left, mid);
    buildTree (2*node+2, mid+1, right);
    tree[node] = std::max (tree[2*node+1], tree[2*node+2]);
}

void update (int node, int left, int right, int l, int r, int val){
    if (lazy[node]){
        tree[node] += lazy[node];
        if (left < right){
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (left > right or left > r or right < l)
        return;
    if (l <= left and right <= r){
        tree[node] += val;
        if (left < right){
            lazy[2*node+1] += val;
            lazy[2*node+2] += val;
        }
        return;
    }
    int mid = (left + right) / 2;
    update (2*node+1, left, mid, l, r, val);
    update (2*node+2, mid+1, right, l, r, val);
    tree[node] = std::max (tree[2*node+1], tree[2*node+2]);
}

int query (int node, int left, int right, int l, int r){
    if (lazy[node]){
        tree[node] += lazy[node];
        if (left < right){
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (left > right or left > r or right < l)
        return 0;
    if (l <= left  and right <= r)
        return tree[node];
    int mid = (left + right) / 2;
    int ans1 = query (2*node+1, left, mid, l, r);
    int ans2 = query (2*node+2, mid+1, right, l, r);
    tree[node] = std::max (tree[2*node+1], tree[2*node+2]);
    return std::max (ans1, ans2);
}

int main()
{
    int Q, n, i;
    fin >> n >> Q;
    for (i=0; i<n; i++){
        fin >> x[i];
    }
    buildTree (0, 0,
               n-1);
    int left, right, val, type;
    while (Q --){
        fin >> type;
        if (type == 1){
            fin >> left >> right;
            left--; right--;
            fout << query (0, 0, n-1, left, right) << '\n';
        }
        else{
            fin >> left >> right >> val;
            left--; right--;
            update (0, 0, n-1, left, right, val);
        }
    }
    return 0;
}
