#include "driver_min_heap.h"
#include <stdexcept>

DriverMinHeap::DriverMinHeap(int cap)
    : capacity(cap), heapSize(0) {
    data = new Driver*[capacity];
}

DriverMinHeap::~DriverMinHeap() {
    delete[] data;
}

bool DriverMinHeap::isEmpty() const {
    return heapSize == 0;
}

int DriverMinHeap::size() const {
    return heapSize;
}

void DriverMinHeap::resize() {
    int newCap = capacity * 2;
    Driver **newData = new Driver*[newCap];
    for (int i = 0; i < heapSize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCap;
}

void DriverMinHeap::heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (data[idx]->availableAt < data[parent]->availableAt) {
            Driver *tmp = data[idx];
            data[idx] = data[parent];
            data[parent] = tmp;
            idx = parent;
        } else {
            break;
        }
    }
}

void DriverMinHeap::heapifyDown(int idx) {
    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < heapSize &&
            data[left]->availableAt < data[smallest]->availableAt) {
            smallest = left;
        }
        if (right < heapSize &&
            data[right]->availableAt < data[smallest]->availableAt) {
            smallest = right;
        }
        if (smallest != idx) {
            Driver *tmp = data[idx];
            data[idx] = data[smallest];
            data[smallest] = tmp;
            idx = smallest;
        } else {
            break;
        }
    }
}

void DriverMinHeap::insert(Driver *d) {
    if (heapSize == capacity) {
        resize();
    }
    data[heapSize] = d;
    heapifyUp(heapSize);
    ++heapSize;
}

Driver *DriverMinHeap::getMin() const {
    if (isEmpty()) return nullptr;
    return data[0];
}

Driver *DriverMinHeap::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("No drivers available (heap empty).");
    }
    Driver *min = data[0];
    data[0] = data[heapSize - 1];
    --heapSize;
    heapifyDown(0);
    return min;
}
