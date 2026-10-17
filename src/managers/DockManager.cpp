#include "../../include/managers/DockManager.h"
#include <iostream>

using namespace std;

void DockManager::addDock(int dockID, string name, int LocationID) {
    if (docks.find(dockID) != docks.end()) {
        cout << "Dock " << dockID << " already exists.\n";
        return;
    }
    docks.emplace(dockID, Dock(dockID, name, LocationID));
    cout << "Dock " << dockID << " added successfully.\n";
}

Dock* DockManager::getDock(int dockID) {
    auto it = docks.find(dockID);
    if (it == docks.end()) {
        return nullptr;
    }
    return &(it->second);
}

void DockManager::displayAllDocks() const {
    if (docks.empty()) {
        cout << "No docks in the system.\n";
        return;
    }
    for (const auto& pair : docks) {
        pair.second.displayDock();
        cout << '\n';
    }
}

Dock* DockManager::Docklocationmap(int LocationID){
    for(auto& entry : docks){
        Dock& dock = entry.second;
        if(dock.getGraphLocationID() == LocationID){
            return &dock;
        }
    }
    return nullptr;
}