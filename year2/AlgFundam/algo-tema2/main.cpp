#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <queue>

struct ToNode {
    int node = -1;
    long long cost = 1;
};

struct Edge {
    int from = -1;
    struct ToNode to;

    static bool edgeCmp(const Edge& a, const Edge& b) {
        return a.to.cost < b.to.cost;
    }
};

class DSU {
    std::vector <int> root;
    std::vector <int> dim;

    int getRoot(int node) {
        if(root[node] == node) {
            return node;
        }
        return root[node] = getRoot(root[node]);
    }

public:
    DSU(int size) {
        root.resize(size);
        dim.resize(size, 1);
        for(int i = 0; i < size; i ++) {
            root[i] = i;
        }
    }

    void addEdge(int node1, int node2) {
        node1 = this->getRoot(node1);
        node2 = this->getRoot(node2);

        if(node1 == node2) {
            return;
        }

        if(dim[node1] < dim[node2]) {
            std::swap(node1, node2);
        }
        dim[node1] += dim[node2];

        root[node2] = node1;
    }

    bool areInSameComponent(int node1, int node2) {
        return getRoot(node1) == getRoot(node2);
    }

    int getSize(int node) {
        node = this->getRoot(node);
        return dim[node];
    }
};

class Graph {
    int v;
    std::vector <std::vector <ToNode>> adj;

public:
    Graph(const std::vector <std::vector <ToNode>> &adj = {}): adj(adj) {
        this->v = adj.size();
    }

    Graph(int v, const std::vector <Edge>& edges = {}) {
        this->v = v;
        adj.resize(this->v);
        for(const auto& edge: edges) {
            addEdge(edge);
        }
    }

    void addEdge(Edge edge) {
        this->adj[edge.from].push_back(edge.to);
        this->adj[edge.to.node].push_back({edge.from, edge.to.cost});
    }

    double getMSTCost() {
        std::vector <Edge> edges;
        for(int node = 0; node < this->v; node ++) {
            for(ToNode next: adj[node]) {
                edges.push_back({node, next});
            }
        }

        std::sort(edges.begin(), edges.end(), Edge::edgeCmp);

        DSU dsu(this->v);

        int remainingEdgesToAdd = this->v - 1;
        double cost = 0;
        for(const Edge& edge: edges) {
            if(dsu.areInSameComponent(edge.from, edge.to.node) == false) {
                dsu.addEdge(edge.from, edge.to.node);
                cost += edge.to.cost;
                remainingEdgesToAdd -= 1;

                if(remainingEdgesToAdd == 0) {
                    break;
                }
            }
        }
        return cost;
    }
};

double dist(std::pair <int, int> point1, std::pair <int, int> point2) {
    return std::sqrt(1.0 * (point1.first - point2.first) * (point1.first - point2.first) + (point1.second - point2.second) * (point1.second - point2.second));
}

// Algoritmul lui Prim
void cablaj() {
    std::ifstream fin("cablaj.in");
    std::ofstream fout("cablaj.out");

    int n;
    fin >> n;
    std::vector <std::pair <int, int>> coord(n);

    for(int i = 0; i < n; i ++) {
        fin >> coord[i].first >> coord[i].second;
    }

//    std::vector <Edge> edges;
//
//    Graph graph(n);
//
//    for(int i = 0; i < n; i ++) {
//        for(int j = i + 1; j < n; j ++) {
//            graph.addEdge({i, {j, dist(coord[i], coord[j])}});
//        }
//    }
//
//    fout << graph.getMSTCost() << '\n';

    std::vector <bool> visited(n, false);
    std::vector <double> d(n);
    visited[0] = true;
    for(int i = 0; i < n; i ++) {
        d[i] = dist(coord[i], coord[0]);
    }

    double totalCost = 0;

    for(int step = 1; step < n; step ++) {
        double dmin = 1e9;
        int index;

        for(int i = 0; i < n; i ++) {
            if(visited[i] == false and dmin > d[i]) {
                dmin = d[i];
                index = i;
            }
        }

        totalCost += dmin;
        visited[index] = true;

        for(int i = 0; i < n; i ++) {
            if(visited[i] == false) {
                d[i] = std::min(d[i], dist(coord[i], coord[index]));
            }
        }
    }

    fout << std::setprecision(6) << std::fixed;
    fout << totalCost << '\n';

    fin.close();
    fout.close();
}

