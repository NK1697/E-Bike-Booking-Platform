#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

template <typename T>
class CustomStack {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& newValue) : value(newValue), next(nullptr) {}
    };
    Node* topNode;
    int itemCount;

public:
    CustomStack() : topNode(nullptr), itemCount(0) {}
    ~CustomStack() { clear(); }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        itemCount++;
    }

    bool pop(T& value) {
        if (topNode == nullptr) return false;
        Node* oldNode = topNode;
        value = oldNode->value;
        topNode = topNode->next;
        delete oldNode;
        itemCount--;
        return true;
    }

    bool peek(T& value) const {
        if (topNode == nullptr) return false;
        value = topNode->value;
        return true;
    }

    bool empty() const { return topNode == nullptr; }
    int size() const { return itemCount; }

    void clear() {
        T value;
        while (pop(value)) {}
    }
};

#endif
