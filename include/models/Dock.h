#ifndef DOCK_H
#define DOCK_H

#include <string>
#include <vector>

using namespace std;

class Dock {
private:
    int locationID;
    int dockID;
    string name;
    vector<int> bikes;

public:
    Dock(int id, string name, int locationID);
    int getDockID() const;
    string getName() const;
    int getLocationID() const;
    void addBike(int bikeID);
    bool removeBike(int bikeID);
    bool hasBike(int bikeID) const;
    void displayDock() const;
    int getAvailableBike() const;
};

#endif
