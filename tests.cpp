#include <iostream>
#include <climits>
#include <unordered_map>

#include "models/Graph.h"
#include "managers/RentalManager.h"
#include "managers/UserManager.h"
#include "managers/BikeManager.h"
#include "managers/DockManager.h"
#include "managers/ReservationManager.h"

using namespace std;

int main() {

    // ==========================================
    // CREATE MANAGERS
    // ==========================================

    Graph campus;
    UserManager userManager;
    BikeManager bikeManager;
    DockManager dockManager;
    RentalManager rentalManager;
    ReservationManager reservationManager;


    // ==========================================
    // TEST 1: REGISTER USERS
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 1: REGISTER USERS\n";
    cout << "========================================\n";

    userManager.addUser(101, "Nirav", "nirav@example.com");
    userManager.addUser(102, "Rahul", "rahul@example.com");
    userManager.addUser(103, "Aditi", "aditi@example.com");

    cout << "\nAll users:\n";
    userManager.displayAllUsers();


    // ==========================================
    // TEST 2: DUPLICATE USER
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 2: DUPLICATE USER\n";
    cout << "========================================\n";

    userManager.addUser(
        101,
        "Another Person",
        "another@example.com"
    );


    // ==========================================
    // TEST 3: ADD BIKES
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 3: ADD BIKES\n";
    cout << "========================================\n";

    bikeManager.addBike(501);
    bikeManager.addBike(502);
    bikeManager.addBike(503);

    cout << "\nAll bikes:\n";
    bikeManager.displayAllBikes();


    // ==========================================
    // TEST 4: DUPLICATE BIKE
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 4: DUPLICATE BIKE\n";
    cout << "========================================\n";

    bikeManager.addBike(501);


    // ==========================================
    // TEST 5: ADD DOCKS
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 5: ADD DOCKS\n";
    cout << "========================================\n";

    dockManager.addDock(101, "Library", 2);
    dockManager.addDock(102, "Hostel Zone", 3);

    cout << "\nAll docks:\n";
    dockManager.displayAllDocks();


    // ==========================================
    // TEST 6: DUPLICATE DOCK
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 6: DUPLICATE DOCK\n";
    cout << "========================================\n";

    dockManager.addDock(103, "Another Library", 1);


    // =========================================
    // TEST 7: ADD BIKES TO DOCK
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 7: ADD BIKES TO DOCK\n";
    cout << "========================================\n";

    Dock* library = dockManager.getDock(101);
    Dock* hostel = dockManager.getDock(102);

    if (library != nullptr) {
        library->addBike(501);
        library->addBike(502);
    }

    if (hostel != nullptr) {
        hostel->addBike(503);
    }

    cout << "\nLibrary:\n";
    library->displayDock();

    cout << "\nHostel Zone:\n";
    hostel->displayDock();


    // ==========================================
    // TEST 8: INVALID DOCK
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 8: INVALID DOCK\n";
    cout << "========================================\n";

    Dock* invalidDock = dockManager.getDock(999);

    if (invalidDock == nullptr) {
        cout << "Correctly handled invalid dock.\n";
    }


    // ==========================================
    // TEST 9: SUCCESSFUL BIKE REQUEST
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 9: SUCCESSFUL BIKE REQUEST\n";
    cout << "========================================\n";

    rentalManager.rentBike(
        101,
        1,
        userManager,
        bikeManager,
        dockManager
    );

    cout << "\nUser 101:\n";

    User* user101 = userManager.getUser(101);

    if (user101 != nullptr) {
        cout << "Current Bike: "
             << user101->getCurrentBike()
             << '\n';
    }

    cout << "\nLibrary after rental:\n";
    library->displayDock();


    // ==========================================
    // TEST 10: SECOND SUCCESSFUL REQUEST
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 10: SECOND SUCCESSFUL REQUEST\n";
    cout << "========================================\n";

    rentalManager.rentBike(
        102,
        1,
        userManager,
        bikeManager,
        dockManager
    );

    cout << "\nUser 102:\n";

    User* user102 = userManager.getUser(102);

    if (user102 != nullptr) {
        cout << "Current Bike: "
             << user102->getCurrentBike()
             << '\n';
    }

    cout << "\nLibrary after second rental:\n";
    library->displayDock();


    // ==========================================
    // TEST 11: DOCK HAS NO BIKES
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 11: NO BIKE AVAILABLE\n";
    cout << "========================================\n";

    rentalManager.rentBike(
        103,
        1,
        userManager,
        bikeManager,
        dockManager
    );

    cout << "\nQueue at Library:\n";
    reservationManager.displayQueue(1);


    // ==========================================
    // TEST 12: USER ALREADY HAS A BIKE
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 12: USER ALREADY HAS A BIKE\n";
    cout << "========================================\n";

    rentalManager.rentBike(
        101,
        2,
        userManager,
        bikeManager,
        dockManager
    );


    // ==========================================
    // TEST 13: NON-EXISTENT USER
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 13: NON-EXISTENT USER\n";
    cout << "========================================\n";

    rentalManager.rentBike(
        999,
        1,
        userManager,
        bikeManager,
        dockManager
    );


    // ==========================================
    // TEST 14: NON-EXISTENT DOCK
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 14: NON-EXISTENT DOCK\n";
    cout << "========================================\n";

    rentalManager.rentBike(
        103,
        999,
        userManager,
        bikeManager,
        dockManager
    );

    // ==========================================
    // TEST 15: RETURN BIKE WITH WAITING USER
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 15: RETURN BIKE WITH WAITING USER\n";
    cout << "========================================\n";

    rentalManager.returnBike(
        101,
        1,
        userManager,
        bikeManager,
        dockManager,
        reservationManager
    );

    cout << "\nUser 101:\n";
    user101 = userManager.getUser(101);

    if (user101 != nullptr) {
        cout << "Current Bike: "
            << user101->getCurrentBike()
            << '\n';
    }

    cout << "\nUser 103:\n";
    User* user103 = userManager.getUser(103);

    if (user103 != nullptr) {
        cout << "Current Bike: "
            << user103->getCurrentBike()
            << '\n';
    }

    cout << "\nLibrary:\n";
    library->displayDock();

    cout << "\nQueue:\n";
    reservationManager.displayQueue(1);

    // ==========================================
    // TEST 16: RETURN BIKE WITH EMPTY QUEUE
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 16: RETURN BIKE WITH EMPTY QUEUE\n";
    cout << "========================================\n";

    rentalManager.returnBike(
        102,
        1,
        userManager,
        bikeManager,
        dockManager,
        reservationManager
    );

    cout << "\nLibrary after return:\n";
    library->displayDock();

    // ==========================================
    // TEST 17: RETURN WITHOUT BIKE
    // ==========================================

    cout << "\n========================================\n";
    cout << "TEST 17: RETURN WITHOUT BIKE\n";
    cout << "========================================\n";

    rentalManager.returnBike(
        102,
        1,
        userManager,
        bikeManager,
        dockManager,
        reservationManager
    );

    cout << "\n========================================\n";
    cout << "CAMPUS GRAPH TEST\n";
    cout << "========================================\n";

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

    campus.displayGraph();

    cout << "\n===== DIJKSTRA TEST =====\n";

    unordered_map<int, int> distances =
        campus.dijkstra(1);

    cout << "Shortest distances from CSE:\n";

    for (const auto& entry : distances) {

        cout << "Location "
            << entry.first
            << " : ";

        if (entry.second == INT_MAX) {
            cout << "Unreachable";
        } else {
            cout << entry.second;
        }

        cout << '\n';
    }

    campus.markAsDock(2);
    campus.markAsDock(3);

    int userLocation = 1; // CSE

    int nearestLocation = campus.findNearestDock(userLocation);

    if (nearestLocation != -1) {
        Dock* nearestDock = dockManager.Docklocationmap(nearestLocation);

        if (nearestDock != nullptr) {
            cout << "\nNearest dock to "
                << "CSE"
                << " is Dock "
                << nearestDock->getDockID()
                << " (" << nearestDock->getName() << ").\n";
        } else {
            cout << "No dock exists at this location.\n";
        }
    } else {
        cout << "No reachable dock found.\n";
    }

    cout << "\n===== NEAREST DOCK TEST =====\n";

    int nearestDock = campus.findNearestDock(1);

    if (nearestDock != -1) {
        cout << "Nearest dock from CSE: "
            << nearestDock << '\n';
    } else {
        cout << "No dock reachable.\n";
    }

    // ==========================================
    // FINAL SYSTEM STATE
    // ==========================================

    cout << "\n========================================\n";
    cout << "FINAL SYSTEM STATE\n";
    cout << "========================================\n";

    cout << "\n--- USERS ---\n";
    userManager.displayAllUsers();

    cout << "\n--- BIKES ---\n";
    bikeManager.displayAllBikes();

    cout << "\n--- DOCKS ---\n";
    dockManager.displayAllDocks();

    cout << "\n--- RESERVATION QUEUES ---\n";
    reservationManager.displayQueue(1);
    reservationManager.displayQueue(2);

    cout << "\n===== GRAPH → DOCK TEST =====\n";

    Dock* near = dockManager.Docklocationmap(2);

    if (near != nullptr) {
        cout << "Graph location 2 corresponds to Dock:\n";
        near->displayDock();
    } 
    else {
        cout << "No dock found at this graph location.\n";
    }


    cout << "\n========================================\n";
    cout << "ALL CURRENT TESTS COMPLETED\n";
    cout << "========================================\n";

    return 0;
}