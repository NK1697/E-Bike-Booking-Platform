#ifndef RENTAL_MANAGER_H
#define RENTAL_MANAGER_H

#include <unordered_map>

using namespace std;

class UserManager;
class BikeManager;
class DockManager;
class ReservationManager;

class RentalManager {
    private:
        unordered_map<int, int> activeRentals;

    public:
        bool rentBike(
            int userID,
            int dockID,
            UserManager& userManager,
            BikeManager& bikeManager,
            DockManager& dockManager
        );
        bool returnBike(
            int userID,
            int dockID,
            UserManager& userManager,
            BikeManager& bikeManager,
            DockManager& dockManager,
            ReservationManager& reservationManager
        );
        int getActiveBike(int userID) const;
};

#endif