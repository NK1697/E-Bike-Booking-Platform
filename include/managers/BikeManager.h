#ifndef BIKE_MANAGER_H
#define BIKE_MANAGER_H

#include <unordered_map>
#include "../models/Bike.h"

using namespace std;

class BikeManager {
private:
    unordered_map<int, Bike> bikes;

public:
    void addBike(int bikeID);
    bool bikeExists(int bikeID) const;
    Bike* getBike(int bikeID);

    void displayAllBikes() const;
};

#endif