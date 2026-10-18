#include "../include/SystemSetup.h"

using namespace std;

void setupSystem(Graph& campus,DockManager& dockManager,BikeManager& bikeManager) {
    campus.addLocation(1, "CSE");
    campus.addLocation(2, "Library");
    campus.addLocation(3, "Hostel");
    campus.addLocation(4, "Main Gate");
    campus.addLocation(5, "Sports Complex");

    campus.addRoad(1, 2, 3);
    campus.addRoad(1, 4, 5);
    campus.addRoad(2, 3, 4);
    campus.addRoad(3, 4, 2);
    campus.addRoad(2, 5, 6);

    dockManager.addDock(101, "Library", 2);
    dockManager.addDock(102, "Hostel Zone", 3);

    campus.markAsDock(2);
    campus.markAsDock(3);

    bikeManager.addBike(501);
    bikeManager.addBike(502);
    bikeManager.addBike(503);

    Dock* library = dockManager.getDock(101);
    Dock* hostel = dockManager.getDock(102);
    if (library != nullptr) {
        library->addBike(501);
        library->addBike(502);
    }
    if (hostel != nullptr) hostel->addBike(503);
}
