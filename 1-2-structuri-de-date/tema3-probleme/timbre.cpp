#include <bits/stdc++.h>

std::ifstream fin ("timbre.in");
std::ofstream fout ("timbre.out");

class Heap{

int size;
std::vector <int> heap;

public:
    Heap (){
        size = 0;
        heap.clear();
    }

    void insert (int value){
        heap.push_back (value);
        size ++;
        propagateUp (size-1);
    }

    void propagateUp (int node){
        if (node == 0)
            return;
        int parent = (node-1) / 2;
        if (heap[parent] > heap[node]){
            std::swap (heap[parent], heap[node]);
            propagateUp(parent);
        }
    }

    void erase (){
        heap[0] = heap[--size];
        heap.pop_back();
        propagateDown (0);
    }

    void propagateDown (int node){
        int left = 2*node+1;
        int right = 2*node+2;
        int next = node;
        if (left < size and heap[next] > heap[left])
            next = left;
        if (right < size and heap[next] > heap[right])
            next = right;

        if (next != node){
            std::swap (heap[next], heap[node]);
            propagateDown(next);
        }
    }

    int findMin (){
        return heap[0];
    }

};

struct Intervals{
    int end, cost;
};

bool sortIntervals (Intervals a, Intervals b){
    return a.end > b.end;
}

int main()
{
    int n, m, k, ans=0, crt=0, i;
    fin >> n >> m >> k;
    struct Intervals v[m];

    for (i=0; i<m; i++)
        fin >> v[i].end >> v[i].cost;

    std::sort (v, v+m, sortIntervals);

    class Heap H;

    while (n > 0){
        while (crt < m and v[crt].end >= n){
            H.insert (v[crt].cost);
            crt ++;
        }
        ans = ans + H.findMin ();
        n -= k;
        H.erase();
    }

    fout << ans << '\n';

    return 0;
}
