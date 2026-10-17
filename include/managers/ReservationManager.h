#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <unordered_map>
#include <queue>

using namespace std;

class UserManager;
class BikeManager;
class DockManager;

class ReservationManager {
    private:
        unordered_map<int, queue<int>> reservationQueues;

    public:
        bool requestBike(
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
            DockManager& dockManager
        );

        void displayQueue(int dockID) const;
};

#endif