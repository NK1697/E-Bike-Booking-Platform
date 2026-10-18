#include "../../include/managers/ReservationManager.h"
#include "../../include/managers/UserManager.h"
#include "../../include/managers/DockManager.h"

#include <iostream>

using namespace std;

ReservationManager::~ReservationManager() {
    for (DockQueue* queue : reservationQueues) delete queue;
}

DockQueue* ReservationManager::getQueue(int dockID) {
    for (DockQueue* queue : reservationQueues) {
        if (queue->dockID == dockID) return queue;
    }
    return nullptr;
}

const DockQueue* ReservationManager::getQueue(int dockID) const {
    for (const DockQueue* queue : reservationQueues) {
        if (queue->dockID == dockID) return queue;
    }
    return nullptr;
}

bool ReservationManager::addToQueue(int userID, int dockID, UserManager& userManager, DockManager& dockManager) {
    User* user = userManager.getUser(userID);
    if (user == nullptr) {
        cout << "User does not exist.\n";
        return false;
    }
    if (dockManager.getDock(dockID) == nullptr) {
        cout << "Dock does not exist.\n";
        return false;
    }
    if (user->hasBike()) {
        cout << "User already has a bike.\n";
        return false;
    }

    DockQueue* queue = getQueue(dockID);
    if (queue == nullptr) {
        queue = new DockQueue(dockID);
        reservationQueues.push_back(queue);
    }
    if (queue->users.contains(userID)) {
        cout << "User is already waiting at this dock.\n";
        return false;
    }

    queue->users.enqueue(userID);
    cout << "User " << userID << " added to the reservation queue.\n";
    return true;
}

bool ReservationManager::hasWaitingUser(int dockID) const {
    const DockQueue* queue = getQueue(dockID);
    return queue != nullptr && !queue->users.empty();
}

int ReservationManager::getNextUser(int dockID) {
    DockQueue* queue = getQueue(dockID);
    int userID;
    if (queue == nullptr || !queue->users.dequeue(userID)) return -1;
    return userID;
}

void ReservationManager::displayQueue(int dockID) const {
    const DockQueue* queue = getQueue(dockID);
    if (queue == nullptr || queue->users.empty()) {
        cout << "No users waiting at Dock " << dockID << ".\n";
        return;
    }
    cout << "Reservation Queue for Dock " << dockID << ": ";
    queue->users.forEach([](int userID) { cout << userID << " "; });
    cout << '\n';
}
