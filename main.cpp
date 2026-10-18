#include <iostream>
#include <string>

#include "SystemSetup.h"
#include "managers/UserManager.h"
#include "managers/BikeManager.h"
#include "managers/DockManager.h"
#include "managers/ReservationManager.h"
#include "managers/RentalManager.h"
#include "managers/MaintenanceManager.h"

using namespace std;

void showMenu() {
    cout << "\n====================================\n";
    cout << "       NIT TRICHY E-BIKE SYSTEM\n";
    cout << "====================================\n";
    cout << "1. Register user\n";
    cout << "2. View docks\n";
    cout << "3. View bikes\n";
    cout << "4. Find nearest dock\n";
    cout << "5. View nearby docks\n";
    cout << "6. Rent a bike\n";
    cout << "7. Join reservation queue\n";
    cout << "8. Return a bike\n";
    cout << "9. View active rental\n";
    cout << "10. Report bike for maintenance\n";
    cout << "11. Complete maintenance\n";
    cout << "0. Exit\n";
}

int main() {
    UserManager userManager;
    BikeManager bikeManager;
    DockManager dockManager;
    ReservationManager reservationManager;
    RentalManager rentalManager;
    MaintenanceManager maintenanceManager;
    Graph campus;
    setupSystem(campus, dockManager, bikeManager);

    int choice = -1;
    while (choice != 0) {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int userID;
            string name;
            string email;
            cout << "User ID: ";
            cin >> userID;
            cout << "Name: ";
            cin >> name;
            cout << "Email: ";
            cin >> email;
            userManager.addUser(userID, name, email);
        } else if (choice == 2) {
            dockManager.displayAllDocks();
        } else if (choice == 3) {
            bikeManager.displayAllBikes();
        } else if (choice == 4) {
            int locationID;
            cout << "Current location ID: ";
            cin >> locationID;
            int nearestLocation = campus.findNearestDock(locationID);
            Dock* dock = dockManager.findDockByLocation(nearestLocation);
            if (dock == nullptr) {
                cout << "No reachable dock found.\n";
            } else {
                cout << "Nearest dock: " << dock->getName() << " (Dock " << dock->getDockID() << ")\n";
            }
        } else if (choice == 5) {
            int locationID;
            cout << "Current location ID: ";
            cin >> locationID;
            vector<NearbyDock> nearbyDocks = campus.getNearbyDocks(locationID);
            if (nearbyDocks.empty()) cout << "No reachable docks found.\n";
            for (const NearbyDock& item : nearbyDocks) {
                Dock* dock = dockManager.findDockByLocation(item.locationID);
                if (dock != nullptr) cout << dock->getName() << " - distance " << item.distance << '\n';
            }
        } else if (choice == 6) {
            int userID;
            int dockID;
            cout << "User ID: ";
            cin >> userID;
            cout << "Dock ID: ";
            cin >> dockID;
            rentalManager.rentBike(userID, dockID, userManager, bikeManager, dockManager);
        } else if (choice == 7) {
            int userID;
            int dockID;
            cout << "User ID: ";
            cin >> userID;
            cout << "Dock ID: ";
            cin >> dockID;
            reservationManager.addToQueue(userID, dockID, userManager, dockManager);
        } else if (choice == 8) {
            int userID;
            int dockID;
            cout << "User ID: ";
            cin >> userID;
            cout << "Return dock ID: ";
            cin >> dockID;
            rentalManager.returnBike(userID, dockID, userManager, bikeManager, dockManager, reservationManager);
        } else if (choice == 9) {
            int userID;
            cout << "User ID: ";
            cin >> userID;
            int bikeID = rentalManager.getActiveBike(userID);
            if (bikeID == -1) cout << "No active rental found.\n";
            else cout << "Active bike: " << bikeID << '\n';
        } else if (choice == 10) {
            int bikeID;
            cout << "Bike ID: ";
            cin >> bikeID;
            maintenanceManager.reportBike(bikeID, bikeManager, dockManager);
        } else if (choice == 11) {
            int bikeID;
            int dockID;
            cout << "Bike ID: ";
            cin >> bikeID;
            cout << "Dock ID: ";
            cin >> dockID;
            maintenanceManager.completeMaintenance(bikeID, dockID, bikeManager, dockManager);
        } else if (choice != 0) {
            cout << "Please choose a valid option.\n";
        }
    }

    cout << "Thank you for using the e-bike system.\n";
    return 0;
}
