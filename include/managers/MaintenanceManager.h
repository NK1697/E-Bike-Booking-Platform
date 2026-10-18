#ifndef MAINTENANCE_MANAGER_H
#define MAINTENANCE_MANAGER_H

#include "../ds/HashTable.h"
#include "../ds/CustomQueue.h"

class BikeManager;
class DockManager;

class MaintenanceManager {
private:
    HashTable<bool> reportedBikes;
    CustomQueue<int> waitingBikes;

public:
    bool reportBike(int bikeID, BikeManager& bikeManager, DockManager& dockManager);
    bool completeMaintenance(int bikeID, int dockID, BikeManager& bikeManager, DockManager& dockManager);
    bool isReported(int bikeID) const;
    void displayWaitingBikes() const;
};

#endif
