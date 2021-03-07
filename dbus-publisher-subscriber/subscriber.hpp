#ifndef DBUS_SUBSCRIBER_HPP
#define DBUS_SUBSCRIBER_HPP

#include <dbus/dbus.h>
#include <string>
#include <memory>

class Subscriber {
    DBusBusType     bus_type;
    DBusConnection* bus_conn;
    std::string&    bus_name;
    std::string&    bus_interface;

public:

    Subscriber(
        const DBusBusType&  arg_bus_type,
        const std::string&  arg_bus_name,
        const std::string&  arg_bus_interface
    )   noexcept(false);

    virtual ~Subscriber();

    virtual std::unique_ptr<char[]> consume(
        const std::string&  arg_signal,
        int&                get_payload_size, 
        const int&          arg_receive_timeout_ms
    )   const noexcept(false);

};

#endif