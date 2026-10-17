#include "../../include/managers/RentalManager.h"

#include "../../include/managers/UserManager.h"
#include "../../include/managers/BikeManager.h"
#include "../../include/managers/DockManager.h"
#include "../../include/managers/ReservationManager.h"

#include "models/User.h"
#include "models/Bike.h"
#include "models/Dock.h"

#include <iostream>

using namespace std;


bool RentalManager::rentBike(
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

    if (user->hasBike()) {
        cout << "User already has a bike.\n";
        return false;
    }

    int bikeID = dock->getAvailableBike();

    if (bikeID == -1) {
        cout << "No bike available at Dock "
             << dockID << ".\n";

        return false;
    }

    Bike* bike = bikeManager.getBike(bikeID);

    if (bike == nullptr) {
        cout << "Bike data not found.\n";
        return false;
    }

    dock->removeBike(bikeID);

    bike->rentBike();

    user->assignBike(bikeID);

    activeRentals[userID] = bikeID;

    cout << "Bike " << bikeID
         << " assigned to User "
         << userID << ".\n";

    return true;
}