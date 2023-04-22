// main.cpp
#include <iostream>
#include "BSTController.h"
#include "invGenerator.h"

using namespace std;

void TestpalletBST() {
    PalletBST palletBST;

    PalletInfo pallet1 = {1, "CA", "Los Angeles", 150};
    PalletInfo pallet2 = {3, "NY", "New York", 180};
    PalletInfo pallet3 = {2, "TX", "Dallas", 200};
    PalletInfo pallet4 = {4, "FL", "Miami", 100};

    palletBST.insert(pallet1);
    palletBST.insert(pallet2);
    palletBST.insert(pallet3);
    palletBST.insert(pallet4);

    cout << "In-order traversal:" << endl;
    palletBST.printInOrder();

    cout << "\nSearching for pallet number 2: " << (palletBST.search(2) ? "Found" : "Not found") << endl;
    cout << "Searching for pallet number 5: " << (palletBST.search(5) ? "Found" : "Not found") << endl;

    cout << "\nDeleting pallet number 2" << endl;
    palletBST.remove(2);

    cout << "\nIn-order traversal after deletion:" << endl;
    palletBST.printInOrder();
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
    testInvGen();

    return 0;
}