void rusoaica() {
    std::ifstream fin("rusuoaica.in");
    std::ofstream fout("rusuoaica.out");

    int n, m, cost;
    fin >> n >> m >> cost;

    std::vector <Edge> edges(m);
    for(int i = 0; i < m; i ++) {
        fin >> edges[i].from >> edges[i].to.node >> edges[i].to.cost;
        edges[i].from -= 1;
        edges[i].to.node -= 1;
    }

    std::sort(edges.begin(), edges.end(), Edge::edgeCmp);

    DSU dsu(n);
    int cnt = n - 1;
    int totalCost = 0;

    for(auto edge: edges) {
        if(cnt == 0) {
            totalCost -= edge.to.cost;
            continue;
        }
        if(dsu.areInSameComponent(edge.from, edge.to.node)) {
            totalCost -= edge.to.cost;
            continue;
        }
        if(edge.to.cost > cost) {
            totalCost += cost - edge.to.cost;
        }
        else {
            totalCost += edge.to.cost;
        }
        dsu.addEdge(edge.from, edge.to.node);
        cnt -= 1;
    }

    totalCost += cnt * cost;


    fout << totalCost << '\n';


    fin.close();
    fout.close();
}

void camionas() {
    std::ifstream fin("camionas.in");
    std::ofstream fout("camionas.out");

    int n, m, g;
    fin >> n >> m >> g;

    std::vector <Edge> edges(m);
    std::vector <std::vector <ToNode>> adj(n);
    for(int i = 0; i < m; i ++) {
        fin >> edges[i].from >> edges[i].to.node >> edges[i].to.cost;
        edges[i].from -= 1;
        edges[i].to.node -= 1;

        adj[edges[i].from].push_back(edges[i].to);
        adj[edges[i].to.node].push_back({edges[i].from, edges[i].to.cost});
    }

    std::vector <int> dist(m, 1e9);
    std::deque <int> q;

    dist[0] = 0;
    q.push_back(0);

    while(q.empty() == false) {
        int node = q.front();
        q.pop_front();

        for(auto next: adj[node]) {
            if(next.cost < g and dist[next.node] > dist[node] + 1) {
                dist[next.node] = dist[node] + 1;
                q.push_back(next.node);
            }
            else if(next.cost >= g and dist[next.node] > dist[node]) {
                dist[next.node] = dist[node];
                q.push_front(next.node);
            }
        }
    }

    fout << dist[n-1] << '\n';

    fin.close();
    fout.close();
}

