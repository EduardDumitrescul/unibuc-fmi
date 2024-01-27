#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <queue>
#include <stack>
#include <unordered_map>
#include <map>
#include <algorithm>

class Seg {
    std::ifstream fin;
    std::ofstream fout;

    int n;
    struct  Point {
        double x, y;
        double dist(Point p) {
            return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
        }
    };
    struct Line {
        Point a, b;
    };

    std::vector <Line> lines;
    std::vector <double> dp[2][17];

    void reset() {
        lines.clear();
        for(int i = 0; i < 2; i ++) {
            for(int j = 0;j  < 17; j ++) {
                dp[i][j].clear();
            }
        }
    }

    void readTest() {
        fin >> n;
        lines.resize(n);
        for(int i = 0; i < n; i ++) {
            double x1, x2, y1, y2;
            fin >> x1 >> y1 >> x2 >> y2;
            lines[i] = {{x1, y1}, {x2, y2}};
        }
    }

    void solveTest() {
        for(int i = 0; i < 2; i ++) {
//            dp[i].resize(n);
            for (int j = 0; j < n; j++) {
                dp[i][j].resize(1 << n, 1e18);
            }
        }
        dp[0][0][1] = 0;
        for(int bitmask = 1; bitmask < (1<<n); bitmask ++) {
            for(int endNode = 0; endNode < n; endNode ++) {
                if(bitmask & (1<<endNode)) {
                    for(int x=0; x < n; x ++) {
                        if(x == endNode or (bitmask & (1<<x)) == 0){
                            continue;
                        }
                        int prevMask = bitmask ^ (1 << endNode);
                        dp[0][endNode][bitmask] = std::min(dp[0][endNode][bitmask], dp[0][x][prevMask] + lines[x].a.dist(lines[endNode].b)); //dist[0][1][x][endNode]
                        dp[0][endNode][bitmask] = std::min(dp[0][endNode][bitmask], dp[1][x][prevMask] + lines[x].b.dist(lines[endNode].b));  // dist[1][1][x][endNode]
                        dp[1][endNode][bitmask] = std::min(dp[1][endNode][bitmask], dp[0][x][prevMask] + lines[x].a.dist(lines[endNode].a)); // dist[0][0][x][endNode]
                        dp[1][endNode][bitmask] = std::min(dp[1][endNode][bitmask], dp[1][x][prevMask] + lines[x].b.dist(lines[endNode].a));  // dist[1][0][x][endNode]
                    }
                }
            }
        }

        double sol = 1e18;
        for(int i = 1; i < n; i ++) {
            sol = std::min(sol, dp[0][i][(1<<n) - 1] + lines[i].a.dist(lines[0].b));// dist[0][1][i][0]);
            sol = std::min(sol, dp[1][i][(1<<n) - 1] + lines[i].b.dist(lines[0].b));// dist[1][1][i][0]);
        }
        fout << sol << '\n';
    }
public:
    void solve() {
        fin.open("seg.in");
        fout.open("seg.out");

        int Q;
        fin >> Q;
        fout << std::setprecision(6) << std::fixed;
        while(Q --) {
            this->reset();
            this->readTest();
            this->solveTest();
        }

        fin.close();
        fout.close();
    }
};

// https://leetcode.com/problems/shortest-path-visiting-all-nodes/
class ShortestPath {
    std::ifstream fin;
    std::ofstream fout;


public:
    int shortestPathLength(std::vector<std::vector<int>>& graph) {
        int n = graph.size();
        bool visited[(1<<n)][n];
        for(int mask=0; mask < (1<<n); mask ++) {
            for(int i = 0; i < n; i ++) {
                visited[mask][i] = false;
            }
        }
        std::queue<std::pair <int, int>> q, q2;
        for(int i = 0; i < n; i ++) {
            q.push({i, (1<<i)});
        }
        int dist = 0;
        while(q.empty() == false) {
            while(q.empty() == false) {
                auto [node, mask] = q.front();
                q.pop();

                if(mask == (1<<n) - 1) {
                    return dist;
                }
                if(visited[mask][node]) {
                    continue;
                }
                visited[mask][node] = true;

                for(int next: graph[node]) {
                    q2.push({next, mask | (1<< next)});
                }
            }
            std::swap(q, q2);
            dist += 1;
        }
        return -1;
    }

    void solve() {
        fin.open("input.txt");
        fout.open("output.txt");
        int n;
        fin >> n;
        std::vector <std::vector <int>> graph(n);
        for(int i = 0; i < n; i ++) {
            int k;
            fin >> k;
            for(int j = 0; j < k; j ++) {
                int temp;
                fin >> temp;
                graph[i].push_back(temp);
            }
        }

        fout << shortestPathLength(graph) << '\n';
    }
};

