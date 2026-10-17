#include "../../include/models/Graph.h"
#include <climits>
#include <queue>
#include <iostream>
using namespace std;

void Graph::addLocation(int locationID, string name) {
    if (locationNames.find(locationID) != locationNames.end()) {
        cout << "Location " << locationID << " already exists.\n";
        return;
    }
    locationNames[locationID] = name;
    adjacencyList[locationID];
    cout << "Location " << name << " added successfully.\n";
}

void Graph::addRoad(int location1, int location2, int distance){
    if (locationNames.find(location1) == locationNames.end() ||
        locationNames.find(location2) == locationNames.end()) {
        cout << "One or both locations do not exist.\n";
        return;
    }
    adjacencyList[location1].push_back(
        {location2, distance}
    );
    adjacencyList[location2].push_back(
        {location1, distance}
    );
    cout << "Road added between " << locationNames[location1] << " and " << locationNames[location2] << ".\n";
}

void Graph::displayGraph() const {
    for (const auto& location : adjacencyList) {
        int locationID = location.first;
        cout << locationNames.at(locationID) << " (" << locationID << ")" << " -> ";
        for (const auto& neighbour : location.second) {
            int neighbourID = neighbour.first;
            int distance = neighbour.second;
            cout << locationNames.at(neighbourID)
                 << "[" << distance << "] ";
        }
        cout << '\n';
    }
}

unordered_map<int, int> Graph::dijkstra(int startLocation) const{
    unordered_map<int, int> distance;
    for (const auto& location : locationNames) {
        distance[location.first] = INT_MAX;
    }

    distance[startLocation] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int> >> pq;
    pq.push({0, startLocation});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int currentLocation = pq.top().second;

        pq.pop();

        if (currentDistance > distance[currentLocation]) {
            continue;
        }

        for (const auto& neighbour : adjacencyList.at(currentLocation)) {
            int neighbourID = neighbour.first;
            int roadDistance = neighbour.second;

            int newDistance = currentDistance + roadDistance;

            if (newDistance < distance[neighbourID]) {
                distance[neighbourID] = newDistance;
                pq.push({newDistance, neighbourID});
            }
        }
    }
    return distance;
}

void Graph::markAsDock(int locationID) {
    if (locationNames.find(locationID) == locationNames.end()) {
        cout << "Location does not exist.\n";
        return;
    }

    dockLocations.insert(locationID);

    cout << locationNames.at(locationID) << " marked as a bike dock.\n";
}

int Graph::findNearestDock(int startLocation) const {
    if (locationNames.find(startLocation) == locationNames.end()) {
        return -1;
    }

    unordered_map<int, int> distance;
    for (const auto& location : locationNames) {
        distance[location.first] = INT_MAX;
    }

    distance[startLocation] = 0;
    priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>> > pq;

    pq.push({0, startLocation});
    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int currentLocation = pq.top().second;

        pq.pop();
        if (currentDistance >
            distance[currentLocation]) {
            continue;
        }
        if (dockLocations.find(currentLocation) !=
            dockLocations.end()) {

            return currentLocation;
        }
        for (const auto& neighbour : adjacencyList.at(currentLocation)) {
            int neighbourID = neighbour.first;
            int roadDistance = neighbour.second;

            int newDistance = currentDistance + roadDistance;

            if (newDistance < distance[neighbourID]) {
                distance[neighbourID] = newDistance;
                pq.push({newDistance, neighbourID});
            }
        }
    }
    return -1;
}