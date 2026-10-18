#include "../../include/models/Graph.h"
#include <climits>
#include <iostream>
using namespace std;

int Graph::getLocationIndex(int locationID) const {
    for (int i = 0; i < static_cast<int>(locations.size()); i++) {
        if (locations[i].locationID == locationID) return i;
    }
    return -1;
}

void Graph::addLocation(int locationID, string name) {
    if (getLocationIndex(locationID) != -1) {
        cout << "Location " << locationID << " already exists.\n";
        return;
    }
    locations.push_back({locationID, name, vector<Edge>(), false});
    cout << "Location " << name << " added successfully.\n";
}

void Graph::addRoad(int location1, int location2, int distance){
    int firstIndex = getLocationIndex(location1);
    int secondIndex = getLocationIndex(location2);
    if (firstIndex == -1 || secondIndex == -1) {
        cout << "One or both locations do not exist.\n";
        return;
    }
    if (distance <= 0) {
        cout << "Road distance must be positive.\n";
        return;
    }
    locations[firstIndex].roads.push_back({location2, distance});
    locations[secondIndex].roads.push_back({location1, distance});
    cout << "Road added between " << locations[firstIndex].name << " and " << locations[secondIndex].name << ".\n";
}

void Graph::displayGraph() const {
    for (const LocationData& location : locations) {
        cout << location.name << " (" << location.locationID << ") -> ";
        for (const Edge& road : location.roads) {
            int neighbourIndex = getLocationIndex(road.destinationLocationID);
            cout << locations[neighbourIndex].name
                 << "[" << road.distance << "] ";
        }
        cout << '\n';
    }
}

vector<LocationDistance> Graph::dijkstra(int startLocation) const {
    vector<LocationDistance> distances;
    for (const LocationData& location : locations) distances.push_back({location.locationID, INT_MAX});
    int startIndex = getLocationIndex(startLocation);
    if (startIndex == -1) return distances;
    distances[startIndex].distance = 0;
    MinHeap heap;
    heap.push(0, startLocation);
    HeapNode current;
    while (heap.pop(current)) {
        int currentIndex = getLocationIndex(current.locationID);
        if (current.distance > distances[currentIndex].distance) continue;
        for (const Edge& road : locations[currentIndex].roads) {
            int nextIndex = getLocationIndex(road.destinationLocationID);
            int newDistance = current.distance + road.distance;
            if (newDistance < distances[nextIndex].distance) {
                distances[nextIndex].distance = newDistance;
                heap.push(newDistance, road.destinationLocationID);
            }
        }
    }
    return distances;
}

void Graph::markAsDock(int locationID) {
    int index = getLocationIndex(locationID);
    if (index == -1) {
        cout << "Location does not exist.\n";
        return;
    }

    locations[index].isDock = true;
    cout << locations[index].name << " marked as a bike dock.\n";
}

int Graph::findNearestDock(int startLocation) const {
    if (getLocationIndex(startLocation) == -1) {
        return -1;
    }

    vector<LocationDistance> distances = dijkstra(startLocation);
    int nearestLocation = -1;
    int nearestDistance = INT_MAX;
    for (int i = 0; i < static_cast<int>(locations.size()); i++) {
        if (locations[i].isDock && distances[i].distance < nearestDistance) {
            nearestDistance = distances[i].distance;
            nearestLocation = locations[i].locationID;
        }
    }
    return nearestLocation;
}

vector<NearbyDock> Graph::getNearbyDocks(int startLocation) const {
    vector<NearbyDock> nearbyDocks;
    if (getLocationIndex(startLocation) == -1) return nearbyDocks;

    vector<LocationDistance> distances = dijkstra(startLocation);
    for (int i = 0; i < static_cast<int>(locations.size()); i++) {
        if (locations[i].isDock && distances[i].distance != INT_MAX) {
            nearbyDocks.push_back({locations[i].locationID, distances[i].distance});
        }
    }

    for (int i = 0; i < static_cast<int>(nearbyDocks.size()); i++) {
        int smallest = i;
        for (int j = i + 1; j < static_cast<int>(nearbyDocks.size()); j++) {
            if (nearbyDocks[j].distance < nearbyDocks[smallest].distance) smallest = j;
        }
        if (smallest != i) {
            NearbyDock temp = nearbyDocks[i];
            nearbyDocks[i] = nearbyDocks[smallest];
            nearbyDocks[smallest] = temp;
        }
    }
    return nearbyDocks;
}
