#include "driver.h"

Driver::Driver()
    : id(-1), name(""), availableAt(0) {}

Driver::Driver(int id_,
               const std::string &name_,
               int availableAt_)
    : id(id_), name(name_), availableAt(availableAt_) {}
