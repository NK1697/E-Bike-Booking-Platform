#include "../../include/models/Dock.h"
#include <iostream>

using namespace std;

Dock::Dock(int id, string name, int locationID) {
    dockID = id;
    this->name = name;
    this->locationID = locationID;
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

void Dock::addBike(int bikeID) {
    for (int storedBikeID : bikes) {
        if (storedBikeID == bikeID) {
            return;
        }
    }
    bikes.push_back(bikeID);
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
