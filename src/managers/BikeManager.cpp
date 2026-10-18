#include "../../include/managers/BikeManager.h"
#include <iostream>

using namespace std;

void BikeManager::addBike(int bikeID) {
    if (bikeExists(bikeID)) {
        cout << "Bike " << bikeID << " already exists.\n";
        return;
    }
    bikes.insert(bikeID, Bike(bikeID));
    cout << "Bike " << bikeID << " added successfully.\n";
}

bool BikeManager::bikeExists(int bikeID) const {
    return bikes.contains(bikeID);
}

Bike* BikeManager::getBike(int bikeID) {
    return bikes.find(bikeID);
}

void BikeManager::displayAllBikes() const {
    if (bikes.empty()) {
        cout << "No bikes in the system.\n";
        return;
    }
    bikes.forEach([](int, const Bike& bike) {
        bike.displayBike();
        cout << '\n';
    });
}
