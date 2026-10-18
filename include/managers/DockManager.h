#ifndef DOCK_MANAGER_H
#define DOCK_MANAGER_H

#include "../ds/HashTable.h"
#include "../models/Dock.h"

using namespace std;

class DockManager {
private:
    HashTable<Dock> docks;

public:
    void addDock(int dockID, string name, int locationID);
    Dock *getDock(int dockID);
    void displayAllDocks() const;
    Dock* findDockByLocation(int locationID);
    bool removeBikeFromDocks(int bikeID);
};

#endif
