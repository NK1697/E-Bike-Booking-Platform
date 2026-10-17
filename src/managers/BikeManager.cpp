#include "../../include/managers/BikeManager.h"
#include <iostream>

using namespace std;

void BikeManager::addBike(int bikeID) {
    if (bikeExists(bikeID)) {
        cout << "Bike " << bikeID << " already exists.\n";
        return;
    }
    bikes.emplace(bikeID, Bike(bikeID));
    cout << "Bike " << bikeID << " added successfully.\n";
}

bool BikeManager::bikeExists(int bikeID) const {
    return bikes.find(bikeID) != bikes.end();
}

Bike* BikeManager::getBike(int bikeID) {
    auto it = bikes.find(bikeID);
    if (it == bikes.end()) {
        return nullptr;
    }
    return &(it->second);
}

void BikeManager::displayAllBikes() const {
    if (bikes.empty()) {
        cout << "No bikes in the system.\n";
        return;
    }
    for (const auto& pair : bikes) {
        pair.second.displayBike();
        cout << '\n';
    }
}