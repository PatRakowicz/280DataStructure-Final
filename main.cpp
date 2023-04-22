// main.cpp
#include <iostream>
#include "BSTController.h"
#include "invGenerator.h"

int main() {
    PalletBST palletBST;

    PalletInfo pallet1 = {1, "CA", "Los Angeles", 150};
    PalletInfo pallet2 = {3, "NY", "New York", 180};
    PalletInfo pallet3 = {2, "TX", "Dallas", 200};

    palletBST.insert(pallet1);
    palletBST.insert(pallet2);
    palletBST.insert(pallet3);

    return 0;
}

