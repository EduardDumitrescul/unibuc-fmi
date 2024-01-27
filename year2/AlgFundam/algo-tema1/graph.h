//
// Created by Eduard on 10/27/2023.
//

#include <iostream>
#include <vector>

#include <stack>

class Graph {
    int v;
    std::vector <std::vector <int>> adj;
    std::vector <int> value;

    /**
     *
     * @return A char array representing the coloring of the graph if it is bipartite, or an empty array otherwise
     */
    std::vector <char> checkBipartite() {
        std::vector <char> color(v, 0);
        for(int node = 0; node < this->v; node ++) {
            if(color[node] == 0) {
                color[node] = 1;
                if(!this->dfsWithColoring(node, color)) {
                    return {};
                }
            }
        }
        return color;
    }

    /**
     * Dfs traversing of the graph while trying to color the nodes using two colors, such that no two adjacent noeds have
     * the same color
     * @param node
     * @param color
     * @return true - the coloring is successful\n
     * false - otherwise
     */
    bool dfsWithColoring(int node, std::vector <char>& color) {
        for(int next: this->adj[node]) {
            if(color[node] == color[next]) {
                return false;
            }
            if(color[next] == 0) {
                color[next] = 3 - color[node];
                if(!this->dfsWithColoring(next, color)) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     *
     * @param node
     * @param visited
     * @param nodeStack a stack that will contain the nodes in inverse topological order
     */
    void dfsTopological(int node, std::vector <bool> &visited, std::stack <int>& nodeStack) {
        visited[node] = true;

        for(int next: adj[node]) {
            if(visited[next] == false) {
                dfsTopological(next, visited, nodeStack);
            }
        }
        nodeStack.push(node);
    }
    /**
     *
     * @return a vector of nodes in topological order if exists, otherwise an empty vector
     */
    std::vector <int> findTopologicalOrder() {
        std::vector <bool> visited(this->v, false);
        std::stack <int> nodeStack;
        for(int node = 0; node < this->v; node ++) {
            if(visited[node] == false) {
                dfsTopological(node, visited, nodeStack);
            }
        }

        std::vector <int> solution;
        std::vector <int> pos(this->v);
        while(nodeStack.empty() == false) {
            solution.push_back(nodeStack.top());
            pos[nodeStack.top()] = solution.size() - 1;
            nodeStack.pop();
        }
        if(solution.size() != this->v) {
            return {};
        }
        for(int node = 0; node < this->v; node ++) {
            for(int next: this->adj[node]) {
                if(pos[node] > pos[next]) {
                    return {};
                }
            }
        }
        return solution;
    }
    /**
     *
     * @return a vector containing all bridges in the graph (stored as 2-element vectors)
     */
    std::vector <std::vector <int>> findBridges() {
        std::vector <std::vector <int>> bridges;
        std::vector <bool> visited(this->v, false);
        std::vector <int> tin(this->v, 0);
        std::vector <int> low(this->v, 0);

        for(int node = 0; node < this->v; node ++) {
            if(visited[node] == false) {
                dfsBridges(node, -1, 0, visited, tin, low, bridges);
            }
        }

        return bridges;
    }

    /**
     *
     * @param node
     * @param parent
     * @param time
     * @param visited
     * @param tin entry time of the node
     * @param low lowest entry time from a node with the possibility of using one back-edge
     * @param bridges
     */
    void dfsBridges(int node, int parent, int time, std::vector <bool> &visited, std::vector <int>& tin, std::vector <int>& low,
                    std::vector <std::vector <int>>& bridges) {
        visited[node] = true;
        tin[node] = time;
        low[node] = time;

        for(int next: adj[node]) {
            if(next == parent) {
                continue;
            }
            if(visited[next] == true) {
                low[node] = std::min(low[node], tin[next]);
            }
            else {
                dfsBridges(next, node, time+1, visited, tin, low, bridges);
                low[node] = std::min(low[node], low[next]);

                if(low[next] > tin[node]) {
                    bridges.push_back({node, next});
                }
            }
        }
    }

    /**
     *
     * @param node
     * @param visited
     * @param onStack
     * @return true if there is a cycle reachable from the starting node, false otherwise
     */
    bool dfsCheckCycles(int node, std::vector <bool>& visited, std::vector <bool>& onStack) {
        visited[node] = true;
        onStack[node] = true;

        for(int next: adj[node]) {
            if(onStack[next] == true) {
                return true;
            }
            if(visited[next] == false) {
                if(dfsCheckCycles(next, visited, onStack) == true) {
                    return true;
                }
            }
        }
        onStack[node] = false;
        return false;
    }

    void dfsConnectedComponent(int node, std::vector <bool>& visited, std::vector <int>& nodes) {
        visited[node] = true;
        nodes.push_back(node);

        for(int next: this->adj[node]) {
            if(visited[next] == false) {
                dfsConnectedComponent(next, visited, nodes);
            }
        }
    }

    void fill(int node, std::vector <bool>& visited, std::vector <int>& list) {
        visited[node] = true;
        list.push_back(node);
        for(int next: this->adj[node]) {
            if(visited[next] == false and this->value[node] == this->value[next]) {
                this->fill(next, visited, list);
            }
        }
    }

public:
    /**
     * @param v number of vertices
     * @param edges vector of edges, stored as vectors with 2 elements.
     * (The nodes must be 0-indexed)
     */
    Graph(int v, const std::vector <std::vector <int>>& edges, bool directed = false, const std::vector <int>& value = {}):
            v(v), value(value){
        this->adj.resize(this->v);
        for(const std::vector<int>& edge: edges) {
            this->adj[edge[0]].push_back(edge[1]);
            if(directed == false) {
                this->adj[edge[1]].push_back(edge[0]);
            }
        }
    }

    Graph(const std::vector <std::vector <int>>& adj): adj(adj) {
        this->v = adj.size();
    }

    bool isBipartite() {
        std::vector <char> color = this->checkBipartite();
        return !color.empty();
    }

    std::vector <char> getBipartiteColoring() {
        return this->checkBipartite();
    }

    std::vector <int> getTopologicalOrder() {
        return this->findTopologicalOrder();
    }

    std::vector <std::vector <int>> getBridges() {
        return this->findBridges();
    }


    /**
     * Check which nodes from the directed graph have a path towards a cycle
     * @return a boolean array that for every node tells if it can reach a cycle
     */
    std::vector <bool> nodesCanReachCycle() {
        std::vector <bool> visited(this->v, false);
        std::vector <bool> onStack(this->v, false);

        for(int node = 0; node < this->v; node ++) {
            if(visited[node] == false) {
                dfsCheckCycles(node, visited, onStack);
            }
        }

        std::vector <bool> canReachCycle(this->v, false);

        for(int node = 0; node < this->v; node ++) {
            if(onStack[node] == true) {
                canReachCycle[node] = true;
            }
        }

        return canReachCycle;
    }

    std::vector <int> getConnectedVerticesWithSameValue(int node) {
        std::vector <bool> visited(this->v, false);
        std::vector <int> list;

        this->fill(node, visited, list);

        return list;
    }
    /**
     * Calculates the minimum distance between a node from the list of starting nodes to any of the nodes in the list
     * of end nodes
     * @param startNodes
     * @param endNodes
     * @return
     */
    int getMinDistanceBetweenGroups(const std::vector <int>& startNodes, const std::vector <int>& endNodes) {
        std::vector <int> dist(this->v, 1e9);
        std::vector <int> isEndNode(this->v, false);
        std::deque <int> dq;
        for(int node: startNodes) {
            dist[node] = 0;
            dq.push_back(node);
        }

        for(int node: endNodes) {
            isEndNode[node] = true;
        }

        while(dq.empty() == false) {
            int node = dq.front();
            if(isEndNode[node] == true) {
                return dist[node];
            }
            dq.pop_front();

            for(int next: this->adj[node]) {
                if(dist[next] > dist[node] + 1) {
                    dist[next] = dist[node] + 1;
                    dq.push_back(next);
                }
            }
        }
        return -1;
    }

    std::pair <int, int> getMaxDistanceBetweenGroups(const std::vector <int>& startNodes, const std::vector <int>& endNodes) {
        std::vector <int> dist(this->v, 1e9);
        std::vector <int> isEndNode(this->v, false);
        std::deque <int> dq;
        for(int node: startNodes) {
            dist[node] = 0;
            dq.push_back(node);
        }

        for(int node: endNodes) {
            isEndNode[node] = true;
        }

        while(dq.empty() == false) {
            int node = dq.front();
            dq.pop_front();

            for(int next: this->adj[node]) {
                if(dist[next] > dist[node] + 1) {
                    dist[next] = dist[node] + 1;
                    dq.push_back(next);
                }
            }
        }
        int node = endNodes[0];
        for(int i = 1; i < endNodes.size(); i ++) {
            if(dist[node] < dist[endNodes[i]]) {
                node = endNodes[i];
            }
        }

        return {dist[node], node};
    }

    std::vector <std::vector <int>> getConnectedComponents() {
        std::vector <bool> visited(this->v, false);
        std::vector <std::vector <int>> connectedComponents;

        for(int node = 0; node < this->v; node ++) {
            if(visited[node] == false) {
                std::vector <int> nodes;
                this->dfsConnectedComponent(node, visited, nodes);
                connectedComponents.push_back(nodes);
            }
        }

        return connectedComponents;
    }

};

/* LeetCode -  https://leetcode.com/problems/possible-bipartition/

 class Solution {

public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        for(auto& it: dislikes) {
            it[0] --;
            it[1] --;
        }

        Graph g(n, dislikes);
        return g.isBipartite();
    }

};

 */

/* LeetCode - https://leetcode.com/problems/course-schedule-ii/

 class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        for(auto& it: prerequisites) {
            std::swap(it[0], it[1]);
        }

        Graph g(numCourses, prerequisites, true);
        return g.getTopologicalOrder();
    }
};

 */


/* LeetCode - https://leetcode.com/problems/critical-connections-in-a-network

 class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        Graph g(n, connections);
        return g.getBridges();
    }
};

 */


/* LeetCode - https://leetcode.com/problems/find-eventual-safe-states/

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        Graph g(graph);
        std::vector <bool> canReachCycle = g.nodesCanReachCycle();

        std::vector <int> sol;
        for(int node = 0; node < graph.size(); node ++) {
            if(canReachCycle[node] == false) {
                sol.push_back(node);
            }
        }

        return sol;
    }
};

 */


/* LeetCode - https://leetcode.com/problems/shortest-bridge/
    class Solution {

public:
    int shortestBridge(vector<vector<int>>& grid) {
        std::vector <std::vector <int>> edges;
        int n = grid.size();
        std::vector <int> value(n*n, 0);
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < n; j ++) {
                value[i*n+j] = grid[i][j];
                if(i > 0) {
                    edges.push_back({(i-1)*n+j, i*n+j});
                }
                if(j > 0) {
                    edges.push_back({i*n+j-1, i*n+j});
                }
            }
        }

        Graph g(n*n, edges, false, value);

        std::vector <int> startNodes;
        std::vector <int> endNodes;
        std::vector <bool> visited(n*n, false);

        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < n; j ++) {
                if(grid[i][j] == 1 and startNodes.empty() == true) {
                    startNodes = g.getConnectedVerticesWithSameValue(i*n+j);
                    for(auto node: startNodes) {
                        visited[node] = true;
                    }
                }
                else if (grid[i][j] == 1 and visited[i*n+j] == false) {
                    endNodes = g.getConnectedVerticesWithSameValue(i*n+j);
                    i = j = n;
                }
            }
        }

        std::cout << startNodes.size() << " " << endNodes.size() << '\n';

        return g.getDistanceBetweenGroups(startNodes, endNodes) - 1;
    }
};

*/

/*
 LeetCode - https://leetcode.com/problems/satisfiability-of-equality-equations/

 class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        std::vector <std::vector <int>> edges;
        std::vector <std::vector <int>> diff;
        for(std::string eq: equations) {
            if(eq[1] == '=') {
                edges.push_back({eq[0] - 'a', eq[3] - 'a'});
            }
            else {
                diff.push_back({eq[0] - 'a', eq[3] - 'a'});
            }
        }

        Graph g(26, edges);
        std::vector <std::vector <int>> connComp = g.getConnectedComponents();

        std::vector <int> comp(26, 0);

        for(int i = 0; i < connComp.size(); i ++) {
            for(int node: connComp[i]) {
                comp[node] = i;
            }
        }

        for(auto it: diff) {
            if(comp[it[0]] == comp[it[1]]) {
                return false;
            }
        }

        return true;
    }
};

 */



/*
 Infoarena - https://www.infoarena.ro/problema/padure

 #include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")

// #define fin std::cin
// #define fout std::cout

std::ifstream fin("padure.in");
std::ofstream fout("padure.out");

class Padure {
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {-1, 0, 1, 0};

    bool inBounds(int n, int m, int i, int j) {
        return (0 <= i & i < n & 0 <= j & j < m);
    }

public:

    int solve(int n, int m, int sx, int sy, int fx, int fy, char** map) {
        std::queue <std::pair <int, int>> q[n+m];
        short int dist[n][m];
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                dist[i][j] = SHRT_MAX - 1;
            }
        }
        dist[sx][sy] = 0;

        q[0].push({sx, sy});

        for(int d = 0; d < n+m; d ++) {
            while(q[d].empty() == false) {
                int i = q[d].front().first;
                int j = q[d].front().second;
                q[d].pop();

                if(dist[i][j] != d)
                    continue;

                if(fx == i && fy == j) {
                    return dist[i][j];
                }

                for(int k = 0; k < 4; k ++) {
                    int ii = i + di[k];
                    int jj = j + dj[k];
                    if(inBounds(n, m, ii, jj) and dist[ii][jj] > dist[i][j] + (map[i][j] != map[ii][jj])) {
                        dist[ii][jj] = dist[i][j] + (map[i][j] != map[ii][jj]);
                        q[dist[ii][jj]].push({ii, jj});
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    int n, m, sx, sy, fx, fy;
    fin >> n >> m;
    fin >> sx >> sy >> fx >> fy;

    char** x;
    x = new char*[n];
    for(int i = 0; i < n; i ++) {
        x[i] = new char[m];
    }

    for(int i = 0; i < n; i ++)
    for(int j = 0; j < m; j ++) {
        int temp;
        fin >> temp;
        x[i][j] = temp;
    }


    fout << Padure().solve(n, m, sx-1, sy-1, fx-1, fy-1, x) << '\n';

    for(int i = 0; i < n; i ++) {
        delete x[i];
    }
    delete x;
    return 0;
}

 */


/*
 Codeforces - https://codeforces.com/contest/1144/problem/F

 int main() {
    int v, e;
    std::cin >> v >> e;
    std::vector <std::vector <int>> edges;
    for(int i = 0; i < e; i ++) {
        int a, b;
        std::cin >> a >> b;
        edges.push_back({a-1, b-1});
    }

    Graph g(v, edges);
    auto color = g.getBipartiteColoring();

    if(color.empty() == true) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES\n";
        for(auto edge: edges) {
            std::cout << int(color[edge[0]] == 1);
        }
    }
    return 0;
}

 */


/*
 Codeforces -  https://codeforces.com/contest/1881/problem/F

 int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t;
    std::cin >> t;
    while(t --) {
        int v, m;
        std::cin >> v >> m;
        std::vector <int> marked(m);
        std::vector <std::vector <int>> edges;
        for(int i = 0; i < m; i ++) {
            std::cin >> marked[i];
            marked[i] --;
        }

        for(int i = 0; i < v-1; i ++) {
            int a, b;
            std::cin >> a >> b;
            edges.push_back({a-1, b-1});
        }

        if(m <= 1) {
            std::cout << 0 << '\n';
            continue;
        }

        Graph g(v, edges);


       int start = marked.back();
       marked.pop_back();
        auto p = g.getMaxDistanceBetweenGroups({start}, marked);
        for(auto &it: marked) {
            if(it == p.second) {
                it = start;
                break;
            }
        }
        auto p2 = g.getMaxDistanceBetweenGroups({p.second}, marked);

        std::cout << (1 + p2.first) / 2 << '\n';
    }
}
 */



/* Infoarena - https://www.infoarena.ro/problema/patrol2


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
 */