class Cartite {
    std::ifstream fin;
    std::ofstream fout;

    int task;
    int n, m;
    int sx, sy;
    std::vector <std::vector <bool>> blocked;
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, -1, 0, 1};

    int edges;
    std::vector <std::vector <int>> graph;
    std::vector <bool> isEntry;

    void blockCells(int i, int j, int p) {
        blocked[i][j] = true;
        if(p > 0) {
            for(int k = 0; k < 4; k ++) {
                int ii = i + di[k];
                int jj = j + dj[k];
                if(0 <= ii and ii < n and 0 <= jj and jj < m) {
                    blockCells(ii, jj, p-1);
                }
            }
        }

    }


    void readInput() {
        fin >> task;
        fin >> n >> m;
        blocked.resize(n, std::vector <bool> (m, false));
        graph.resize(n * m);
        isEntry.resize(n*m, false);
        fin >> sx >> sy;
        sx -= 1;
        sy -= 1;
        int foxes;
        fin >> foxes;
        for(int i = 0; i < foxes; i ++) {
            int x, y, p;
            fin >> x >> y >> p;
            x -= 1;
            y -= 1;
            blockCells(x, y, p);
        }

        fin >> edges;
        for(int e = 0; e < edges; e ++) {
            int x1, y1, x2, y2;
            fin >> x1 >> y1 >> x2 >> y2;
            x1 -= 1;
            y1 -= 1;
            x2 -= 1;
            y2 -= 1;
            graph[x1*m+y1].push_back(x2*m+y2);
            graph[x2*m+y2].push_back(x1*m+y1);
            isEntry[x1*m+y1] = true;
            isEntry[x2*m+y2] = true;
        }
    }
    void solveTask1() {
        std::vector <int> dist(n*m, 1e9);

        std::queue <int> q;
        q.push(sx*m+sy);
        dist[sx*m+sy] = 0;

        while(q.empty() == false) {
            int node = q.front();
            int i = node / m;
            int j = node % m;
            q.pop();

            if(isEntry[node]) {
                fout << i+1 << ' ' << j+1 << ' ' << dist[node] << '\n';
                return;
            }

            for(int k = 0; k < 4; k ++) {
                int ii = i + di[k];
                int jj = j + dj[k];
                if(0 <= ii and ii < n and 0 <= jj and jj < m and blocked[ii][jj] == false and dist[ii * m + jj] > dist[node] + 1) {
                    dist[ii * m + jj] = dist[node] + 1;
                    q.push(ii * m + jj);
                }
            }
        }
    }
    void solveTask2() {
        std::stack <int> ans;
        std::stack <int> path;
        std::unordered_map <int, bool> usedEdge;

        for(int node = 0; node < n*m; node ++ ){
            if(graph[node].empty() == false and blocked[node / m][node % m] == false) {
                path.push(node);
                break;
            }
        }

        while(path.empty() == false) {
            int node = path.top();
            if(graph[node].empty() == false) {
                int next = graph[node].back();
                graph[node].pop_back();
                if(usedEdge[node * n * m + next] == false) {
                    usedEdge[node * n * m + next] = true;
                    usedEdge[next * n * m + node] = true;
                    path.push(next);
                }
            } else {
                path.pop();
                ans.push(node);
            }
        }

        while(ans.empty() == false){
            fout << ans.top() / m + 1 << ' ' << ans.top() % m + 1 << '\n';
            ans.pop();
        }
    }

public:
    void solve() {
        fin.open("cartite.in");
        fout.open("cartite.out");

        this->readInput();
        if(task == 1) {
            this->solveTask1();
        }
        else {
            this->solveTask2();
        }

        fin.close();
        fout.close();
    }
};

