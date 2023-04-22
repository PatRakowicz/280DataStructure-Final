// BSTController.h
#ifndef BSTCONTROLLER_H
#define BSTCONTROLLER_H

#include <iostream>
#include <string>
#include <memory>

struct PalletInfo {
    int pallet_number;
    std::string state;
    std::string city;
    int weight; // in pounds
};

class BSTNode {
public:
    PalletInfo data;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;

    BSTNode(PalletInfo d) : data(d), left(nullptr), right(nullptr) {}
};

class PalletBST {
private:
    std::unique_ptr<BSTNode> root;

    void insert(std::unique_ptr<BSTNode> &current, const PalletInfo &data);

    std::unique_ptr<BSTNode> &search(std::unique_ptr<BSTNode> &current, int pallet_number);

    std::unique_ptr<BSTNode> &findMin(std::unique_ptr<BSTNode> &current);

    void remove(std::unique_ptr<BSTNode> &current, int pallet_number);

    void inOrderTraversal(std::unique_ptr<BSTNode> &current);

public:
    PalletBST() : root(nullptr) {}

    void insert(const PalletInfo &data);

    bool remove(int pallet_number);

    bool search(int pallet_number);

    void printInOrder();
};

void PalletBST::insert(std::unique_ptr<BSTNode> &current, const PalletInfo &data) {
    if (!current) {
        current = std::make_unique<BSTNode>(data);
        return;
    }

    if (data.pallet_number < current->data.pallet_number) {
        insert(current->left, data);
    } else {
        insert(current->right, data);
    }
}

std::unique_ptr<BSTNode> &PalletBST::search(std::unique_ptr<BSTNode> &current, int pallet_number) {
    if (!current || current->data.pallet_number == pallet_number) {
        return current;
    }

    if (pallet_number < current->data.pallet_number) {
        return search(current->left, pallet_number);
    } else {
        return search(current->right, pallet_number);
    }
}

std::unique_ptr<BSTNode> &PalletBST::findMin(std::unique_ptr<BSTNode> &current) {
    if (!current->left) {
        return current;
    }
    return findMin(current->left);
}

void PalletBST::remove(std::unique_ptr<BSTNode> &current, int pallet_number) {
    if (!current) {
        return;
    }

    if (pallet_number < current->data.pallet_number) {
        remove(current->left, pallet_number);
    } else if (pallet_number > current->data.pallet_number) {
        remove(current->right, pallet_number);
    } else {
        if (!current->left && !current->right) {
            current.reset();
        } else if (current->left && !current->right) {
            current = std::move(current->left);
        } else if (!current->left && current->right) {
            current = std::move(current->right);
        } else {
            auto &minNode = findMin(current->right);
            current->data = minNode->data;
            remove(current->right, minNode->data.pallet_number);
        }
    }
}

void PalletBST::inOrderTraversal(std::unique_ptr<BSTNode> &current) {
    if (!current) {
        return;
    }

    inOrderTraversal(current->left);
    std::cout << "Pallet Number: " << current->data.pallet_number
              << " State: " << current->data.state
              << " City: " << current->data.city
              << " Weight: " << current->data.weight << " lbs" << std::endl;
    inOrderTraversal(current->right);
}

inline void PalletBST::insert(const PalletInfo &data) {
    insert(root, data);
}

inline bool PalletBST::remove(int pallet_number) {
    std::unique_ptr<BSTNode> &nodeToDelete = search(root, pallet_number);
    if (!nodeToDelete) {
        return false;
    }
    remove(root, pallet_number);
    return true;
}

inline bool PalletBST::search(int pallet_number) {
    return static_cast<bool>(search(root, pallet_number));
}

inline void PalletBST::printInOrder() {
    inOrderTraversal(root);
}

#endif //BSTCONTROLLER_H