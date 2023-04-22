#ifndef INVENTORY_GENERATOR_H
#define INVENTORY_GENERATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;

// Define a struct to represent a pallet
struct Pallet {
    int pallet_number;
    string state;
    string city;
    int weight;  // in pounds
};

class InventoryGenerator {
public:
    InventoryGenerator(const string& filename);
    Pallet generate_pallet(int pallet_number);

private:
    vector<string> cities;
    vector<string> states;
    string state_name; // added for reading state name from CSV

    int generate_weight() {
        // Generate a random weight between 1 and 1000 pounds
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> weight_dist(25, 200);
        return weight_dist(gen);
    }
};


InventoryGenerator::InventoryGenerator(const std::string &filename) {
    // Read the CSV file containing cities and states
    ifstream infile(filename);
    string line;
    getline(infile, line); // Skip the header line
    while (getline(infile, line)) {
        string city, state;
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, state_name, ',');
        cities.push_back(city);
        states.push_back(state_name);
    }
}

Pallet InventoryGenerator::generate_pallet(int pallet_number) {
    // Check that cities and states vectors are non-empty and have the same size
    if (cities.empty() || cities.size() != states.size()) {
        throw runtime_error("Invalid state and city data");
    }

    // Generate a random index for the city and state vectors
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> index_dist(0, cities.size()-1);
    int index = index_dist(gen);

    // Create the pallet and return it
    Pallet pallet = { pallet_number, states[index], cities[index], generate_weight() };
    return pallet;
}

#endif // INVENTORY_GENERATOR_H
