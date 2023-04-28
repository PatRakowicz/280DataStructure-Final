#ifndef HEAP_H
#define HEAP_H

#include <iostream>
// vector and string are included in invGenerator.h
#include "invGenerator.h"
using namespace std;

class Heap {
    private:
        vector<Pallet*> pq;
        int root;
        int tail;
        int pqLength;
        void swap(int i1, int n2);
        void setTail();
        bool checkQOH();
        bool checkQOH(int n);
        void enqueue(Pallet* p);
        Pallet* dequeue();
        void heapify();
        // void heapify(int lowest);
    public:
        Heap();
        ~Heap();
        int getRootQty();
        void addPallet(Pallet* p);
        void restock(int amount); //restocks the item
        void printItems(int n);
        void printItems();
};

Heap::Heap() {
    pq.clear();
    root = -1;
    tail = -1;
    pqLength = 0;
}

int Heap::getRootQty() {
    return pq[root]->qoh;
}

void Heap::swap(int i1, int i2) {
    // cout << "swaping" << endl;
    Pallet* tmp = pq[i1];
    // cout << "tmp : " << tmp->pallet_number << endl;
    pq[i1] = pq[i2];
    // cout << "i1 : " << pq[i1]->pallet_number << endl;
    // cout << "i2 : " << pq[i2]->pallet_number << endl;
    pq[i2] = tmp;
}

// void Heap::heapify(int lowest) {
//     if (lowest >= pqLength) {
//         return;
//     }
//     int n = lowest;
//     int left = (lowest*2)+1;
//     int right = (lowest*2)+2;
//     cout << "n " << pq[n]->pallet_number << " " << pq[n]->qoh << endl;
//     cout << "left " << pq[left]->pallet_number << " " << pq[left]->qoh << endl;
//     cout << "right " << pq[right]->pallet_number << " " << pq[right]->qoh << endl;
//     // cout << "testing heap at " << n->id << endl;
    
//     if (left < pqLength && pq[left]->qoh < pq[n]->qoh) {
//         // cout << "left fault" << endl;
//         n = left;
//     }
//     if (right < pqLength && pq[right]->qoh < pq[n]->qoh) {
//         // cout << "right fault" << endl; 
//         n = right;
//     } 
    
//     if (n != lowest) {
//         swap(n, lowest);

//         heapify(n);
//     } else {
//         heapify(right);
//         heapify(left);
//     }
// }

bool Heap::checkQOH(int n) {
    if (n >= pqLength) {
        // cout << "end\n";
        return true;
    }

    int left = (n*2)+1;
    int right = (n*2) + 2;

    if (left < pqLength && pq[left]->qoh < pq[n]->qoh) {
        // cout << "end\n";
        swap(left, n);
        return false;
    }

    if (right < pqLength && pq[right]->qoh < pq[n]->qoh) {
        // cout << "end\n";
        swap(right, n);
        return false;
    }

    return checkQOH(left) && checkQOH(right);
}

bool Heap::checkQOH() {
    return checkQOH(root);
}

void Heap::heapify() {
    while (!checkQOH()); // checkQOH checks to see if it is a heap if false it 
    // swaps the values that are incorrect until it is a heap
}

Heap::~Heap() {
    pq.clear();
    delete (&pq);
}

void Heap::setTail() {
    tail = pqLength - 1;    
}

Pallet* Heap::dequeue() {
    Pallet* tmp = pq[root];
    swap(root, tail);
    pqLength--;
    setTail();
    heapify();
    return tmp;
}

void Heap::enqueue(Pallet* p) {
    if (root == -1) {
        root = 0;
        pq.insert(pq.begin(), p);
        pqLength = 1;
    } else {
        pq.insert(pq.begin() + pqLength, p);
        pqLength++;
        heapify();
        setTail();
    }
}

void Heap::addPallet(Pallet* p) {
    enqueue(p);
}

void Heap::restock(int amount) {
    Pallet* n = dequeue();
    n->qoh += amount;
    enqueue(n);
}

void Heap::printItems(int n) {
    if (n < pqLength && n != -1) {
        cout << pq[n]->pallet_number  << " : " << pq[n]->qoh << endl;
        printItems((n*2)+1);
        printItems((n*2)+2);
    }
    
}

void Heap::printItems() {
    printItems(root);
}

#endif