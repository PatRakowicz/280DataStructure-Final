//
// Created by Patrick on 22/04/2023.
//

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

	Node(Pallet p) : pallet(p), left(nullptr), right(nullptr) {}
};

class BST {
public:
	BST() : root(nullptr) {}

	void insert(Pallet p) { root = insertHelper(root, p); }
	void remove(Pallet p) { root = removeHelper(root, p); }

	Pallet find(int pallet_number);

	void printInorder() { printInorderHelper(root); }
	void printByLocation(const string &location, bool is_state) {
		printByLocationHelper(root, location, is_state);
	};

private:
	Node *root;

	Node *insertHelper(Node *node, Pallet p);
	Node *removeHelper(Node *node, Pallet p);
	Node *findHelper(Node *node, int pallet_number);
	Node *minNode(Node *node);

	void printInorderHelper(Node *node);
	void printByLocationHelper(Node *node, const string &location, bool is_state);
};

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
	return node;
}

Node *BST::removeHelper(Node *node, Pallet p) {
	if (node == nullptr) {
		return node;
	} else if (p.pallet_number < node->pallet.pallet_number) {
		node->left = removeHelper(node->left, p);
	} else if (p.pallet_number > node->pallet.pallet_number) {
		node->right = removeHelper(node->right, p);
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
			node->right = removeHelper(node->right, temp->pallet);
		}
	}
	return node;
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
	while (current->left != nullptr) {
		current = current->left;
	}
	return current;
}

void BST::printInorderHelper(Node *node) {
	if (node == nullptr) {
		return;
	}
	printInorderHelper(node->left);
	cout << "Pallet " << node->pallet.pallet_number << ": " << node->pallet.state << ", " << node->pallet.city
		 << ", " << node->pallet.weight << " pounds, QOH: " << node->pallet.qoh << "\n";
	printInorderHelper(node->right);
}

void BST::printByLocationHelper(Node *node, const string &location, bool is_state) {
	if (node == nullptr) {
		return;
	}
	printByLocationHelper(node->left, location, is_state);
	if ((is_state && node->pallet.state == location) || (!is_state && node->pallet.city == location)) {
		cout << "Pallet " << node->pallet.pallet_number << ": " << node->pallet.state << ", " << node->pallet.city
			 << ", " << node->pallet.weight << " pounds, QOH: " << node->pallet.qoh << "\n";
	}
	printByLocationHelper(node->right, location, is_state);
}


#endif //INC_280DATASTRUCTURE_FINAL_BSTCONTROLLER_H
