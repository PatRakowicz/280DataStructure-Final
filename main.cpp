#include <iostream>
#include "invGenerator.h"
#include "heap.h"
#include "FuncTesting.h"
#include "BSTControl.h"

using namespace std;

void testBST() {
	const int NUM_PALLETS = 10;
	BST bst;

	InventoryGenerator generator("data.csv");
	for (int i = 1; i <= NUM_PALLETS; i++) {
		Pallet pallet = generator.generate_pallet(i);
		bst.insert(pallet);
	}

	cout << "All elements in the BST\n";
	cout << "Pallet # | State Name | City Name | Weight | QOH \n";
	bst.printInorder();

	// Search for pallets by state
	cout << "\n All pallets in Texas:\n";
	bst.printByLocation("Texas", true);

	// Search for pallets by city
	cout << "\n All pallets in Smithfield:\n";
	bst.printByLocation("Smithfield", false);

	cout << "\n Remove Pallet #:6 \n";
	bst.remove(6);
	bst.printInorder();
/*
	// Time Testing
	// Measure insertion time for a single pallet into BST
	Pallet new_pallet = generator.generate_pallet(1001);
	auto insertion_time = measureBSTInsertionTime(bst, new_pallet);
	std::cout << "BST insertion time for a single pallet: " << insertion_time.count() << " microseconds" << std::endl;

	// Measure deletion time for a single pallet from BST
	int pallet_number_to_remove = 852;
	auto deletion_time = measureBSTDeletionTime(bst, pallet_number_to_remove);
	std::cout << "BST deletion time for a single pallet: " << deletion_time.count() << " microseconds" << std::endl;

	// Measure search time for a single pallet in BST
	int pallet_number_to_find = 765;
	auto search_time = measureBSTSearchTime(bst, pallet_number_to_find);
	std::cout << "BST search time for a single pallet: " << search_time.count() << " microseconds" << std::endl;
*/
}

void testHEAP() {
  const int NUM_PALLETS = 16;

    InventoryGenerator generator("data.csv");
    Heap myHeap;
    for (int i = 1; i <= NUM_PALLETS; i++) {
        Pallet * p = new Pallet;
        Pallet pallet = generator.generate_pallet(i);
        p->pallet_number = pallet.pallet_number;
        p->state = pallet.state;
        p->city = pallet.city;
        p->weight = pallet.weight;
        p->qoh = pallet.qoh;
        cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", " << pallet.weight << " pounds, " << pallet.qoh << " on hand" << endl;

        myHeap.addPallet(p);
        // myHeap.printItems();
    }
    myHeap.printItems();

    while (myHeap.getRootQty() < 5) {
        myHeap.restock(50);
    }
    cout << "\n\n";
    myHeap.printItems();

    myHeap.remove(7);
    cout << "\n\n";
    myHeap.printItems();

    cout << myHeap.search(11)->qoh << endl;
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
    // testHEAP();

    return 0;
}

