#include "../include/SystemSetup.h"

using namespace std;

void setupSystem(Graph& campus, DockManager& dockManager, BikeManager& bikeManager) {
    struct LocationSetup {
        int locationID;
        const char* name;
        int dockID;
        int capacity;
        int initialBikes;
    };

    // Each campus location is a dock. Capacity is 50% above the initial bike
    // count, rounded up, as specified for the campus network.
    const LocationSetup locations[] = {
        {1, "Aquamarine A", 101, 8, 5},
        {2, "Aquamarine B", 102, 8, 5},
        {3, "Mega Mess 1", 103, 8, 5},
        {4, "Mega Mess 2", 104, 8, 5},
        {5, "Garnet A", 105, 8, 5},
        {6, "Garnet B", 106, 8, 5},
        {7, "Hostel Office", 107, 15, 10},
        {8, "Logos Lecture Hall", 108, 23, 15},
        {9, "Orion", 109, 30, 20},
        {10, "MIG", 110, 8, 5},
        {11, "Main Gate", 111, 60, 40},
        {12, "NSO Ground", 112, 15, 10},
        {13, "Computer Lab", 113, 15, 10},
        {14, "2K Market", 114, 15, 10},
        {15, "Anjappar", 115, 8, 5},
        {16, "Library", 116, 38, 25},
        {17, "Computer Science Department", 117, 23, 15},
        {18, "Dominos", 118, 8, 5}
    };

    struct RoadSetup {
        int from;
        int to;
        int distance;
    };

    const RoadSetup roads[] = {
        {1, 2, 1}, {1, 3, 3}, {1, 15, 8},
        {2, 3, 3}, {2, 7, 10}, {2, 15, 8},
        {3, 4, 4}, {3, 7, 6},
        {4, 5, 6}, {4, 7, 7},
        {5, 6, 1}, {5, 7, 5}, {5, 8, 4},
        {6, 7, 5}, {6, 8, 4}, {6, 9, 6},
        {8, 9, 7}, {8, 12, 10}, {8, 13, 2},
        {9, 10, 1},
        {10, 11, 6},
        {11, 12, 4},
        {12, 14, 6}, {12, 16, 3}, {12, 18, 12},
        {13, 14, 7},
        {14, 15, 1}, {14, 17, 4},
        {16, 17, 4}
    };

    for (const LocationSetup& location : locations) {
        campus.addLocation(location.locationID, location.name);
        dockManager.addDock(location.dockID, location.name, location.locationID, location.capacity);
        campus.markAsDock(location.locationID);
    }

    for (const RoadSetup& road : roads) {
        campus.addRoad(road.from, road.to, road.distance);
    }

    int bikeID = 501;
    for (const LocationSetup& location : locations) {
        Dock* dock = dockManager.getDock(location.dockID);
        if (dock == nullptr) continue;

        for (int count = 0; count < location.initialBikes; count++) {
            bikeManager.addBike(bikeID);
            dock->addBike(bikeID);
            bikeID++;
        }
    }
}
