//
// Created by Livid on 25/04/2023.
//

#ifndef INC_280DATASTRUCTURE_FINAL_FUNCTESTING_H
#define INC_280DATASTRUCTURE_FINAL_FUNCTESTING_H

#include <chrono>
#include "invGenerator.h"
#include "BSTController.h"
#include "heap.h"

// Measure the execution time for inserting a single pallet into a BST
template<typename T>
std::chrono::microseconds measureBSTInsertionTime(T& bst, const Pallet& pallet) {
	auto start_time = std::chrono::high_resolution_clock::now();
	bst.insert(pallet);
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
}

// Measure the execution time for removing a single pallet from a BST
template<typename T>
std::chrono::microseconds measureBSTDeletionTime(T& bst, int pallet_number) {
	auto start_time = std::chrono::high_resolution_clock::now();
	bst.remove(pallet_number);
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
}

// Measure the execution time for finding a single pallet in a BST
template<typename T>
std::chrono::microseconds measureBSTSearchTime(T& bst, int pallet_number) {
	auto start_time = std::chrono::high_resolution_clock::now();
	bst.find(pallet_number);
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
}

// Measure the execution time for inserting a single pallet into a heap
std::chrono::microseconds measureHeapInsertionTime(Heap& heap, const Pallet& pallet) {
	auto start_time = std::chrono::high_resolution_clock::now();
	heap.addItem(pallet.city, pallet.state, pallet.qoh);
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
}

// Measure the execution time for removing a single pallet from a heap
std::chrono::microseconds measureHeapDeletionTime(Heap& heap, int pallet_number) {
	auto start_time = std::chrono::high_resolution_clock::now();
	heap.restock(1);
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
}

// Measure the execution time for finding a single pallet in a heap
std::chrono::microseconds measureHeapSearchTime(Heap& heap, int pallet_number) {
	auto start_time = std::chrono::high_resolution_clock::now();
	heap.checkQOH();
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
}


#endif //INC_280DATASTRUCTURE_FINAL_FUNCTESTING_H
