// BSTController.h
#ifndef BSTCONTROLLER_H
#define BSTCONTROLLER_H

#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct PalletInfo {
    int pallet_number;
    string state;
    string city;
    int weight; // in pounds
};

class BSTNode {
public:
    PalletInfo data;
    unique_ptr<BSTNode> left;
    unique_ptr<BSTNode> right;

    BSTNode(PalletInfo d) : data(d), left(nullptr), right(nullptr) {}
};

class PalletBST {
private:
    unique_ptr<BSTNode> root;

    void insert(unique_ptr<BSTNode> &current, const PalletInfo &data);


public:
    PalletBST() : root(nullptr) {}

    void insert(const PalletInfo &data);

};

void PalletBST::insert(unique_ptr<BSTNode> &current, const PalletInfo &data) {
    if (!current) {
        current = make_unique<BSTNode>(data);
        return;
    }

    if (data.pallet_number < current->data.pallet_number) {
        insert(current->left, data);
    } else {
        insert(current->right, data);
    }
}

inline void PalletBST::insert(const PalletInfo &data) {
    insert(root, data);
}

#endif // BSTCONTROLLER_H

