#include <bits/stdc++.h>
#include "BinomialHeap.h"


int main() {
    std::ifstream fin("mergeheap.in");
    std::ofstream fout("mergeheap.out");
    int n, q;
    fin >> n >> q;

    BinomialHeap heap[n];

    while(q--) {
        int type, a, b;
        fin >> type;
        if(type == 1) {
            fin >> a >> b;
            heap[a-1].addValue(-b);
        }
        else if(type == 2) {
            fin >> a;
            fout << -heap[a-1].getMin() << '\n';
            heap[a-1].deleteMin();
        }
        else {
            fin >> a >> b;
            heap[a-1].unionHeap(heap[b-1]);
            heap[b-1] = BinomialHeap();
        }


    }

    return 0;
}