//https://leetcode.com/problems/valid-arrangement-of-pairs/submissions/
class ValidArrangements {
    std::ifstream fin;
    std::ofstream fout;
public:
    std::vector<std::vector<int>> validArrangement(std::vector<std::vector<int>>& pairs) {
        std::unordered_map <int, int> norm;
        std::unordered_map <int, int> revNorm;
        int index = 0;
        for(auto& p: pairs) {
            for(int& x: p) {
                if(norm[x] == 0) {
                    norm[x] = ++index;
                    revNorm[index] = x;
                }
                x = norm[x];
            }
        }
        int n = index + 1;

        std::vector <std::vector <int>> graph(n);
        std::vector <int> in(n, 0), out(n, 0);
        for(auto& p: pairs) {
            graph[p[0]].push_back(p[1]);
            out[p[0]] ++;
            in[p[1]] ++;
        }

        std::stack <int> path;
        std::vector <int> ans;

        for(int i = 0; i < n; i ++) {
            if(in[i] == out[i] - 1) {
                path.push(i);
                break;
            }
        }
        if(path.empty() == true) {
            path.push(1);
        }

        std::unordered_map <long long, bool> usedEdge;

        while(path.empty() == false) {
            int node = path.top();
            if(graph[node].empty() == false) {
                int next = graph[node].back();
                graph[node].pop_back();
                if(usedEdge[1LL * node * n + next] == false) {
                    usedEdge[1LL * node * n + next] = true;
                    path.push(next);
                }
            }
            else {
                path.pop();
                ans.push_back(node);
            }
        }

        std::vector <std::vector <int>> ret;

        for(int i = 1; i < ans.size(); i ++) {
            ret.push_back({revNorm[ans[i]], revNorm[ans[i-1]]});
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    void solve() {
        fin.open("input.txt");
        fout.open("output.txt");

        int n;
        fin >> n;
        std::vector <std::vector <int>> v(n, std::vector<int>(2));
        for(int i = 0; i < n; i ++) {
            fin >> v[i][0] >> v[i][1];
        }

        auto ans = validArrangement(v);
        for(auto x: ans) {
            fout << x[0] << ' ' << x[1] << " - ";
        }

        fin.close();
        fout.close();

    }
};

class Dinic {
    const int inf = 1e9;
    struct FlowEdge {
        int from, to;
        int cap, flow = 0;
        FlowEdge(int from, int to, int cap): from(from),to(to), cap(cap) {}
    };

    int n, m = 0;
    int start, finish;
    std::vector <FlowEdge> edges;
    std::vector <std::vector <int>> adj;
    std::vector <int> level, index;

    bool bfs() {
        std::fill(level.begin(), level.end(), -1);
        level[start] = 0;
        std::queue <int> q;
        q.push(start);

        while(q.empty() == false) {
            int node = q.front();
            q.pop();

            for(int i: adj[node]) {
                if(edges[i].cap <= edges[i].flow) {
                    continue;
                }
                if(level[edges[i].to] != -1) {
                    continue;
                }
                level[edges[i].to] = level[node] + 1;
                q.push(edges[i].to);
            }
        }

        return (level[finish] != -1);
    }

    int dfs(int node, int currentFlow) {
        if(currentFlow <= 0) {
            return 0;
        }
        if(node == finish) {
            return currentFlow;
        }

        for(; index[node] < adj[node].size(); index[node] ++) {
            int id = adj[node][index[node]];
            int next = edges[id].to;

            if(level[node] + 1 != level[next]) {
                continue;
            }
            if(edges[id].cap <= edges[id].flow) {
                continue;
            }

            int newFlow = dfs(next, std::min(currentFlow, edges[id].cap - edges[id].flow));
            if(newFlow == 0) {
                continue;
            }

            edges[id].flow += newFlow;
            edges[id^1].flow -= newFlow;
            return newFlow;
        }
        return 0;
    }

    void minCutDfs(int node, std::vector <bool>& visited) {
        visited[node] = true;
        for(int i: adj[node]) {
            int next = edges[i].to;
            if(edges[i].cap <= edges[i].flow) {
                continue;
            }
            if(visited[next] == false) {
                minCutDfs(next, visited);
            }
        }
    }

public:

    Dinic(int n, int start, int finish): n(n), start(start), finish(finish) {
        adj.resize(n);
        level.resize(n);
        index.resize(n);
    }

    void addEdge(int from, int to, int cap) {
        edges.emplace_back(from, to, cap);
        edges.emplace_back(to, from, 0);
        adj[from].push_back(m);
        adj[to].push_back(m+1);
        m += 2;
    }

    int flow(int steps = 1e9) {
        int f = 0;
        while(steps > 0) {
            if(bfs() == false) {
                break;
            }

            std::fill(index.begin(), index.end(), 0);
            while(steps) {
                int current = dfs(start, inf);
                if(current  == 0) {
                    break;
                }
                steps -= 1;
                f += current;
            }
        }

        return f;
    }

    std::vector <FlowEdge> getEdges() {
        return this->edges;
    }


    std::pair <std::vector <int> , std::vector <int>> getMinCut() {
        std::vector <bool> visited(n, false);
        minCutDfs(start, visited);
        std::pair <std::vector <int> , std::vector <int>> ret;
        for(int i = 0; i < n; i ++) {
            if(visited[i]) {
                ret.first.push_back(i);
            }
            else {
                ret.second.push_back(i);
            }
        }
        return ret;
    }
};

class Harta {
    std::ifstream fin;
    std::ofstream fout;

    int n;
    std::vector <int> in, out;

    void readInput() {
        fin >> n;
        in.resize(n);
        out.resize(n);
        for(int i = 0; i < n; i ++) {
            fin >> in[i] >> out[i];
        }
    }
public:
    void solve() {
        fin.open("harta.in");
        fout.open("harta.out");

        this->readInput();

        Dinic graph(2*n+2, 0, 2*n+1);
        for(int i = 0; i < n; i ++) {
            graph.addEdge(0, i+1, in[i]);
            graph.addEdge(n+i+1, 2*n+1, out[i]);
            for(int j = 0; j < n; j ++) {
                if(i == j) {
                    continue;
                }
                graph.addEdge(i+1, n+j+1, 1);
            }
        }

        fout << graph.flow() << '\n';

        auto edges = graph.getEdges();
        for(auto e: edges) {
            if(e.flow > 0 and 1 <= e.from and e.from <= n and n+1 <= e.to and e.to <= 2*n)
            fout << e.from << ' ' << e.to - n << '\n';
        }

        fin.close();
        fout.close();
    }
};

class Negot {
    std::ifstream fin;
    std::ofstream fout;

    int n, m, k;


public:
    void solve() {
        fin.open("negot.in");
        fout.open("negot.out");

        fin >> n >> m >> k;

        Dinic graph(n+m+2, 0, n+m+1);


        for(int i = 0; i < n; i ++) {
            graph.addEdge(0, i+1, k);
            int cnt, s;
            fin >> cnt;
            while(cnt --) {
                fin >> s;
                graph.addEdge(i+1, n+s, 1);
            }
        }
        for(int i = 0; i < m; i ++) {
            graph.addEdge(n+i+1, n+m+1, 1);
        }

        fout << graph.flow() << '\n';

        fin.close();
        fout.close();
    }
};

class Senat {
    std::ifstream fin;
    std::ofstream fout;
public:
    void solve() {
        fin.open("senat.in");
        fout.open("senat.out");

        int sen, com;
        fin >> sen >> com;
        Dinic graph(sen + com + 2, 0, sen + com + 1);

        fin.get();

        for(int i = 0; i < sen; i ++) {
            graph.addEdge(com + i + 1, com + sen + 1, 1);
        }

        for(int i = 0; i < com; i ++) {
            graph.addEdge(0, i + 1, 1);

            std::string line;
            std::getline(fin, line);
            line.push_back(' ');
            int value = 0;
            for(auto chr: line) {
                if(isdigit(chr)) {
                    value = 10 * value + chr - '0';
                }
                else if(value){
                    graph.addEdge(i + 1, com + value, 1);
                    value = 0;
                }
            }
        }

        if(graph.flow() == com) {
            std::vector <int> ans(com);
            auto edges  = graph.getEdges();
            for(auto e: edges) {
                if(1 <= e.from and e.from <= com and e.flow == 1) {
                    ans[e.from - 1] = e.to - com;
                }
            }
            for(auto i: ans) {
                fout << i << '\n';
            }
        }
        else {
            fout << 0 << '\n';
        }

        fin.close();

        fout.close();
    }
};

class Paznici {
    std::ifstream fin;
    std::ofstream fout;

public:
    void solve() {
        fin.open("paznici.in");
        fout.open("paznici.out");

        int n, m;
        fin >> n >> m;
        Dinic graph(n+m+2, 0, n+m+1);

        for(int i = 0; i < n; i ++) {
            graph.addEdge(0, i+1, 1);
        }
        for(int i = 0; i < m; i ++) {
            graph.addEdge(n+i+1, n+m+1, 1);
        }

        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                char chr;
                fin >> chr;
                if(chr == '1') {
                    graph.addEdge(i+1, n+j+1, 1);
                }
            }
        }
        std::vector <char> ans;
        graph.flow();
        auto edges = graph.getEdges();

        auto minCutPart = graph.getMinCut();
        std::vector <bool> isLeftSide(n+m+2, false);
        for(auto node: minCutPart.first) {
            isLeftSide[node] = true;
        }

        for(auto e: edges) {
            if(1 <= e.from and e.from <= n and e.flow == 1) {
                if(isLeftSide[e.from] == false)
                    ans.push_back(e.from + 'A' - 1);
                if(isLeftSide[e.to] == true)
                    ans.push_back(e.to - n + 'a' - 1);
            }
        }
        std::sort(ans.begin(), ans.end());
        for(auto i: ans) {
            fout << i;
        }

        fin.close();
        fout.close();
    }
};

