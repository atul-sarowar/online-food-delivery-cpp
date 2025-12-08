#ifndef FOOD_DELIVERY_SYSTEM_H
#define FOOD_DELIVERY_SYSTEM_H

#include "order_queue.h"
#include "driver_min_heap.h"
#include "order_hash_map.h"

class FoodDeliverySystem {
private:
    OrderQueue      pendingOrders; // Queue of incoming orders
    DriverMinHeap   drivers;       // Min-heap of AVAILABLE drivers
    OrderHashMap    orderTable;    // Hash map: orderId -> Order*

    int nextOrderId;
    int currentTime;               // simulated time units

    void seedDrivers();            // initial registration

public:
    FoodDeliverySystem();

    void placeOrder();             // Module 1
    void assignNextOrder();        // Module 2
    void completeDelivery();       // Module 4
    void viewOrderSummary();       // Module 5
              
    void trackOrderById();         // Module 3 – Track Active Orders


    void run();                    // terminal menu
};

#endif // FOOD_DELIVERY_SYSTEM_H
