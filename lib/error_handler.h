#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"

#define ERROR(msg) ErrorHandler::reportError(__FILE__, __LINE__, __func__, msg)

class ErrorHandler {
public:
    static void reportError(const char* file, int line, const char* func, const std::string& msg) {
        std::cerr << RED << "Error: " << msg << RESET << std::endl;
        std::cerr << "In file: " << file << ", line: " << line << ", function: " << func << std::endl;
        exit(EXIT_FAILURE);
    }
};
#endif