void trilant() {
    std::ifstream fin("trilant.in");
    std::ofstream fout("trilant.out");

    int n, m, node1, node2, node3;
    fin >> n >> m;
    fin >> node1 >> node2 >> node3;
    node1 -= 1;
    node2 -= 1;
    node3 -= 1;

    std::vector <std::vector <std::pair <int, long long>>> adj(n);
    for(int i = 0; i < m; i ++) {
        long long src, dest, cost;
        fin >> src >> dest >> cost;
        src -= 1;
        dest -= 1;
        adj[src].push_back({dest, cost});
        adj[dest].push_back({src, cost});
    }

    long long dist[3][n];
    int prev[3][n], len[3][n];
    for(int node = 0; node < n; node ++) {
        dist[0][node] = 1e16;
        dist[1][node] = 1e16;
        dist[2][node] = 1e16;

        len[0][node] = 1e8;
        len[1][node] = 1e8;
        len[2][node] = 1e8;
    }

    dist[0][node1] = 0; prev[0][node1] = -1; len[0][node1] = 0;
    dist[1][node2] = 0; prev[1][node2] = -1; len[1][node2] = 0;
    dist[2][node3] = 0; prev[2][node3] = -1; len[2][node3] = 0;

    std::priority_queue <
            std::pair <long long, std::pair <int, int>>,
            std::vector <std::pair <long long, std::pair <int, int>>>,
            std::greater <std::pair <long long, std::pair <int, int>>>
    > pq;

    pq.push({0, {0, node1}});
    pq.push({0, {1, node2}});
    pq.push({0, {2, node3}});

    while(pq.empty() == false) {
        long long cost = pq.top().first;
        int start = pq.top().second.first;
        int node = pq.top().second.second;
        pq.pop();

        for(auto next: adj[node]) {
            if(dist[start][next.first] > dist[start][node] + next.second) {
                dist[start][next.first] = dist[start][node] + next.second;
                pq.push({dist[start][next.first], {start, next.first}});
                prev[start][next.first] = node;
                len[start][next.first] = len[start][node] + 1;
            }
        }
    }

    long long min = 1e17;
    int endNode;
    for(int node = 0; node < n; node ++) {
        if (min > dist[0][node] + dist[1][node] + dist[2][node]) {
            min = std::min(min, dist[0][node] + dist[1][node] + dist[2][node]);
            endNode = node;
        }
    }

    fout << min << '\n';

    for(int i = 0; i < 3; i ++) {
        int node = endNode;
        int l = len[i][node];
        fout << l + 1 << ' ';
        while(l >= 0) {
            fout << node + 1 << ' ';
            node = prev[i][node];
            l --;
        }
        fout << '\n';
    }

    fin.close();
    fout.close();
}

void oracol() {
    std::ifstream fin("oracol.in");
    std::ofstream fout("oracol.out");

    int n;
    fin >> n;

    std::vector <Edge> x;

    for(int i = 1; i <= n; i ++) {
        for(int j = i; j <= n; j ++) {
            long long cost;
            fin >> cost;
            x.push_back({i, {j, cost}});
        }
    }

    std::sort(x.begin(), x.end(), Edge::edgeCmp);

    DSU dsu(n + 1);
    long long ans = 0, min = 1e9;

    for(auto edge: x) {

        if(dsu.areInSameComponent(edge.from - 1, edge.to.node) == false) {
            dsu.addEdge(edge.from - 1, edge.to.node);
            ans += edge.to.cost;
        }
    }
    fout << ans;

    fin.close();
    fout.close();
}

void bile() {
    std::ifstream fin("bile.in");
    std::ofstream fout("bile.out");

    int n;
    fin >> n;
    std::vector <std::pair <int, int>> x(n*n);


    for(int i = 0; i < n*n; i ++) {
        fin >> x[i].first >> x[i].second;
        x[i].first -= 1;
        x[i].second -= 1;
    }

    bool ok[n][n];
    for(int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            ok[i][j] = false;
        }
    }

    int max = 1;
    std::vector <int> ans;

    DSU dsu(n*n);

    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, -1, 0, 1};

    ans.push_back(0);

    for(int cnt = n*n-1; cnt >= 0; cnt --) {
        int i = x[cnt].first;
        int j = x[cnt].second;

        for(int k = 0; k < 4; k ++) {
            int ii = i + di[k];
            int jj = j + dj[k];
            if(0 <= ii and ii < n and 0 <= jj and jj < n and ok[ii][jj]) {
                dsu.addEdge(ii*n+jj, i*n+j);
            }
        }

        max = std::max(max, dsu.getSize(i*n+j));
        ok[i][j] = true;

        ans.push_back(max);
    }

    ans.pop_back();
    std::reverse(ans.begin(), ans.end());

    for(auto i: ans) {
        fout << i << '\n';
    }

    fin.close();
    fout.close();
}

struct LanternaDestination {
    int node;
    int t, w;
};

