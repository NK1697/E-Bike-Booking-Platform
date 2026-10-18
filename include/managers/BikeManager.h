#ifndef BIKE_MANAGER_H
#define BIKE_MANAGER_H

#include "../ds/HashTable.h"
#include "../models/Bike.h"

using namespace std;

class BikeManager {
private:
    HashTable<Bike> bikes;

public:
    void addBike(int bikeID);
    bool bikeExists(int bikeID) const;
    Bike* getBike(int bikeID);

    void displayAllBikes() const;
};

#endif
