#include "publisher.hpp"
#include "common.hpp"
#include <cassert>

Publisher::Publisher(
    const DBusBusType& arg_bus_type,
    const std::string& arg_bus_name
)   noexcept(false)
:   bus_type(arg_bus_type),
    bus_name(arg_bus_name) {
        
        DBusError err;
        ::dbus_error_init(&err);

        bus_conn = ::dbus_bus_get(bus_type, &err);

        assert(&err != nullptr);

        if (::dbus_error_is_set(&err)) {
            error_handler(&err);
        }

        ::dbus_bus_request_name(
            bus_conn,
            bus_name.c_str(),
            DBUS_NAME_FLAG_REPLACE_EXISTING,
            &err 
        );

        if (::dbus_error_is_set(&err)) {
            error_handler(&err);
        }

    }


Publisher::~Publisher(){
    ::dbus_connection_unref(bus_conn);
}

void Publisher::publish(
    const char*         arg_payload,
    const size_t&       arg_payload_size,
    const std::string&  arg_obj_path,
    const std::string&  arg_interface,
    const std::string&  arg_signal
)   const noexcept(false) {
    DBusMessage*    msg = nullptr;
    DBusMessageIter args;

    msg = ::dbus_message_new_signal(
        arg_obj_path.c_str(),
        arg_interface.c_str(),
        arg_signal.c_str()
    );

    assert(msg != nullptr);

    if (::dbus_message_append_args(
        msg,
        DBUS_TYPE_ARRAY,
        DBUS_TYPE_BYTE,
        &arg_payload,
        arg_payload_size,
        DBUS_TYPE_INVALID
    )) {
        throw std::bad_alloc();
    }

    ::dbus_message_set_no_reply(msg, true);

    if(not ::dbus_connection_send(
        bus_conn, 
        msg,
        nullptr
    )) {
        throw std::bad_alloc();
    }

    ::dbus_connection_flush(bus_conn);
    ::dbus_message_unref(msg);
}