int lanternaMinTime(int n, std::vector <std::vector <LanternaDestination>>& adj, int watts, std::vector <int>& friendly) {
    int dist[n][watts+1];
    for(int node = 0; node < n; node ++) {
        for(int w = 0; w <= watts; w ++) {
            dist[node][w] = 1e8;
        }
    }

    dist[0][watts] = 0;
    std::priority_queue <
            std::pair <int, std::pair <int, int>>,
            std::vector <std::pair <int, std::pair <int, int>>>,
            std::greater<std::pair <int, std::pair <int, int>>>
    >pq;

    pq.push({0, {0, watts}});

    while(pq.empty() == false) {
        int node = pq.top().second.first;
        int w = pq.top().second.second;
        pq.pop();

        for(auto next: adj[node]) {
            if(next.w > w) {
                continue;
            }
            int nextTime = dist[node][w] + next.t;
            int remainingWatts = w - next.w;
            if(friendly[next.node]) {
                remainingWatts = watts;
            }
            if(dist[next.node][remainingWatts] > nextTime) {
                dist[next.node][remainingWatts] = nextTime;
                pq.push({nextTime, {next.node, remainingWatts}});
            }
        }
    }
    int min = 1e8;
    for(int w = 0; w <= watts; w ++) {
        min = std::min(min, dist[n-1][w]);
    }

    return min;
}

void lanterna() {
    std::ifstream fin("lanterna.in");
    std::ofstream fout("lanterna.out");

    int n, m, k;
    fin >> n >> k;

    std::vector <int> friendly(n);
    for(int i = 0; i < n; i ++) {
        fin >> friendly[i];
    }

    std::vector <std::vector <LanternaDestination>> adj(n);

    fin >> m;

    for(int i = 0; i < m; i ++) {
        int a, b, w, t;
        fin >> a >> b >> t >> w;
        a -= 1;
        b -= 1;
        adj[a].push_back({b, t, w});
        adj[b].push_back({a, t, w});
    }

    int minTime = lanternaMinTime(n, adj, k, friendly);

    int minPower = 0;
    for(int p = log2(k); p >= 0; p --) {
        if(lanternaMinTime(n, adj, minPower + (1<<p), friendly) > minTime)
            minPower += (1<<p);
    }

    fout << minTime << ' ';
    fout << minPower + 1 << '\n';

    fin.close();
    fout.close();
}

