#include "../../include/models/Bike.h"
#include <iostream>
using namespace std;

Bike::Bike(int id) {
    bikeID = id;
    available = true;
    needsMaintenance = false;
}

int Bike::getBikeID() const {
    return bikeID;
}

void Bike::rentBike() {
    if (available && !needsMaintenance){
        available = false;
        cout << "Bike " << bikeID << " has been rented.\n";
    }
    else
        cout << "Bike " << bikeID << " is already rented.\n";
}

void Bike::returnBike() {
    if (needsMaintenance) return;
    available = true;
    cout << "Bike " << bikeID << " has been returned.\n";
}

bool Bike::sendForMaintenance() {
    if (!available || needsMaintenance) return false;
    available = false;
    needsMaintenance = true;
    return true;
}

void Bike::completeMaintenance() {
    needsMaintenance = false;
    available = true;
}

bool Bike::isAvailable() const {
    return available && !needsMaintenance;
}

bool Bike::isUnderMaintenance() const {
    return needsMaintenance;
}

void Bike::displayBike() const {
    cout << "Bike ID: " << bikeID << '\n';

    if (needsMaintenance)
        cout << "Status: Under maintenance\n";
    else if (available)
        cout << "Status: Available\n";
    else
        cout << "Status: Rented\n";
}
