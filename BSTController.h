//
// Created by Patrick on 22/04/2023.
//
/*
main Test
 	cout << "Testing Insertion and Balance:" << endl;
	testInsertionAndBalance();
	cout << endl;

	cout << "Testing Removal and Balance:" << endl;
	testRemovalAndBalance();
	cout << endl;

void printTree(Node *node, const string &prefix = "", bool isLeft = true) {
	if (node != nullptr) {
		cout << prefix;

		cout << (isLeft ? "|-" : "\\-");

		cout << "Pallet " << node->pallet.pallet_number << ", Height: " << node->height << endl;

		printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
		printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
	}
}

void testInsertionAndBalance() {
	const int NUM_PALLETS = 30;
	BST bst;

	InventoryGenerator generator("data.csv");
	for (int i = 1; i <= NUM_PALLETS; i++) {
		Pallet pallet = generator.generate_pallet(i);
		bst.insert(pallet);
		cout << "After inserting pallet " << i << ":" << endl;
		printTree(bst.getRoot());
		cout << endl;
	}
}

void testRemovalAndBalance() {
	const int NUM_PALLETS = 30;
	const int NUM_REMOVALS = 5;
	BST bst;

	InventoryGenerator generator("data.csv");
	for (int i = 1; i <= NUM_PALLETS; i++) {
		Pallet pallet = generator.generate_pallet(i);
		bst.insert(pallet);
	}

	cout << "Initial tree:" << endl;
	printTree(bst.getRoot());
	cout << endl;

	for (int i = 1; i <= NUM_REMOVALS; i++) {
		bst.remove(i);
		cout << "After removing pallet " << i << ":" << endl;
		printTree(bst.getRoot());
		cout << endl;
	}
}*/

#ifndef INC_280DATASTRUCTURE_FINAL_BSTCONTROLLER_H
#define INC_280DATASTRUCTURE_FINAL_BSTCONTROLLER_H

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include "invGenerator.h"

using namespace std;

struct Node {
	Pallet pallet;
	Node *left;
	Node *right;
	int height;

	Node(Pallet p) : pallet(p), left(nullptr), right(nullptr), height(1) {}
};

class BST {
public:
	BST() : root(nullptr) {}
	~BST() { deleteTree(root); }

	void insert(Pallet p) { root = insertHelper(root, p); }
	void remove(int pallet_number) { root = removeHelper(root, pallet_number); }

	Pallet find(int pallet_number);

	void printInorder() { printInorderHelper(root); }
	void printByLocation(const string &location, bool is_state);

	Node *getRoot() { return root; }

private:
	Node *root;
	void deleteTree(Node *node);

	Node *insertHelper(Node *node, Pallet p);
	Node *removeHelper(Node *node, int pallet_number);
	Node *findHelper(Node *node, int pallet_number);
	Node *minNode(Node *node);

	int getHeight(Node *node);
	int getBalance(Node *node);
	Node *rightRotate(Node *y);
	Node *leftRotate(Node *x);
	Node *balancedNode(Node *node);

	void printInorderHelper(Node *node);
	void printByLocationHelper(Node *node, const string &location, bool is_state, int &missing_pallet_count,
							   int &pallet_count);
};

void BST::deleteTree(Node *node) {
	if (node == nullptr) { return; }
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

Pallet BST::find(int pallet_number) {
	Node *node = findHelper(root, pallet_number);
	if (node == nullptr) {
		Pallet empty;
		return empty;
	} else {
		return node->pallet;
	}
}

Node *BST::insertHelper(Node *node, Pallet p) {
	if (node == nullptr) {
		node = new Node(p);
	} else if (p.pallet_number < node->pallet.pallet_number) {
		node->left = insertHelper(node->left, p);
	} else {
		node->right = insertHelper(node->right, p);
	}
	return balancedNode(node);
}

Node *BST::removeHelper(Node *node, int pallet_number) {
	if (node == nullptr) {
		return node;
	} else if (pallet_number < node->pallet.pallet_number) {
		node->left = removeHelper(node->left, pallet_number);
	} else if (pallet_number > node->pallet.pallet_number) {
		node->right = removeHelper(node->right, pallet_number);
	} else {
		if (node->left == nullptr) {
			Node *temp = node->right;
			delete node;
			return temp;
		} else if (node->right == nullptr) {
			Node *temp = node->left;
			delete node;
			return temp;
		} else {
			Node *temp = minNode(node->right);
			node->pallet = temp->pallet;
			node->right = removeHelper(node->right, temp->pallet.pallet_number);
		}
	}
	return balancedNode(node);
}

Node *BST::findHelper(Node *node, int pallet_number) {
	if (node == nullptr || node->pallet.pallet_number == pallet_number) {
		return node;
	} else if (pallet_number < node->pallet.pallet_number) {
		return findHelper(node->left, pallet_number);
	} else {
		return findHelper(node->right, pallet_number);
	}
}

Node *BST::minNode(Node *node) {
	Node *current = node;
	while (current->left != nullptr) { current = current->left; }
	return current;
}

void BST::printInorderHelper(Node *node) {
	if (node == nullptr) { return; }
	printInorderHelper(node->left);
	cout << "Pallet " << node->pallet.pallet_number << ": " << node->pallet.state << ", " << node->pallet.city
		 << ", " << node->pallet.weight << " pounds, QOH: " << node->pallet.qoh << "\n";
	printInorderHelper(node->right);
}

void BST::printByLocation(const string &location, bool is_state) {
	int missing_pallet_count = 0;
	int pallet_count = 0;
	printByLocationHelper(root, location, is_state, missing_pallet_count, pallet_count);
	if (pallet_count == 0) {
		cout << "No pallets found for " << location << endl;
	} else if (missing_pallet_count > 0) {
		cout << missing_pallet_count << " missing pallets in " << location << endl;
	}
}

void BST::printByLocationHelper(Node *node, const string &location, bool is_state, int &missing_pallet_count,
								int &pallet_count) {
	if (node == nullptr) { return; }
	printByLocationHelper(node->left, location, is_state, missing_pallet_count, pallet_count);
	if ((is_state && node->pallet.state == location) || (!is_state && node->pallet.city == location)) {
		cout << "Pallet " << node->pallet.pallet_number << ": " << node->pallet.state << ", " << node->pallet.city
			 << ", " << node->pallet.weight << " pounds, QOH: " << node->pallet.qoh << "\n";
		++pallet_count;
		if (node->pallet.qoh <= 0) {
			++missing_pallet_count;
			if (missing_pallet_count == 1) {
				cout << "Missing pallets found in " << location << ":" << endl;
			}
			cout << "Pallet " << node->pallet.pallet_number << endl;
		}
	}
	printByLocationHelper(node->right, location, is_state, missing_pallet_count, pallet_count);
}

int BST::getHeight(Node *node) {
	if (node == nullptr)
		return 0;
	return node->height;
}

int BST::getBalance(Node *node) {
	if (node == nullptr)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}

Node *BST::rightRotate(Node *y) {
	Node *x = y->left;
	Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	return x;
}

Node *BST::leftRotate(Node *x) {
	Node *y = x->right;
	Node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}

Node *BST::balancedNode(Node *node) {
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	int balance = getBalance(node);

	if (balance > 1 && getBalance(node->left) >= 0)
		return rightRotate(node);

	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && getBalance(node->right) <= 0)
		return leftRotate(node);

	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

#endif //INC_280DATASTRUCTURE_FINAL_BSTCONTROLLER_H
