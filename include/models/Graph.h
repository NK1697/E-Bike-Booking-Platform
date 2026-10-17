#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <climits>
#include <string>
#include <unordered_set>

using namespace std;

class Graph {
    private:
        unordered_set<int> dockLocations;
        unordered_map<int, vector<pair<int, int>>> adjacencyList;
        unordered_map<int, string> locationNames;
    public:
        unordered_map<int, int> dijkstra(int startLocation) const;
        void addLocation(int locationID, string name);
        void addRoad(
            int location1,
            int location2,
            int distance
        );
        void displayGraph() const;
        void markAsDock(int locationID);
        int findNearestDock(int startLocation) const;
};

#endif