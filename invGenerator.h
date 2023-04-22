#ifndef INVENTORY_GENERATOR_H
#define INVENTORY_GENERATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>

// Define a struct to represent a pallet
struct Pallet {
    int pallet_number;
    std::string state;
    std::string city;
    int weight;  // in pounds
};

class InventoryGenerator {
public:
    InventoryGenerator(const std::string& filename) {
        // Read the CSV file containing cities and states
        std::ifstream infile(filename);
        std::string line;
        std::getline(infile, line); // Skip the header line
        while (std::getline(infile, line)) {
            std::string city, state;
            std::istringstream iss(line);
            std::getline(iss, city, ',');
            std::getline(iss, state_name, ',');
            cities.push_back(city);
            states.push_back(state_name);
        }
    }

    Pallet generate_pallet(int pallet_number) {
        // Check that cities and states vectors are non-empty and have the same size
        if (cities.empty() || cities.size() != states.size()) {
            throw std::runtime_error("Invalid state and city data");
        }

        // Generate a random index for the city and state vectors
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> index_dist(0, cities.size()-1);
        int index = index_dist(gen);

        // Create the pallet and return it
        Pallet pallet = { pallet_number, states[index], cities[index], generate_weight() };
        return pallet;
    }

private:
    std::vector<std::string> cities;
    std::vector<std::string> states;
    std::string state_name; // added for reading state name from CSV

    int generate_weight() {
        // Generate a random weight between 1 and 1000 pounds
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> weight_dist(25, 200);
        return weight_dist(gen);
    }
};
#endif // INVENTORY_GENERATOR_H
