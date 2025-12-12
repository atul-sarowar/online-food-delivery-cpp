#include "food_delivery_system.h"
#include "driver.h"
#include <iostream>
#include <limits>


static void clearInputLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

FoodDeliverySystem::FoodDeliverySystem()
    : pendingOrders(),
      drivers(),
      orderTable(),
      nextOrderId(1),
      currentTime(0) {
    seedDrivers();
}

// Asking user how many drivers there are and register them
void FoodDeliverySystem::seedDrivers() {
    int n;
    std::cout << "Enter number of delivery drivers to register: ";
    std::cin >> n;

    if (!std::cin || n <= 0) {
        std::cout << "Invalid number. Defaulting to 3 drivers.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        n = 3;
    }

    for (int i = 1; i <= n; ++i) {
        std::string name;
        std::cout << "Enter name for driver " << i << ": ";
        std::cin >> name;  
        Driver *d = new Driver(i, name, 0);
        allDrivers.push_back(d);
        // At the beginning, all drivers are available at time 0
        drivers.insert(d);
    }
}

FoodDeliverySystem::~FoodDeliverySystem() {
    for (Driver* driver : allDrivers) {
        delete driver;
    }
    for (Order* order : allOrders) {
        delete order;
    }
}

// ========== MODULE 1: Place Order ==========
void FoodDeliverySystem::placeOrder() {
    clearInputLine(); // Clearing leftover newline after reading int

    std::string name, address, items;

    std::cout << "Enter customer name: ";
    std::getline(std::cin, name);

    std::cout << "Enter delivery address: ";
    std::getline(std::cin, address);

    std::cout << "Enter items (comma-separated): ";
    std::getline(std::cin, items);

    Order *order = new Order(nextOrderId, name, address, items);
    allOrders.push_back(order);

    // Hash Map: Store order details (Track Active Orders)
    orderTable.put(order->id, order);

    // Queue: Enqueue new order (FIFO)
    pendingOrders.enqueue(order);

    std::cout << "Order placed successfully. Generated Order ID = "
              << order->id << "\n";

    ++nextOrderId;
}

// ========== MODULE 2: Assign Delivery Driver ==========
void FoodDeliverySystem::assignNextOrder() {
    if (pendingOrders.isEmpty()) {
        std::cout << "No pending orders in the queue.\n";
        return;
    }
    if (drivers.isEmpty()) {
        std::cout << "No AVAILABLE drivers in the system.\n";
        return;
    }

    // 1) Dequeue next order (FIFO)
    Order *order = pendingOrders.dequeue();

    // 2) Extract driver with LOWEST availability time from min-heap
    Driver *driver = drivers.extractMin();

    // Keep our simulated time at least as large as driver availability
    if (currentTime < driver->availableAt) {
        currentTime = driver->availableAt;
    }

    std::cout << "Assigning Order ID " << order->id
              << " to Driver " << driver->name
              << " (Driver ID " << driver->id << ").\n";

    int estMinutes;
    std::cout << "Enter estimated minutes for this delivery: ";
    std::cin >> estMinutes;

    if (!std::cin || estMinutes <= 0) {
        std::cout << "Invalid time. Assuming 30 minutes.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        estMinutes = 30;
    }

    
  // Update driver's next available time
    driver->availableAt = currentTime + estMinutes;

    // Order is now ASSIGNED
    order->status = OrderStatus::ASSIGNED;
    order->assignedDriverId = driver->id;
    order->assignedDriver = driver; // keep pointer for step 4

    currentTime += 1; // small step forward in simulated time

    
    std::cout << "Order assigned. Driver is now busy until simulated time "
              << driver->availableAt << ".\n";
}

// ========== MODULE 4: Complete Delivery ==========
void FoodDeliverySystem::completeDelivery() {
    int id;
    std::cout << "Enter Order ID to mark as delivered: ";
    std::cin >> id;

    Order *order = orderTable.get(id);
    if (!order) {
        std::cout << "Order not found.\n";
        return;
    }

    if (order->status == OrderStatus::DELIVERED) {
        std::cout << "Order is already delivered.\n";
        return;
    }

    if (order->status == OrderStatus::PENDING) {
        std::cout << "Order is still pending and has not been assigned yet.\n";
        return;
    }

    // Mark the order delivered
    order->status = OrderStatus::DELIVERED;
    std::cout << "Order ID " << order->id
              << " marked as DELIVERED successfully.\n";

 
    Driver *driver = order->assignedDriver;
    if (driver == nullptr) {
        std::cout << "Warning: No driver stored for this order.\n";
        return;
    }

    // Insert driver back into min-heap using its updated availableAt time
    drivers.insert(driver);
std::cout << "Driver " << driver->id << " is now free for new orders.\n";

    // Optionally clear pointer
    order->assignedDriver = nullptr;
}

// ========== MODULE 5: View Order Summary ==========
void FoodDeliverySystem::viewOrderSummary() {
    std::cout << "==== Order Summary (All Orders) ====\n";
    orderTable.printAll();
    std::cout << "====================================\n";
}
void FoodDeliverySystem::trackOrderById() {
    int id;
    std::cout << "Enter Order ID to view details: ";
    std::cin >> id;

    Order *order = orderTable.get(id);
    if (!order) {
        std::cout << "No order found with ID " << id << ".\n";
        return;
    }

    std::cout << "------------------------------\n";
    std::cout << "Order ID      : " << order->id << "\n";
    std::cout << "Customer Name : " << order->customerName << "\n";
    std::cout << "Address       : " << order->address << "\n";
    std::cout << "Items         : " << order->items << "\n";
    std::cout << "Status        : " << statusToString(order->status) << "\n";

    if (order->assignedDriverId == -1) {
        std::cout << "Driver        : Not assigned yet\n";
    } else {
        std::cout << "Driver ID     : " << order->assignedDriverId;
        if (order->assignedDriver != nullptr) {
            std::cout << " (" << order->assignedDriver->name << ")";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------\n";
}

// ========== MENU LOOP ==========
void FoodDeliverySystem::run() {
    while (true) {
        std::cout << "\n=== Online Food Delivery Order System ===\n";
        std::cout << "1. Place New Order\n";
        std::cout << "2. Assign Next Order to Driver\n";
        std::cout << "3. Mark Order as Delivered\n";
        std::cout << "4. View All Orders Summary\n";
        std::cout << "5. Track Order by ID\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";

        int choice;
        std::cin >> choice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: placeOrder();        break;
            case 2: assignNextOrder();   break;
            case 3: completeDelivery();  break;
            case 4: viewOrderSummary();  break;
            case 5: trackOrderById();    break;
            case 6:
                std::cout << "Exiting system. Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}
