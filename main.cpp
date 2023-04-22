// main.cpp
#include <iostream>
#include "BSTController.h"
#include "invGenerator.h"

using namespace std;

void testBST() {
    const int NUM_PALLETS = 10;
    BST bst;

    InventoryGenerator generator("data.csv");
    for (int i = 1; i <= NUM_PALLETS; i++) {
        Pallet pallet = generator.generate_pallet(i);
        bst.insert(pallet);
    }

    std::cout << "All elements in the BST:\n";
    bst.printInorder();
}

void testHEAP() {

}

void testInvGen() {
    const int NUM_PALLETS = 10;

    InventoryGenerator generator("data.csv");

    for (int i = 1; i <= NUM_PALLETS; i++) {
        Pallet pallet = generator.generate_pallet(i);
        cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", " << pallet.weight << " pounds\n";
    }
}

int main() {
//    testInvGen();
    testBST();
//    testHEAP();

    return 0;
}