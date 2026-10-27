#include <iostream>
#include <climits>

#include "SystemSetup.h"
#include "ds/HashTable.h"
#include "ds/CustomQueue.h"
#include "ds/CustomStack.h"
#include "ds/MinHeap.h"
#include "managers/RentalManager.h"
#include "managers/UserManager.h"
#include "managers/BikeManager.h"
#include "managers/DockManager.h"
#include "managers/ReservationManager.h"
#include "managers/MaintenanceManager.h"

using namespace std;

int failed = 0;

void check(bool result, const char* name) {
    if (result) {
        cout << "PASS: " << name << '\n';
    } else {
        cout << "FAIL: " << name << '\n';
        failed++;
    }
}

int getDistance(const vector<LocationDistance>& distances, int locationID) {
    for (const LocationDistance& item : distances) {
        if (item.locationID == locationID) return item.distance;
    }
    return INT_MAX;
}

int main() {
    cout << "Campus E-Bike Tests\n\n";

    HashTable<int> table(1);
    check(table.insert(1, 10) && table.insert(4, 20), "hash table stores collision keys");
    check(!table.insert(1, 30), "hash table rejects duplicate keys");
    check(table.find(4) != nullptr && *table.find(4) == 20, "hash table retrieves stored value");
    check(table.erase(1) && !table.contains(1), "hash table removes a key");

    CustomQueue<int> queue;
    int value = -1;
    queue.enqueue(10);
    queue.enqueue(20);
    check(queue.dequeue(value) && value == 10, "queue removes first item first");
    check(queue.dequeue(value) && value == 20 && queue.empty(), "queue stays valid after final item");
    check(!queue.dequeue(value), "queue handles empty dequeue");

    CustomStack<int> stack;
    stack.push(10);
    stack.push(20);
    check(stack.pop(value) && value == 20, "stack removes last item first");
    check(stack.pop(value) && value == 10 && stack.empty(), "stack becomes empty safely");
    check(!stack.pop(value) && !stack.peek(value), "stack handles empty pop and peek");

    MinHeap heap;
    HeapNode node;
    heap.push(8, 1);
    heap.push(3, 2);
    heap.push(5, 3);
    check(heap.pop(node) && node.distance == 3 && node.locationID == 2, "min heap removes shortest item");

    Graph campus;
    UserManager userManager;
    BikeManager bikeManager;
    DockManager dockManager;
    RentalManager rentalManager;
    ReservationManager reservationManager;
    MaintenanceManager maintenanceManager;
    setupSystem(campus, dockManager, bikeManager);

    vector<LocationDistance> distances = campus.dijkstra(1);
    check(getDistance(distances, 3) == 3, "dijkstra finds Aquamarine A to Mega Mess 1 distance");
    check(getDistance(distances, 18) == 27, "dijkstra finds Aquamarine A to Dominos distance");
    check(campus.findNearestDock(1) == 1, "each campus location is a dock");
    vector<NearbyDock> nearbyDocks = campus.getNearbyDocks(1);
    check(nearbyDocks.size() == 18 && nearbyDocks[0].locationID == 1, "all campus docks are ordered by distance");
    check(campus.findNearestDock(999) == -1, "unknown graph location is safe");

    userManager.addUser(1, "Nirav", "nirav@example.com");
    userManager.addUser(2, "Rahul", "rahul@example.com");
    userManager.addUser(3, "Aditi", "aditi@example.com");
    userManager.addUser(1, "Duplicate", "duplicate@example.com");
    check(userManager.getUser(1) != nullptr, "user registration works");
    check(bikeManager.bikeExists(501), "sample bike exists");
    check(dockManager.findDockByLocation(1) != nullptr, "dock location lookup works");
    check(dockManager.getDock(101)->getCapacity() == 8, "dock capacity is initialized at 50 percent above bike count");

    check(rentalManager.rentBike(1, 101, userManager, bikeManager, dockManager), "first rental succeeds");
    check(rentalManager.rentBike(2, 101, userManager, bikeManager, dockManager), "second rental succeeds");
    check(dockManager.getDock(101)->getBikeCount() == 3, "bike count updates after rentals");
    check(reservationManager.addToQueue(3, 101, userManager, dockManager), "user joins dock queue");
    check(!reservationManager.addToQueue(3, 101, userManager, dockManager), "duplicate queue entry is rejected");
    check(rentalManager.returnBike(1, 101, userManager, bikeManager, dockManager, reservationManager), "return succeeds with waiting user");
    check(!userManager.getUser(1)->hasBike() && userManager.getUser(3)->hasBike(), "returned bike goes to waiting user");
    check(rentalManager.getActiveBike(3) != -1, "automatic rental is recorded");
    check(rentalManager.returnBike(2, 101, userManager, bikeManager, dockManager, reservationManager), "return succeeds with empty queue");
    check(dockManager.getDock(101)->getAvailableBike() != -1, "returned bike is stored at dock");
    check(!rentalManager.returnBike(2, 101, userManager, bikeManager, dockManager, reservationManager), "return without rental fails safely");
    check(maintenanceManager.reportBike(502, bikeManager, dockManager), "available dock bike enters maintenance");
    check(bikeManager.getBike(502)->isUnderMaintenance() && !dockManager.getDock(101)->hasBike(502), "maintenance bike is not rentable or docked");
    check(maintenanceManager.completeMaintenance(502, 102, bikeManager, dockManager), "maintenance can be completed at a dock");
    check(bikeManager.getBike(502)->isAvailable() && dockManager.getDock(102)->hasBike(502), "repaired bike returns to service");

    cout << '\n' << (failed == 0 ? "All tests passed.\n" : "Tests failed: ") ;
    if (failed != 0) cout << failed << '\n';
    return failed == 0 ? 0 : 1;
}
