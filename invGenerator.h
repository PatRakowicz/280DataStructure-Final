#ifndef INVENTORY_GENERATOR_H
#define INVENTORY_GENERATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>


// Define a struct to represent a pallet
struct Pallet {
    int pallet_number;
    std::string state;
    std::string city;
    int weight;  // in pounds
    int qoh;
};

class InventoryGenerator {
public:
    InventoryGenerator(const std::string &filename) {
        // Read the CSV file containing cities and states
        std::ifstream infile(filename);
        std::string line;
        std::string tmp;
        getline(infile, line); // Skip the header line
        while (getline(infile, line)) {
            std::string city, state;
            std::istringstream iss(line);
            getline(iss, city, ',');
            getline(iss, tmp, ',');
            getline(iss, tmp, ',');
            getline(iss, state_name, ',');
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
        // unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        unsigned seed = pallet_number;
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> index_dist(0, cities.size() - 1);
        int index = index_dist(gen);

        // Create the pallet and return it
        Pallet pallet = {pallet_number, states[index], cities[index], generate_weight(seed), generate_qoh(seed)};
        return pallet;
    }

private:
    std::vector<string> cities;
    std::vector<string> states;
    std::string state_name; // added for reading state name from CSV

    int generate_weight(int seed) {
        // Generate a random weight between 1 and 1000 pounds
        // unsigned seed = chrono::system_clock::now().time_since_epoch().count();

        std::mt19937 gen(seed);
        std::uniform_int_distribution<> weight_dist(25, 200);
        return weight_dist(gen);
    }

    int generate_qoh(int seed) {
        // Generate a random weight between 1 and 1000 pounds
        // unsigned seed = chrono::system_clock::now().time_since_epoch().count();

        std::mt19937 gen(seed);
        std::uniform_int_distribution<> qoh_dist(1, 200);
        return qoh_dist(gen);
    }
};

#endif // INVENTORY_GENERATOR_H