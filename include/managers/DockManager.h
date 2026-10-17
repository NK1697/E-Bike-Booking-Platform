#ifndef DOCK_MANAGER_H
#define DOCK_MANAGER_H

#include <unordered_map>
#include "../models/Dock.h"

using namespace std;

class DockManager {
private:
    unordered_map<int, Dock> docks;

public:
    void addDock(int dockID, string name, int LocationID);
    Dock *getDock(int dockID);
    void displayAllDocks() const;
    Dock* Docklocationmap(int LocationID);
};

#endif