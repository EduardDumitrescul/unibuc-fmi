#include <bits/stdc++.h>
std::ifstream f("pariuri.in");
std::ofstream g("pariuri.out");
int main(){
int n,k,t,v,i;
f>>n;
std::unordered_map<int,int>m;
while(n--){
    f>>k;
    while(k--){
    f>>t>>v;
    m[t]+=v;
    }
}

g<<m.size()<<'\n';
for(auto it: m)
    g<<it.first<<' '<<it.second<<' ';
return 0;
}
