#include "../../include/models/Bike.h"
#include <iostream>
using namespace std;

Bike::Bike(int id) {
    bikeID = id;
    available = true;
}

int Bike::getBikeID() const {
    return bikeID;
}

void Bike::rentBike() {
    if (available){
        available = false;
        cout << "Bike " << bikeID << " has been rented.\n";
    }
    else
        cout << "Bike " << bikeID << " is already rented.\n";
}

void Bike::returnBike() {
    available = true;
    cout << "Bike " << bikeID << " has been returned.\n";
}

bool Bike::isAvailable() const {
    return available;
}

void Bike::displayBike() const {
    cout << "Bike ID: " << bikeID << '\n';

    if (available)
        cout << "Status: Available\n";
    else
        cout << "Status: Rented\n";
}