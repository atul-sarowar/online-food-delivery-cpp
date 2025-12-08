#ifndef DRIVER_MIN_HEAP_H
#define DRIVER_MIN_HEAP_H

#include "driver.h"

class DriverMinHeap {
private:
    Driver **data;
    int capacity;
    int heapSize;

    void resize();
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    DriverMinHeap(int cap = 10);
    ~DriverMinHeap();

    bool isEmpty() const;
    int size() const;

    void insert(Driver *d);    // insert available driver
    Driver *getMin() const;    // view next available driver
    Driver *extractMin();      
};

#endif 
