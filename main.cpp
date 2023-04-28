#include <iostream>
#include "invGenerator.h"
#include "heap.h"
#include "priority.h"
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
  const int NUM_PALLETS = 3;

    InventoryGenerator generator("data.csv");
    Heap myHeap;
    for (int i = 1; i <= NUM_PALLETS; i++) {
        Pallet pallet = generator.generate_pallet(i);
        cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", " << pallet.weight << " pounds, " << pallet.qoh << " on hand" << endl;

        myHeap.addPallet(&pallet);
        // myHeap.printItems();
    }
    myHeap.printItems();

    // while (myHeap.getRootQty() < 5) {
    //     myHeap.restock(50);
    // }
    // cout << "\n\n";
    // myHeap.printItems();
}

void testPrio() {
    const int NUM_PALLETS = 10;

    InventoryGenerator generator("data.csv");
    Priority prio;
    
    for (int i = 1; i <= NUM_PALLETS; i++) {
        Pallet pallet = generator.generate_pallet(i);
        prio.addPallet(pallet);
        cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", " << pallet.weight << " pounds\n" << pallet.qoh << " on hand" << endl;
    }
    
    prio.print();
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
    // testPrio();

    return 0;
}

