#include <iostream>
#include "invGenerator.h"
#include "heap.h"
#include "BSTController.h"

using namespace std;

// use for testing different functions
// auto startTime = std::chrono::high_resolution_clock::now();
// 	auto endTime = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
//	std::cout << "~~~ Execution time for HEAP Insert: " << duration.count() << " milliseconds" << std::endl;

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

	// Check QOH and restock pallets with QOH less than 5
	vector<Pallet> lowQOH = bst.checkQOH();
	for (const auto& pallet : lowQOH) {
		if (pallet.qoh < 5) {
			bst.restockQOH(pallet.pallet_number, 10);  // Restock with a QOH of 10
		}
	}

	// Print updated pallet information
	bst.printInorder();
}

void testHEAP() {
	const int NUM_PALLETS = 10;

	InventoryGenerator generator("data.csv");
	Heap myHeap;
	for (int i = 1; i <= NUM_PALLETS; i++) {
		Pallet *p = new Pallet;
		Pallet pallet = generator.generate_pallet(i);
		p->pallet_number = pallet.pallet_number;
		p->state = pallet.state;
		p->city = pallet.city;
		p->weight = pallet.weight;
		p->qoh = pallet.qoh;
		cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", "
			 << pallet.weight << " pounds, " << pallet.qoh << " on hand" << endl;

		myHeap.addPallet(p);
//		 myHeap.printItems();
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
		cout << "Pallet " << pallet.pallet_number << ": " << pallet.state << ", " << pallet.city << ", "
			 << pallet.weight << " pounds\n";
	}
}

int main() {
	// testInvGen();
	testBST();
	testHEAP();

	return 0;
}

