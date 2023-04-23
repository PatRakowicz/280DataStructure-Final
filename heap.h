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
        int getRootQty();
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

int Heap::getRootQty() {
    return root->qty_on_hand;
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
    // cout << "swaping" << endl;
    int tmpId = n1->id;
    string tmpCity = n1->city;
    string tmpState = n1->state;
    int tmpQty = n1->qty_on_hand;

    n1->id = n2->id;
    n1->city = n2->city;
    n1->state = n2->state;
    n1->qty_on_hand = n2->qty_on_hand;

    n2->id = tmpId;
    n2->city = tmpCity;
    n2->state = tmpState;
    n2->qty_on_hand = tmpQty;
}

void Heap::heapify(node* lowest) {
    node* n = lowest;
    node* left = lowest->leftChild;
    node* right = lowest->rightChild;
    // cout << "testing heap at " << n->id << endl;
    if (left != nullptr && left->qty_on_hand < n->qty_on_hand) {
        // cout << "left fault" << endl;
        n = left;
    }

    if (right != nullptr && right->qty_on_hand < n->qty_on_hand) {
        // cout << "right fault" << endl; 
        n = right;
    }


    if (n != lowest) {
        swap(n, lowest);

        heapify(n);
    }
}

void Heap::heapify() {
    heapify(root);
}

Heap::~Heap() {
    destroy(root);
}

void Heap::setTail(node* n) {
    // cout << "setting tail" << endl;
    if (n->parent == nullptr) {
        tail = n;

        while (tail->leftChild != nullptr) {
            tail = tail->leftChild;
        }
    } else if (n->parent->leftChild == n) {
        tail = n->parent->rightChild;

        while (tail->leftChild != nullptr) {
            tail = tail->leftChild;
        }
    } else if (n->parent->rightChild == n) {
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
    // cout << "enqueuing " << n->id;
    if (root == nullptr) {
        // cout << " root" << endl;
        root = n;
        tail = root;
        return;
    }

    if (tail->leftChild == nullptr) {
        // cout << " left" << endl;
        tail->leftChild = n;
        n->parent = tail;
        heapify();
        // cout << "heapify finished" << endl;
    } else {
        // cout << " right" << endl;
        tail->rightChild = n;
        n->parent = tail;
        heapify();
        // cout << "heapify finished" << endl;
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
    n->parent = nullptr;
    n->leftChild = nullptr;
    n->rightChild = nullptr;
    enqueue(n);
}

void Heap::printItems(node* n) {
    if (n != nullptr) {
        cout << n->id  << " : " << n->qty_on_hand << endl;
        printItems(n->leftChild);
        printItems(n->rightChild);
    }
}

void Heap::printItems() {
    printItems(root);
}
#endif