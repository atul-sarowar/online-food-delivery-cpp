#include "order.h"

Order::Order()
    : id(-1),
      customerName(""),
      address(""),
      items(""),
      status(OrderStatus::PENDING),
      assignedDriverId(-1),
      assignedDriver(nullptr) {}

Order::Order(int id_,
             const std::string &cname,
             const std::string &addr,
             const std::string &items_)
    : id(id_),
      customerName(cname),
      address(addr),
      items(items_),
      status(OrderStatus::PENDING),
      assignedDriverId(-1),
      assignedDriver(nullptr) {}

std::string statusToString(OrderStatus s) {
    switch (s) {
        case OrderStatus::PENDING:   return "Pending";
        case OrderStatus::ASSIGNED:  return "Assigned";
        case OrderStatus::DELIVERED: return "Delivered";
        default:                     return "Unknown";
    }
}
