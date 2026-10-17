#ifndef DOCK_H
#define DOCK_H

#include <string>
#include <vector>

using namespace std;

class Dock {
private:
    int LocationID;
    int dockID;
    string name;
    vector<int> bikes;

public:
    int getGraphLocationID() const;
    Dock(int id, string name, int locationID);
    int getDockID() const;
    string getName() const;
    void addBike(int bikeID);
    bool removeBike(int bikeID);
    void displayDock() const;
    int getAvailableBike() const;
};

#endif