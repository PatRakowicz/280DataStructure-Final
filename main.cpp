// main.cpp
#include <iostream>
#include "BSTController.h"
#include "invGenerator.h"
#include "heap.h"
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
	cout << "All pallets in Texas:\n";
	bst.printByLocation("Texas", true);

//	 Search for pallets by city
	cout << "All pallets in Houston:\n";
	bst.printByLocation("Smithfield", false);

	cout << "Remove Pallet \n";
	bst.remove(6);
	bst.printInorder();
}

void testHEAP() {
	const int NUM_PALLETS = 10;

	InventoryGenerator generator("data.csv");
	Heap myHeap;
	for (int i = 1; i <= NUM_PALLETS; i++) {
		Pallet pallet = generator.generate_pallet(i);
		myHeap.addItem(pallet.city, pallet.state, pallet.qoh);
		cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", " << pallet.weight << " pounds, " << pallet.qoh << " on hand" << endl;
	}
	myHeap.printItems();

	// while (myHeap.getRootQty() < 5) {
	//     myHeap.restock(50);
	// }
}

void testInvGen() {
	const int NUM_PALLETS = 10;

	InventoryGenerator generator("data.csv");

	for (int i = 1; i <= NUM_PALLETS; i++) {
		Pallet pallet = generator.generate_pallet(i);
		cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", "
			 << pallet.weight << " pounds\n";
	}
}

int main() {
//    testInvGen();
//    testBST();
//    testHEAP();

	return 0;
}