#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <string>
#include <exception>

class Exception : public std::exception {
    std::string file;
    int         line;
    std::string name;
    std::string info;
    std::string msg;

public:
    Exception(
        const std::string&  arg_file,
        const int&          arg_line,
        const std::string&  arg_name,
        const std::string&  arg_info
    ):  file(arg_file),
        line(arg_line),
        name(arg_name),
        info(arg_info),
        msg("") {

            msg += file;
            msg += "#";
            msg += std::to_string(line);
            msg += ": ";
            msg += name;
            msg += ": ";
            msg += info;
            msg += "\n";
    }

    const char* what() const noexcept {
        return msg.c_str();
    }
};

#define THROW_CUSTOM_EXCEPTION(name, info) throw Exception(__FILE__, __LINE__, name, info)

#endif 