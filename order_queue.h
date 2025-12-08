#ifndef ORDER_QUEUE_H
#define ORDER_QUEUE_H

#include "order.h"

class OrderQueue {
private:
    Order **data;
    int capacity;
    int front;
    int rear;
    int count;

    void resize();

public:
    OrderQueue(int cap = 10);
    ~OrderQueue();

    bool isEmpty() const;
    int size() const;

    void enqueue(Order *o);   // Place Order
    Order *dequeue();         // used in Assign Delivery Driver
    Order *peek() const;
};

#endif // ORDER_QUEUE_H
