#include <bits/stdc++.h>
#define maxn 100005

std::ifstream fin("arbint.in");
std::ofstream fout("arbint.out");

int v[maxn];
int max[4 * maxn];

void build(int node, int left, int right) {
    if(left == right) {
        max[node] = v[left];
        return;
    }
    int mid = (left + right) / 2;
    build(2*node+1, left, mid);
    build(2*node+2, mid+1, right);
    max[node] = std::max(max[2*node+1], max[2*node+2]);
}

int query(int node, int left, int right, int l, int r) {
    if(l > right or r < left ) {
        return 0;
    }
    if(l <= left  and right <= r) {
        return max[node];
    }
    int mid = (left + right) / 2;
    return std::max(query(2*node+1, left, mid, l, r), query(2*node+2, mid+1, right, l, r));
}

void update(int node, int left, int right, int pos, int val) {
    if(left == right) {
        max[node] = val;
        return;
    }
    int mid = (left + right) / 2;
    if(mid >= pos) {
        update(2*node+1, left, mid, pos, val);
    }
    else {
        update(2*node+2, mid+1, right, pos, val);
    }
    max[node] = std::max(max[2*node+1], max[2*node+2]);
}

int main() {
    int n, q;
    fin >> n >> q;
    for(int i = 0; i < n; i ++) {
        fin >> v[i];
    }
    build(0, 0, n-1);
    while(q --) {
        int type, a, b;
        fin >> type >> a >> b;
        if(type == 0) {
            fout << query(0, 0, n-1, a-1, b-1) << '\n';
        }
        else {
            update(0, 0, n-1, a-1, b);
        }
    }
    return 0;
}
