#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

template <typename T>
class CustomQueue {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& newValue) : value(newValue), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int itemCount;

public:
    CustomQueue() : frontNode(nullptr), rearNode(nullptr), itemCount(0) {}
    ~CustomQueue() { clear(); }

    CustomQueue(const CustomQueue&) = delete;
    CustomQueue& operator=(const CustomQueue&) = delete;

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (rearNode == nullptr) {
            frontNode = newNode;
            rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        itemCount++;
    }

    bool dequeue(T& value) {
        if (frontNode == nullptr) {
            return false;
        }
        Node* oldNode = frontNode;
        value = oldNode->value;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete oldNode;
        itemCount--;
        return true;
    }

    bool peek(T& value) const {
        if (frontNode == nullptr) {
            return false;
        }
        value = frontNode->value;
        return true;
    }

    bool empty() const { return frontNode == nullptr; }
    int size() const { return itemCount; }

    bool contains(const T& value) const {
        Node* current = frontNode;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(const T& value) {
        Node* current = frontNode;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->value == value) {
                if (previous == nullptr) frontNode = current->next;
                else previous->next = current->next;
                if (current == rearNode) rearNode = previous;
                delete current;
                itemCount--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    template <typename Func>
    void forEach(Func action) const {
        Node* current = frontNode;
        while (current != nullptr) {
            action(current->value);
            current = current->next;
        }
    }

    void clear() {
        T value;
        while (dequeue(value)) {}
    }
};

#endif
