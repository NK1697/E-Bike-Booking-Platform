#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>

using namespace std;

template <typename T>
class HashTable {
private:
    struct Node {
        int key;
        T value;
        Node* next;

        Node(int newKey, const T& newValue) : key(newKey), value(newValue), next(nullptr) {}
    };

    vector<Node*> buckets;
    int itemCount;

    int getIndex(int key) const {
        int index = key % static_cast<int>(buckets.size());
        return index < 0 ? index + static_cast<int>(buckets.size()) : index;
    }

    void grow() {
        vector<Node*> oldBuckets = buckets;
        buckets.assign(buckets.size() * 2 + 1, nullptr);
        itemCount = 0;

        for (Node* head : oldBuckets) {
            while (head != nullptr) {
                Node* nextNode = head->next;
                insert(head->key, head->value);
                delete head;
                head = nextNode;
            }
        }
    }

public:
    HashTable(int size = 11) : buckets(size, nullptr), itemCount(0) {}

    ~HashTable() {
        clear();
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool insert(int key, const T& value) {
        if (contains(key)) {
            return false;
        }

        if ((itemCount + 1) * 4 > static_cast<int>(buckets.size()) * 3) {
            grow();
        }

        int index = getIndex(key);
        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        itemCount++;
        return true;
    }

    T* find(int key) {
        Node* current = buckets[getIndex(key)];
        while (current != nullptr) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    const T* find(int key) const {
        Node* current = buckets[getIndex(key)];
        while (current != nullptr) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool contains(int key) const {
        return find(key) != nullptr;
    }

    bool erase(int key) {
        int index = getIndex(key);
        Node* current = buckets[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    buckets[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                itemCount--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool empty() const { return itemCount == 0; }
    int size() const { return itemCount; }

    template <typename Func>
    void forEach(Func action) {
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                action(current->key, current->value);
                current = current->next;
            }
        }
    }

    template <typename Func>
    void forEach(Func action) const {
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                action(current->key, current->value);
                current = current->next;
            }
        }
    }

    void clear() {
        for (Node*& head : buckets) {
            while (head != nullptr) {
                Node* nextNode = head->next;
                delete head;
                head = nextNode;
            }
        }
        itemCount = 0;
    }
};

#endif
