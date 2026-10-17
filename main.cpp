#include <iostream>

#include "SystemSetup.h"
#include "managers/UserManager.h"
#include "managers/BikeManager.h"
#include "managers/DockManager.h"
#include "managers/ReservationManager.h"
#include "managers/RentalManager.h"

using namespace std;

int main() {
    UserManager userManager;
    BikeManager bikeManager;
    DockManager dockManager;
    ReservationManager reservationManager;
    Graph campus;
    RentalManager rentalManager;

    setupSystem(campus, dockManager, bikeManager);

    int choice;

    while (true) {
        cout << "\n====================================\n";
        cout << "       NIT TRICHY E-BIKE SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Register selected.\n";
        }
        else if (choice == 2) {
            cout << "Login selected.\n";
        }
        else if (choice == 3) {
            cout << "Exiting system...\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}