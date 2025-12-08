#ifndef DRIVER_H
#define DRIVER_H

#include <string>

struct Driver {
    int id;
    std::string name;
    int availableAt;   // simulated "next available time"

    Driver();
    Driver(int id, const std::string &name, int availableAt);
};

#endif 
