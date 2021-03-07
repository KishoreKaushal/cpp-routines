#ifndef DBUS_COMMON_HPP
#define DBUS_COMMON_HPP

#include "dbus/dbus.h"
#include <iostream>
#include <stdexcept>

inline void error_handler(DBusError* err) {
    std::cout << "DBusError.name: " << err->name << "\n";
    std::cout << "DBusError.message: " << err->message << std::endl;
    ::dbus_error_free(err);
    throw std::runtime_error("DBusError");
}

#endif