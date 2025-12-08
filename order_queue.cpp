#include "order_queue.h"
#include <stdexcept>

OrderQueue::OrderQueue(int cap)
    : capacity(cap), front(0), rear(0), count(0) {
    data = new Order*[capacity];
}

OrderQueue::~OrderQueue() {
    delete[] data;
}

bool OrderQueue::isEmpty() const {
    return count == 0;
}

int OrderQueue::size() const {
    return count;
}

void OrderQueue::resize() {
    int newCap = capacity * 2;
    Order **newData = new Order*[newCap];

    for (int i = 0; i < count; ++i) {
        newData[i] = data[(front + i) % capacity];
    }

    delete[] data;
    data = newData;
    capacity = newCap;
    front = 0;
    rear = count;
}

void OrderQueue::enqueue(Order *o) {
    if (count == capacity) {
        resize();
    }
    data[rear] = o;
    rear = (rear + 1) % capacity;
    ++count;
}

Order *OrderQueue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue underflow: no pending orders.");
    }
    Order *o = data[front];
    front = (front + 1) % capacity;
    --count;
    return o;
}

Order *OrderQueue::peek() const {
    if (isEmpty()) return nullptr;
    return data[front];
}
