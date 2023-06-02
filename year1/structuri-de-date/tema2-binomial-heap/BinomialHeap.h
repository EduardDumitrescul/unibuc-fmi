//
// Created by eduarddumitrescul on 4/18/23.
//

#ifndef SD_BINOMIAL_HEAP_BINOMIALHEAP_H
#define SD_BINOMIAL_HEAP_BINOMIALHEAP_H


#include <vector>
#include <ostream>
#include <list>

class BinomialHeap {
public:
    struct Node {
        long long value, degree;
        Node *child, *sibling, *parent;
    };

private:
    std::list <Node*> roots;


public:
    void print(std::ostream&) const;
    static void printTree(std::ostream&, Node*);
    static Node* newNode(long long value);
    static Node* mergeTrees(Node*, Node*);
    Node* findNode(Node*, long long);


    void insertTree(Node*);
    void unionHeap(std::list <Node*>);
    void unionHeap(const BinomialHeap& );
    void decreaseKey(Node*, long long, long long);


    void addValue(long long);

    long long getMin() const;
    void deleteMin();
    bool empty() const;

    ~BinomialHeap();
};


#endif //SD_BINOMIAL_HEAP_BINOMIALHEAP_H
