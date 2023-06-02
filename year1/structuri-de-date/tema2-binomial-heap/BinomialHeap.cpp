//
// Created by eduarddumitrescul on 4/18/23.
//

#include <algorithm>
#include "BinomialHeap.h"

void BinomialHeap::print(std::ostream &out) const{
    for(auto& it: this->roots) {
        BinomialHeap::printTree(out, it);
    }
}

void BinomialHeap::printTree(std::ostream &out, Node *node) {
    out << node->value << " " << node->degree << '\n';
    Node *it = node->child;
    while(it != nullptr) {
        BinomialHeap::printTree(out, it);
        it = it->sibling;
    }
}

BinomialHeap::Node *BinomialHeap::newNode(long long value) {
    Node *temp = new Node;
    temp->value = value;
    temp->degree = 0;
    temp->child = nullptr;
    temp->sibling = nullptr;
    temp->parent = nullptr;
    return temp;
}

BinomialHeap::Node *BinomialHeap::mergeTrees(BinomialHeap::Node *a, BinomialHeap::Node *b) {
    if(a->value < b->value) {
        std::swap(a, b);
    }
    a->sibling = b->child;
    a->parent = b;
    b->child = a;
    b->degree ++;

    return b;
}

void BinomialHeap::unionHeap(std::list<Node *> heap) {
    std::list <Node*> temp;
    std::list<Node*>::iterator i;
    std::list<Node*>::iterator j;
    i = this->roots.begin();
    j = heap.begin();

    Node* carry = nullptr;

    while(i != this->roots.end() and j != heap.end()){
        if(carry != nullptr) {
            if((*i)->degree == (*j)->degree and carry->degree) {
                temp.push_back(carry);
                carry = nullptr;
            }
            else if((*i)->degree == carry->degree) {
                carry = BinomialHeap::mergeTrees(*i, carry);
                i ++;
            }
            else if((*j)->degree == carry->degree) {
                carry = BinomialHeap::mergeTrees(*j, carry);
                j ++;
            }
            else {
                temp.push_back(carry);
                carry = nullptr;
            }
            continue;
        }

        if((*i)->degree == (*j)->degree) {
            carry = BinomialHeap::mergeTrees(*i, *j);
            i ++;
            j ++;
        }
        else if((*i)->degree < (*j)->degree) {
            temp.push_back(*i);
            i ++;
        }
        else {
            temp.push_back(*j);
            j ++;
        }
    }


    while(i != this->roots.end()) {
        if(carry != nullptr and (*i)->degree == carry->degree) {
            carry = BinomialHeap::mergeTrees(*i, carry);
            i ++;
        }
        else if(carry != nullptr) {
            temp.push_back(carry);
            carry = nullptr;
        }
        else {
            temp.push_back(*i);
            i ++;
        }
    }

    while(j != heap.end()) {
        if(carry != nullptr and (*j)->degree == carry->degree) {
            carry = BinomialHeap::mergeTrees(*j, carry);
            j ++;
        }
        else if(carry != nullptr) {
            temp.push_back(carry);
            carry = nullptr;
        }
        else {
            temp.push_back(*j);
            j ++;
        }
    }
    if(carry != nullptr) {
        temp.push_back(carry);
        carry = nullptr;
    }
    this->roots = temp;
//    for(auto it: this->roots) {
//        std::cout << it->degree << ' ';
//    }
//    std::cout << '\n';
}

void BinomialHeap::insertTree(BinomialHeap::Node *node) {
    std::list <Node*> temp;
    temp.push_back(node);
    this->unionHeap(temp);

}

void BinomialHeap::addValue(long long value) {
//    std::cout << "add\n";
    this->insertTree(BinomialHeap::newNode(value));
}

long long BinomialHeap::getMin() const {
    long long temp = INT64_MAX;
    for(auto& it: this->roots) {
        temp = std::min(temp, it->value);
    }
    return temp;
}



void BinomialHeap::deleteMin() {
//    std::cout << "delete\n";
    std::list <Node*> temp;
    long long min = this->getMin();
    Node* node = nullptr;
    for(auto& it: this->roots) {
        if(it->value == min) {
            node = it;
            this->roots.remove(it);
            break;
        }
    }

    if(node == nullptr) {
        return;
    }
//    int prevSize = 101;
//    int currentSize = 100;
    Node *it = node->child;
    while(it != nullptr) {
        temp.push_back(it);
//        prevSize = currentSize;
//        currentSize = it->degree;
//        if(prevSize <= currentSize) {
//            std::cout << "not ok\n";
//        }
        it = it->sibling;
    }
    std::reverse(temp.begin(), temp.end());
//    for(auto it: temp) {
//        std::cout << it->degree << ' ';
//    }
//    std::cout << '\n';

    this->unionHeap(temp);
}

bool BinomialHeap::empty() const {
    return this->roots.empty();
}

void BinomialHeap::unionHeap(const BinomialHeap& heap) {
    this->unionHeap(heap.roots);
}

BinomialHeap::~BinomialHeap() {
    for(auto &it: this->roots) {
        if(it != nullptr) {
            delete it;
            it = nullptr;
        }
    }
}

void BinomialHeap::decreaseKey(BinomialHeap::Node *root, long long int oldValue, long long int newValue) {
    Node *node = this->findNode(root, oldValue);
    if(node == nullptr or oldValue < newValue) {
        return;
    }
    node->value = newValue;
    while(node->parent != nullptr and node->parent->value > node->value) {
        std::swap(node->value, node->parent->value);
        node = node->parent;
    }
}

BinomialHeap::Node *BinomialHeap::findNode(BinomialHeap::Node *node, long long int value) {
    if(node == nullptr) {
        return nullptr;
    }
    if(node->value == value) {
        return node;
    }
    Node* result = this->findNode(node->child, value);
    if(result != nullptr) {
        return result;
    }
    return this->findNode(node->sibling, value);
}



