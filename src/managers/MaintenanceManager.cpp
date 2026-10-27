#include "../../include/managers/MaintenanceManager.h"
#include "../../include/managers/BikeManager.h"
#include "../../include/managers/DockManager.h"
#include "../../include/models/Bike.h"

#include <iostream>

using namespace std;

bool MaintenanceManager::reportBike(int bikeID, BikeManager& bikeManager, DockManager& dockManager) {
    Bike* bike = bikeManager.getBike(bikeID);
    if (bike == nullptr || !bike->isAvailable()) {
        cout << "Bike is not available for a maintenance report.\n";
        return false;
    }
    if (reportedBikes.contains(bikeID)) {
        cout << "Bike is already in maintenance.\n";
        return false;
    }
    if (!dockManager.removeBikeFromDocks(bikeID) || !bike->sendForMaintenance()) {
        cout << "Bike must be at a dock before maintenance can begin.\n";
        return false;
    }
    reportedBikes.insert(bikeID, true);
    waitingBikes.enqueue(bikeID);
    cout << "Bike " << bikeID << " sent for maintenance.\n";
    return true;
}

bool MaintenanceManager::completeMaintenance(int bikeID, int dockID, BikeManager& bikeManager, DockManager& dockManager) {
    Bike* bike = bikeManager.getBike(bikeID);
    Dock* dock = dockManager.getDock(dockID);
    if (!reportedBikes.contains(bikeID) || bike == nullptr || dock == nullptr) {
        cout << "Bike or dock data is not valid for maintenance completion.\n";
        return false;
    }
    if (!dock->hasSpace()) {
        cout << "Dock " << dockID << " is full. Choose another dock.\n";
        return false;
    }
    bike->completeMaintenance();
    dock->addBike(bikeID);
    reportedBikes.erase(bikeID);
    waitingBikes.remove(bikeID);
    cout << "Bike " << bikeID << " is ready at Dock " << dockID << ".\n";
    return true;
}

bool MaintenanceManager::isReported(int bikeID) const {
    return reportedBikes.contains(bikeID);
}

void MaintenanceManager::displayWaitingBikes() const {
    if (waitingBikes.empty()) {
        cout << "No bikes are waiting for maintenance.\n";
        return;
    }
    cout << "Maintenance reports: ";
    waitingBikes.forEach([](int bikeID) { cout << bikeID << " "; });
    cout << '\n';
}
