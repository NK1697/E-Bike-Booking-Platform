#include "ReservationManager.h"
#include "UserManager.h"
#include "BikeManager.h"
#include "DockManager.h"

#include <iostream>

using namespace std;

bool ReservationManager::requestBike(
    int userID,
    int dockID,
    UserManager& userManager,
    BikeManager& bikeManager,
    DockManager& dockManager
) 

{
    User* user = userManager.getUser(userID);
    if (user == nullptr) {
        cout << "User does not exist.\n";
        return false;
    }

    Dock* dock = dockManager.getDock(dockID);
    if (dock == nullptr) {
        cout << "Dock does not exist.\n";
        return false;
    }
    if (user->hasBike()) {
        cout << "User already has a bike.\n";
        return false;
    }
    int bikeID = dock->getAvailableBike();
    if (bikeID == -1) {
        reservationQueues[dockID].push(userID);
        cout << "No bike available at Dock " << dockID << ".\n";
        cout << "User " << userID << " added to reservation queue.\n";
        return true;
    }

    Bike* bike = bikeManager.getBike(bikeID);
    if (bike == nullptr) {
        cout << "Bike data not found.\n";
        return false;
    }
    dock->removeBike(bikeID);
    bike->rentBike();
    user->assignBike(bikeID);
    cout << "Bike " << bikeID << " assigned to User " << userID << ".\n";
    return true;
}

bool ReservationManager::returnBike(
    int userID,
    int dockID,
    UserManager& userManager,
    BikeManager& bikeManager,
    DockManager& dockManager
) {
    User* user = userManager.getUser(userID);
    if (user == nullptr) {
        cout << "User does not exist.\n";
        return false;
    }

    Dock* dock = dockManager.getDock(dockID);
    if (dock == nullptr) {
        cout << "Dock does not exist.\n";
        return false;
    }
    if (!user->hasBike()) {
        cout << "User does not have a bike.\n";
        return false;
    }
    int bikeID = user->getCurrentBike();
    Bike* bike = bikeManager.getBike(bikeID);
    if (bike == nullptr) {
        cout << "Bike data not found.\n";
        return false;
    }
    user->returnBike();
    bike->returnBike();
    cout << "User " << userID << " returned Bike " << bikeID << ".\n";

    auto it = reservationQueues.find(dockID);

    if (it != reservationQueues.end() &&
        !it->second.empty()) {
        int nextUserID = it->second.front();
        it->second.pop();

        User* nextUser = userManager.getUser(nextUserID);
        if (nextUser != nullptr) {
            nextUser->assignBike(bikeID);
            bike->rentBike();
            cout << "Bike " << bikeID << " automatically assigned to User " << nextUserID << ".\n";
            return true;
        }
    }
    dock->addBike(bikeID);
    cout << "Bike " << bikeID
         << " is now available at Dock "
         << dockID << ".\n";

    return true;
}

void ReservationManager::displayQueue(int dockID) const {
    auto it = reservationQueues.find(dockID);
    if (it == reservationQueues.end() || it->second.empty()) {
        cout << "No users waiting at Dock " << dockID << ".\n";
        return;
    }
    queue<int> temp = it->second;
    cout << "Reservation Queue for Dock " << dockID << ": ";
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << '\n';
}