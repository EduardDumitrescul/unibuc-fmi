#include <fstream>
#include <vector>
#include <queue>

#define CL 420
#define INF 1000000000

std::ifstream fin("patrol2.in");
std::ofstream fout("patrol2.out");

std::vector <std::vector <int>> adj;
std::vector <int> dist[CL];

void computeGuards(int n, int k) {
    for(int i = 0; i < CL; i ++) {
        dist[i].resize(n, INF);
    }

    for(int i = 0; i < k; i ++) {
        int cnt;
        fin >> cnt;
        std::vector <int> path(cnt);
        for(int j = 0; j < cnt; j ++) {
            fin >> path[j];
        }
        for(int j = 0; j < CL; j ++) {
            dist[j][path[j % cnt]] = -1;
        }
    }
}

int solve(int n) {
    std::queue <std::pair <int, int>> q;
    q.push({0, 0});
    dist[0][0] = 0;


    while(q.empty() == false) {
        auto p = q.front();
        int node = p.first;
        int mod = p.second;
        q.pop();

        int nextMod = (mod + 1) % CL;

        for(int next: adj[node]) {
            if(dist[nextMod][next] == -1) {
               continue;
            }
            if(dist[nextMod][next] > dist[mod][node] + 1) {
                dist[nextMod][next] = dist[mod][node] + 1;
                q.push({next, nextMod});
            }
        }
    }
    int min = INF;
    for(int i = 0; i < CL; i ++) {
        if(dist[i][n-1] != -1) {
           min = std::min(min, dist[i][n-1]);
        }
    }
    if(min == INF){
        min = -1;
    }

    return min;
}

int main() {
    int n, m, k;
    fin >> n >> m >> k;
    adj.resize(n);

    for(int i = 0; i < m; i ++) {
        int a, b;
        fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 0; i < n ; i ++) {
        adj[i].push_back(i);
    }

    computeGuards(n, k);

    fout << solve(n);

    return 0;
}