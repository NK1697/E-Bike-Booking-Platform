#include "../../include/managers/DockManager.h"
#include <iostream>

using namespace std;

void DockManager::addDock(int dockID, string name, int locationID, int capacity) {
    if (docks.contains(dockID)) {
        cout << "Dock " << dockID << " already exists.\n";
        return;
    }
    if (capacity <= 0) {
        cout << "Dock capacity must be positive.\n";
        return;
    }
    docks.insert(dockID, Dock(dockID, name, locationID, capacity));
    cout << "Dock " << dockID << " added successfully.\n";
}

Dock* DockManager::getDock(int dockID) {
    return docks.find(dockID);
}

void DockManager::displayAllDocks() const {
    if (docks.empty()) {
        cout << "No docks in the system.\n";
        return;
    }
    docks.forEach([](int, const Dock& dock) {
        dock.displayDock();
        cout << '\n';
    });
}

Dock* DockManager::findDockByLocation(int locationID) {
    Dock* foundDock = nullptr;
    docks.forEach([&](int, Dock& dock) {
        if (dock.getLocationID() == locationID) foundDock = &dock;
    });
    return foundDock;
}

bool DockManager::removeBikeFromDocks(int bikeID) {
    Dock* foundDock = nullptr;
    docks.forEach([&](int, Dock& dock) {
        if (dock.hasBike(bikeID)) foundDock = &dock;
    });
    return foundDock != nullptr && foundDock->removeBike(bikeID);
}
