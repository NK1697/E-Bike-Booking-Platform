#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <vector>
#include "../ds/CustomQueue.h"

using namespace std;

class UserManager;
class DockManager;

struct DockQueue {
    int dockID;
    CustomQueue<int> users;
    DockQueue(int id) : dockID(id) {}
};

class ReservationManager {
    private:
        vector<DockQueue*> reservationQueues;
        DockQueue* getQueue(int dockID);
        const DockQueue* getQueue(int dockID) const;

    public:
        ~ReservationManager();
        bool addToQueue(
            int userID,
            int dockID,
            UserManager& userManager,
            DockManager& dockManager
        );
        bool hasWaitingUser(int dockID) const;
        int getNextUser(int dockID);
        void displayQueue(int dockID) const;
};

#endif