class Ghizi {
    std::ifstream fin;
    std::ofstream fout;

public:
    void solve() {
        fin.open("ghizi.in");
        fout.open("ghizi.out");

        int n, k;
        fin >> n >> k;
        Dinic graph(101, 0, 100);
        std::vector <int> p[101][101];
        for(int i = 0; i < n; i ++) {
            int l, r;
            fin >> l >> r;
            graph.addEdge(l, r, 1);
            p[l][r].push_back(i+1);
        }

        graph.flow(k);
        auto edges = graph.getEdges();
        std::vector <int> ans;

        for(auto e: edges) {
            if(e.flow == 1) {
                ans.push_back(p[e.from][e.to].back());
                p[e.from][e.to].pop_back();
            }
        }

        std::sort(ans.begin(), ans.end());
        fout << ans.size() << '\n';
        for(auto i: ans) {
            fout << i << ' ';
        }

        fin.close();
        fout.close();
    }
};

//https://leetcode.com/problems/find-the-shortest-superstring/submissions/
class SuperString {
    std::ifstream fin;
    std::ofstream fout;

    int n;
    std::vector <std::vector <int>> overlap;

    void computeOverlap(std::vector <std::string>& words) {
        n = words.size();
        overlap.resize(n, std::vector <int>(n));

        for(int i = 0; i < n; i ++){
            for(int j = 0; j < n; j++) {
                if(i == j) {
                    continue;
                }
                bool foundOverlap = false;
                for(int start = std::max(0, int(words[i].size() - words[j].size())); start < words[i].size(); start ++) {
                    foundOverlap = true;
                    for(int k = 0; start + k < words[i].size(); k ++) {
                        if(words[i][start+k] != words[j][k]) {
                            foundOverlap = false;
                            break;
                        }
                    }

                    if(foundOverlap) {
                        overlap[i][j] = words[i].size() - start;
                        break;
                    }
                }
            }
        }

//        for(int i = 0; i < n; i ++) {
//            for(int j = 0; j < n; j ++) {
//                fout << overlap[i][j] << ' ';
//            }
//            fout << '\n';
//        }
    }

public:
    std::string shortestSuperstring(std::vector<std::string>& words) {
        computeOverlap(words);

        int n = words.size();
        std::vector <std::vector <int>> dp(n, std::vector <int>((1<<n), 0));

        for(int mask = 0; mask < (1<<n); mask ++) {
            for(int last = 0; last < n; last ++) {
                if((mask & (1<<last)) == 0) {
                    continue;
                }
                for(int i = 0; i < n; i ++) {
                    if(i == last or (mask & (1<<i)) == 0) {
                        continue;
                    }
                    dp[last][mask] = std::max(dp[last][mask], dp[i][mask ^ (1 << last)] + overlap[i][last]);
                }
            }
        }
        int max = -1, imax;
        for(int i = 0; i < n; i ++) {
            if(max < dp[i][(1<<n) - 1]) {
                max = dp[i][(1<<n) - 1];
                imax = i;
            }
        }

        std::vector <int> ans;

        for(int mask = (1<<n)-1; mask > 0; ) {
            ans.push_back(imax);
            int newmask = mask ^ (1<<imax);
            for(int i = 0; i < n; i++) {
                if((newmask & (1<<i)) != 0 and dp[i][mask ^ (1<<imax)] + overlap[i][imax] == dp[imax][mask]) {
                    imax = i;
                    break;
                }
            }
            mask = newmask;
        }

        std::reverse(ans.begin(), ans.end());

        std::string ret = words[ans[0]];
        for(int i = 1; i < ans.size(); i ++) {
            for(int j = overlap[ans[i-1]][ans[i]]; j < words[ans[i]].size(); j ++) {
                ret.push_back(words[ans[i]][j]);
            }
        }

        return ret;
    }

    void solve() {
        fin.open("input.txt");
        fout.open("output.txt");

        int n;
        fin >> n;
        std::vector <std::string> v(n);
        for(int i = 0; i < n; i ++) {
            fin >> v[i];
        }

        fout << this->shortestSuperstring(v) << '\n';

        fin.close();
        fout.close();
    }
};

int main() {
    ShortestPath().solve();
    return 0;
}