void banuti() {
    std::ifstream fin("banuti.in");
    std::ofstream fout("banuti.out");

    int inf = 1070000001;

    int n, min = inf;
    fin >> n;
    std::vector <int> coins(n);

    for(int i = 0; i < n; i ++) {
        fin >> coins[i];
        min = std::min(min, coins[i]);
    }

    std::vector <int> cost(min, inf);

    for(int i = 0; i < n; i ++) {
        cost[coins[i] % min] = std::min(cost[coins[i] % min], coins[i]);
    }


    std::vector <int> d(min, inf);
    std::priority_queue <int, std::vector <int>, std::greater <int>> pq;
    std::vector <int> edges;
    for(int i = 0; i < min; i ++) {
        if(cost[i] < inf) {
            pq.push(cost[i]);
            d[i] = cost[i];
            edges.push_back(cost[i]);
        }
    }

    while(pq.empty() == false) {
        int value = pq.top();
        pq.pop();

        for(auto i: edges) {
            int nextDist = d[value % min] + i;
            int nextNode = (value + i) % min;
            if(nextDist < d[nextNode]) {
                d[nextNode] = nextDist;
                pq.push(nextDist);
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < min; i ++) {
        ans = std::max(ans, d[i]);
    }
    if(ans == inf) {
        ans = -1;
    }
    else {
        ans -= min;
    }

    fout << ans << '\n';

    fin.close();
    fout.close();
}

void apm2() {
    std::ifstream fin("apm2.in");
    std::ofstream fout("apm2.out");

    int n, m, Q;
    fin >> n >> m >> Q;

    std::vector <Edge> edges(m);
    for(int i = 0; i < m; i ++) {
        int src, dest, cost;
        fin >> src >> dest >> cost;
        src -= 1;
        dest -= 1;
        edges[i] = {src, {dest, cost}};
    }

    std::sort(edges.begin(), edges.end(), Edge::edgeCmp);

    struct Query {
        int src, dest;
        int ans = -1;
    };

    std::vector <Query> queries(Q);
    for(int q = 0; q < Q; q ++) {
        fin >> queries[q].src >> queries[q].dest;
        queries[q].src -= 1;
        queries[q].dest -= 1;
    }

    DSU dsu(n);

    for(auto edge: edges) {
        if(dsu.areInSameComponent(edge.from, edge.to.node)) {
            continue;
        }

        dsu.addEdge(edge.from, edge.to.node);
        for(int q = 0; q < Q; q ++) {
            if(queries[q].ans == -1 and dsu.areInSameComponent(queries[q].src, queries[q].dest)) {
                queries[q].ans = edge.to.cost - 1;
            }
        }
    }

    for(auto query: queries) {
        fout << query.ans << '\n';
    }

    fin.close();
    fout.close();
}

int dragoni_task1(int n, std::vector <std::vector <ToNode>>& adj, std::vector <int>& dragons) {
    std::deque <int> dq;
    dq.push_back(0);
    std::vector <bool> visited(n);
    visited[0] = true;
    int max =  dragons[0];

    while(dq.empty() == false) {
        int node = dq.front();
        dq.pop_front();

        for(auto next: adj[node]) {
            if(visited[next.node] == false and next.cost <= dragons[0]) {
                dq.push_back(next.node);
                visited[next.node] = true;
                max = std::max(max, dragons[next.node]);
            }
        }
    }

    return max;
}

int dragoni_task2(int n, std::vector <std::vector <ToNode>>& adj, std::vector <int>& dragons) {
    std::priority_queue <
        std::pair <int, std::pair <int, int>>,
        std::vector <std::pair <int, std::pair <int, int>>>,
        std::greater <std::pair <int, std::pair <int, int>>>
    > pq;

    pq.push({0, {0, dragons[0]}});

    std::vector <int> maxPower(n, 0);

    while(pq.empty() == false) {
        int dist = pq.top().first;
        int node = pq.top().second.first;
        int power = pq.top().second.second;

        pq.pop();

        if(power < maxPower[node]) {
            continue;
        }

        maxPower[node] = power;

        if(node == n-1) {
            return dist;
        }

        for(auto next: adj[node]) {
            int nextPower = std::max(power, dragons[next.node]);
            if(next.cost <= power and maxPower[next.node] < nextPower) {
                pq.push({dist + next.cost, {next.node, nextPower}});
            }
        }
    }

    return -1;
}

void dragoni() {
    std::ifstream fin("dragoni.in");
    std::ofstream fout("dragoni.out");

    int task;
    fin >> task;
    int n, m;
    fin >> n >> m;
    std::vector <int> dragons(n);

    for(int i = 0; i < n; i ++) {
        fin >> dragons[i];
    }

    std::vector <std::vector <ToNode>> adj(n);
    for(int i = 0; i < m; i ++) {
        int src, dest, cost;
        fin >> src >> dest >> cost;
        src -= 1;
        dest -= 1;
        adj[src].push_back({dest, cost});
        adj[dest].push_back({src, cost});
    }

    if(task == 1) {
        fout << dragoni_task1(n, adj, dragons) << '\n';
    }
    else {
        fout << dragoni_task2(n, adj, dragons) << '\n';
    }



    fin.close();
    fout.close();
}


int main() {
//    cablaj();
//    rusoaica();
//    camionas();
//    trilant();
//    oracol();
//    bile();
//    lanterna();
//    banuti();
//    apm2();
    dragoni();
    return 0;
}
