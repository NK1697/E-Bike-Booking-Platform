#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>

using namespace std;

struct HeapNode {
    int distance;
    int locationID;
};

class MinHeap {
private:
    vector<HeapNode> items;

    void swapNodes(int first, int second) {
        HeapNode temp = items[first];
        items[first] = items[second];
        items[second] = temp;
    }

    void moveUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (items[parent].distance <= items[index].distance) {
                break;
            }
            swapNodes(parent, index);
            index = parent;
        }
    }

    void moveDown(int index) {
        while (true) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int smallest = index;

            if (left < static_cast<int>(items.size()) && items[left].distance < items[smallest].distance) smallest = left;
            if (right < static_cast<int>(items.size()) && items[right].distance < items[smallest].distance) smallest = right;
            if (smallest == index) break;
            swapNodes(index, smallest);
            index = smallest;
        }
    }

public:
    void push(int distance, int locationID) {
        items.push_back({distance, locationID});
        moveUp(static_cast<int>(items.size()) - 1);
    }

    bool pop(HeapNode& node) {
        if (items.empty()) return false;
        node = items[0];
        items[0] = items.back();
        items.pop_back();
        if (!items.empty()) moveDown(0);
        return true;
    }

    bool empty() const { return items.empty(); }
    int size() const { return static_cast<int>(items.size()); }
};

#endif
