#include "../../include/models/Dock.h"
#include <iostream>
#include <algorithm>

using namespace std;

Dock::Dock(int id, string name, int LocationID) {
    dockID = id;
    this->name = name;
    this->LocationID = LocationID;
}

int Dock::getDockID() const {
    return dockID;
}

string Dock::getName() const {
    return name;
}

int Dock::getGraphLocationID() const {
    return LocationID;
}

void Dock::addBike(int bikeID) {
    bikes.push_back(bikeID);
}

bool Dock::removeBike(int bikeID){
    auto it = find(bikes.begin(), bikes.end(), bikeID);
    if (it != bikes.end()) {
        bikes.erase(it);
        return true;
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
        for(int bikeID : bikes) {
            cout << bikeID << " ";
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