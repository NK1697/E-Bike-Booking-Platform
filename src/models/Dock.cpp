#include "../../include/models/Dock.h"
#include <iostream>

using namespace std;

Dock::Dock(int id, string name, int locationID, int capacity) {
    dockID = id;
    this->name = name;
    this->locationID = locationID;
    this->capacity = capacity;
}

int Dock::getDockID() const {
    return dockID;
}

string Dock::getName() const {
    return name;
}

int Dock::getLocationID() const {
    return locationID;
}

int Dock::getCapacity() const {
    return capacity;
}

int Dock::getBikeCount() const {
    return static_cast<int>(bikes.size());
}

bool Dock::hasSpace() const {
    return getBikeCount() < capacity;
}

bool Dock::addBike(int bikeID) {
    for (int storedBikeID : bikes) {
        if (storedBikeID == bikeID) {
            return false;
        }
    }
    if (!hasSpace()) return false;
    bikes.push_back(bikeID);
    return true;
}

bool Dock::removeBike(int bikeID){
    for (int i = 0; i < static_cast<int>(bikes.size()); i++) {
        if (bikes[i] == bikeID) {
            bikes.erase(bikes.begin() + i);
            return true;
        }
    }
    return false;
}

bool Dock::hasBike(int bikeID) const {
    for (int storedBikeID : bikes) {
        if (storedBikeID == bikeID) return true;
    }
    return false;
}

void Dock::displayDock() const {
    cout << "Dock ID: " << dockID << '\n';
    cout << "Location: " << name << '\n';
    cout << "Capacity: " << getBikeCount() << "/" << capacity << '\n';
    cout << "Bikes: ";

    if(bikes.empty()) {
        cout << "No bikes available";
    } 
    else {
        for(int storedBikeID : bikes) {
            cout << storedBikeID << " ";
        }
    }
    cout << '\n';
}

int Dock::getAvailableBike() const{
    if(bikes.empty()){
        return -1;
    }
    return bikes[0];
}
