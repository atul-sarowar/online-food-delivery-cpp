#ifndef ORDER_H
#define ORDER_H

#include <string>

// Forward declaration to avoid circular include
struct Driver;

enum class OrderStatus {
    PENDING,
    ASSIGNED,
    DELIVERED
};

struct Order {
    int id;
    std::string customerName;
    std::string address;
    std::string items;
    OrderStatus status;

    int assignedDriverId;   // -1 if not yet assigned
    Driver* assignedDriver; // pointer to driver handling this order (used in step 4)

    Order();
    Order(int id,
          const std::string &cname,
          const std::string &addr,
          const std::string &items);
};

std::string statusToString(OrderStatus s);

#endif // ORDER_H
