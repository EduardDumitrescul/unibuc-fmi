#include <bits/stdc++.h>

std::ifstream fin("curatenie.in");
std::ofstream fout("curatenie.out");


int a[500005], b[500005], pos[500005];
std::pair <int, int> res[500005];


void solve(int left, int right, int left2, int right2) {
    if(left  >= right)
        return;
    int mid = pos[b[left]];
    
    int l = mid - left2, r = right2 - mid;

    if(l) res[b[left]].first = b[left + 1];
    if(r) res[b[left]].second = b[left + l + 1];

    solve(left+1, left + l, left2, left2+l-1);
    solve(left + l + 1, right, right2-r+1, right2);

}

int main() {
    int n;
    fin >> n;
    for(int i = 0; i < n; i ++) {
        fin >> a[i];
        pos[a[i]] = i;
    }
    for(int i = 0; i < n; i ++) {
        fin >> b[i];
    }
    solve(0, n-1, 0, n-1);

    for(int i = 1; i <= n; i ++){
        fout << res[i].first << ' ' << res[i].second << '\n';
    }

    

    return 0;
}
