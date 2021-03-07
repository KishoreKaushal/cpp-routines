#ifndef DBUS_PUBLISHER_HPP
#define DBUS_PUBLISHER_HPP

#include <dbus/dbus.h>
#include <string>

class Publisher {
    DBusBusType         bus_type;
    DBusConnection*     bus_conn;
    std::string         bus_name;

public:
    Publisher(const Publisher&) = delete;

    Publisher& operator=(const Publisher&) = delete;

    Publisher(
        const DBusBusType& arg_bus_type,
        const std::string& arg_bus_name
    )   noexcept(false);

    virtual ~Publisher();

    virtual void publish(
        const char*         arg_payload,
        const size_t&       arg_payload_size,
        const std::string&  arg_obj_path,
        const std::string&  arg_interface,
        const std::string&  arg_signal
    )   const noexcept(false);

};

#endif