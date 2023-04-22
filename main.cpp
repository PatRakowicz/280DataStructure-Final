#include <iostream>
#include "invGenerator.h"
#include "heap.h"
using namespace std;
// void testBST() {
//     const int NUM_PALLETS = 10;
//     BST bst;

//     InventoryGenerator generator("data.csv");
//     for (int i = 1; i <= NUM_PALLETS; i++) {
//         Pallet pallet = generator.generate_pallet(i);
//         bst.insert(pallet);
//     }

//     std::cout << "All elements in the BST:\n";
//     bst.printInorder();
// }

void testHEAP() {
  const int NUM_PALLETS = 2;

    InventoryGenerator generator("data.csv");
    Heap myHeap;
    for (int i = 1; i <= NUM_PALLETS; i++) {
        Pallet pallet = generator.generate_pallet(i);
        myHeap.addItem(pallet.city, pallet.state, pallet.qoh);
        cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", " << pallet.weight << " pounds, " << pallet.qoh << " on hand" << endl;
    }
    myHeap.printItems();
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
    // testInvGen();
    // testBST();
    testHEAP();

    return 0;
}

