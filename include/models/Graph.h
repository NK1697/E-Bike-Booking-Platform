#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <climits>
#include <string>
#include "../ds/MinHeap.h"

using namespace std;

struct Edge {
    int destinationLocationID;
    int distance;
};

struct LocationData {
    int locationID;
    string name;
    vector<Edge> roads;
    bool isDock;
};

struct LocationDistance {
    int locationID;
    int distance;
};

struct NearbyDock {
    int locationID;
    int distance;
};

class Graph {
    private:
        vector<LocationData> locations;
        int getLocationIndex(int locationID) const;
    public:
        vector<LocationDistance> dijkstra(int startLocation) const;
        void addLocation(int locationID, string name);
        void addRoad(
            int location1,
            int location2,
            int distance
        );
        void displayGraph() const;
        void markAsDock(int locationID);
        int findNearestDock(int startLocation) const;
        vector<NearbyDock> getNearbyDocks(int startLocation) const;
};

#endif
