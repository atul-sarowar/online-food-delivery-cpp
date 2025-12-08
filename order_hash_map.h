#ifndef ORDER_HASH_MAP_H
#define ORDER_HASH_MAP_H

#include "order.h"
#include <vector>

class OrderHashMap {
private:
    struct Node {
        int key;
        Order *value;
        Node *next;
        Node(int k, Order *v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Node*> table;
    int numElements;

    int hash(int key) const;
    void rehash();

public:
    OrderHashMap(int initialSize = 101);
    ~OrderHashMap();

    void put(int key, Order *value);  // add/update
    Order *get(int key) const;        // Track Active Orders
    bool contains(int key) const;
    void remove(int key);

    void printAll() const;            // View Order Summary
};

#endif // ORDER_HASH_MAP_H
