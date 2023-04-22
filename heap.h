#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <iostream>
#include "invGenerator.h"
using namespace std;

struct node
{
	int id;
    string city;
    string state;
    int qty_on_hand;
	node* parent;
	node* leftChild;
	node* rightChild;
};

class Heap {
    private:
        node* root;
        node* tail;
        int count;
        int check(node* node);
        void destroy(node* node);
        void swap(node* n1, node* n2);
        void heapify();
        void heapify(node* lowest);
    public:
        Heap();
        ~Heap();
        void restock(int amount); //restocks the item
        void enqueue(node* n);
        node* dequeue();
        void addItem(string city, string state, int qoh);
        void setTail(node* n);
        void printItems();
        void printItems(node* node);
};

Heap::Heap() {
    root = nullptr;
    tail = nullptr;
    count = 0;
}

int Heap::check(node* node) {
	if (node->leftChild != nullptr && node->rightChild != nullptr) {
		return 3;
	} 
	if (node->rightChild != nullptr) {
		return 2;
	} 
	if (node->leftChild != nullptr) {
		return 1;
	} 
	return 0;
}

void Heap::destroy(node* node)
{
	switch (check(node))
	{
	case 3:
		destroy(node->leftChild);
		destroy(node->rightChild);
		break;
	
	case 2:
		destroy(node->rightChild);
		break;
	
	case 1:
		destroy(node->leftChild);
		break;

	default:
		delete node;
		break;
	}
}

void Heap::swap(node* n1, node* n2) {
    cout << "swaping" << endl;
    node* parent = n1->parent;
    node* right = n1->rightChild;
    node* left = n1->leftChild;
    
    n1->parent = n2->parent;
    n1->leftChild = n2->leftChild;
    n1->rightChild = n2->leftChild;
    n1->rightChild->parent = n1;
    n1->leftChild->parent = n1;
    if (n1->parent->leftChild == n2) {
        n1->parent->leftChild = n1;
    } else if (n1->parent->rightChild == n2) {
        n1->parent->rightChild = n1;
    }

    n2->parent = parent;
    n2->rightChild = right;
    n2->leftChild = left;
    if (n2->parent->leftChild == n1) {
        n2->parent->leftChild = n2;
    } else if (n1->parent->rightChild == n1) {
        n2->parent->rightChild = n2;
    }

}

void Heap::heapify(node* lowest) {
    node* n = lowest;
    cout << "testing heap" << endl;
    if (n->leftChild != nullptr && n->leftChild->qty_on_hand <= n->qty_on_hand) {
        cout << "left fault" << endl;
        n = n->leftChild;
    }

    if (n->rightChild != nullptr && n->rightChild->qty_on_hand <= n->qty_on_hand) {
        cout << "right fault" << endl;
        n = n->rightChild;
    }

    if (n != lowest) {
        swap(lowest, n);

        heapify(lowest);
    }
}

void Heap::heapify() {
    heapify(root);
}

Heap::~Heap() {
    destroy(root);
}

void Heap::setTail(node* n) {
    cout << "setting tail" << endl;
    if(n->parent == nullptr) {
        tail = n;

        while(tail->leftChild != nullptr) {
            tail = tail->leftChild;
        }
    } else if(n->parent->leftChild == n) {
        tail = n->parent->rightChild;

        while(tail->leftChild != nullptr) {
            tail = tail->leftChild;
        }
    } else if(n->parent->rightChild == n) {
        setTail(n->parent);
    }
}

node* Heap::dequeue() {
    node* n = root;
    root = tail;
    node* parent = root->parent;
    if (parent->rightChild == root) {
        parent->rightChild = nullptr;
    } else {
        parent->leftChild = nullptr;
    }
    root->parent = nullptr;
    root->leftChild = n->leftChild;
    root->leftChild->parent = root;
    root->rightChild = n->rightChild;
    root->rightChild->parent = root;
    setTail(root);
    return n;
}

void Heap::enqueue(node* n) {
    cout << "enqueuing " << n->id;
    if (root == nullptr) {
        cout << " root" << endl;
        root = n;
        tail = root;
        return;
    }

    if (tail->leftChild == nullptr) {
        cout << " left" << endl;
        tail->leftChild = n;
        n->parent = tail;
        heapify();
        cout << "heapify finished" << endl;
    } else {
        cout << " right" << endl;
        tail->rightChild = n;
        n->parent = tail;
        heapify();
        cout << "heapify finished" << endl;
        setTail(tail);
    }
}

void Heap::restock(int amount) {
    node* n = dequeue();
    n->qty_on_hand += amount;
    enqueue(n);
}

void Heap::addItem(string city, string state, int qoh) {
    node* n = new node;
    n->id = ++count;
    n->city = city;
    n->state = state;
    n->qty_on_hand = qoh;
    enqueue(n);
}

void Heap::printItems(node* node) {
    cout << node->id  << " : " << node->qty_on_hand << endl;
    printItems(node->leftChild);
    printItems(node->rightChild);
}

void Heap::printItems() {
    printItems(root);
}
#endif