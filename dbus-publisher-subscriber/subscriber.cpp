#include "common.hpp"
#include "subscriber.hpp"
#include <cassert>
#include <sstream>
#include <cstring>

Subscriber::Subscriber(
    const DBusBusType&  arg_bus_type,
    const std::string&  arg_bus_name,
    const std::string&  arg_bus_interface
)   noexcept(false)
:   bus_type(arg_bus_type),
    bus_name(arg_bus_name),
    bus_interface(arg_bus_interface) {

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

        std::stringstream rule_stringstream;
        rule_stringstream << "type='signal',interface=" << bus_interface << "'";

        ::dbus_bus_add_match(bus_conn, rule_stringstream.str().c_str(), &err);

        ::dbus_connection_flush(bus_conn);

        if (::dbus_error_is_set(&err)) {
            error_handler(&err);
        }

        ::dbus_error_free(&err);
    }

Subscriber::~Subscriber() {
    ::dbus_connection_unref(bus_conn);
}

std::unique_ptr<char[]> Subscriber::consume(
    const std::string&  arg_signal,
    int&                get_payload_size,
    const int&          arg_receive_timeout_ms
)   const noexcept(false) {
    char* buff = nullptr;

    std::unique_ptr<char[]> uptr_buff;
    
    int receive_buff_size = -1;

    ::dbus_connection_read_write(bus_conn, arg_receive_timeout_ms);

    DBusMessage* msg = ::dbus_connection_pop_message(bus_conn);

    DBusError err;
    ::dbus_error_init(&err);

    if (msg != nullptr && 
        ::dbus_message_is_signal(
            msg,
            bus_interface.c_str(),
            arg_signal.c_str()
    )) {
        if (not ::dbus_message_get_args(
            msg, 
            &err,
            DBUS_TYPE_ARRAY,
            DBUS_TYPE_BYTE,
            buff,
            &receive_buff_size,
            DBUS_TYPE_INVALID
        ) && receive_buff_size != 0) {
            return nullptr; // DBUS_HANDLER_RESULT_NOT_YET_HANDLED
        }

        uptr_buff.reset(new char[receive_buff_size]);

        memcpy(uptr_buff.get(), buff, receive_buff_size);

        get_payload_size = receive_buff_size;
    }

    ::dbus_error_free(&err);
    ::dbus_message_unref(msg);

    return std::move(uptr_buff);
}