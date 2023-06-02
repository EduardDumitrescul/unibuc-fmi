#include <bits/stdc++.h>
#define maxn 70000

std::ifstream fin ("schi.in");
std::ofstream fout ("schi.out");

int tree[maxn];
int x[maxn], ans[maxn];

void buildTree (int left, int right, int node){
    if (left == right){
        tree[node] = 1;
        return;
    }
    int mid = (left + right) / 2;
    buildTree (left, mid, 2*node+1);
    buildTree (mid+1, right, 2*node+2);

    tree[node] = tree[2*node+1] + tree[2*node+2];
}

int findTree (int left, int right, int node, int val){
    if (left == right){
        tree[node] = 0;
        return left;
    }

    int mid = (left + right) / 2, ans;
    if (tree[2*node+1] >= val) ans = findTree (left, mid, 2*node+1, val);
    else ans = findTree (mid+1, right, 2*node+2, val - tree[2*node+1]);

    tree[node] = tree[2*node+1] + tree[2*node+2];

    return ans;

}

int main ()
{
	int n, i, pos;
	fin >> n;
	for (i=0; i<n; i++)
        fin >> x[i];

    buildTree (0, n-1, 0);

    for (i=n-1; i>=0; i--){
        pos = findTree (0, n-1, 0, x[i]);
        ans[pos] = i + 1;
    }


    for (i=0; i<n; i++)
        fout << ans[i] << '\n';

	return 0;
}
