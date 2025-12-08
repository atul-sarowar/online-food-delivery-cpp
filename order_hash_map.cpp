#include "order_hash_map.h"
#include <iostream>
#include "driver.h"


OrderHashMap::OrderHashMap(int initialSize)
    : table(initialSize, nullptr), numElements(0) {}

OrderHashMap::~OrderHashMap() {
    for (Node *head : table) {
        while (head) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
}

int OrderHashMap::hash(int key) const {
    if (key < 0) key = -key;
    return key % static_cast<int>(table.size());
}

Order *OrderHashMap::get(int key) const {
    int idx = hash(key);
    Node *cur = table[idx];
    while (cur) {
        if (cur->key == key) return cur->value;
        cur = cur->next;
    }
    return nullptr;
}

bool OrderHashMap::contains(int key) const {
    return get(key) != nullptr;
}

void OrderHashMap::put(int key, Order *value) {
    double load = static_cast<double>(numElements) / table.size();
    if (load > 0.75) {
        rehash();
    }

    int idx = hash(key);
    Node *cur = table[idx];

    while (cur) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }

    Node *node = new Node(key, value);
    node->next = table[idx];
    table[idx] = node;
    ++numElements;
}

void OrderHashMap::remove(int key) {
    int idx = hash(key);
    Node *cur = table[idx];
    Node *prev = nullptr;

    while (cur) {
        if (cur->key == key) {
            if (prev) prev->next = cur->next;
            else      table[idx] = cur->next;
            delete cur;
            --numElements;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void OrderHashMap::rehash() {
    std::vector<Node*> oldTable = table;
    table.assign(oldTable.size() * 2 + 1, nullptr);
    numElements = 0;

    for (Node *head : oldTable) {
        Node *cur = head;
        while (cur) {
            put(cur->key, cur->value);
            Node *tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
}

void OrderHashMap::printAll() const {
    for (Node *head : table) {
        Node *cur = head;
        while (cur) {
            Order *o = cur->value;
            std::cout << "Order ID: " << o->id
                      << " | Customer: " << o->customerName
                      << " | Status: " << statusToString(o->status);

            if (o->assignedDriverId == -1) {
                std::cout << " | Driver: (Not assigned)";
            } else {
                std::cout << " | Driver ID: " << o->assignedDriverId;
                if (o->assignedDriver != nullptr) {
                    std::cout << " (" << o->assignedDriver->name << ")";
                }
            }
            std::cout << '\n';
            cur = cur->next;
        }
    }
}
