#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using std::exception;
using std::string;

class BadPVIndex : public exception{

    private:
    string message{"Index is out of range"};

    public:
    BadPVIndex() = default;
    BadPVIndex(string s): message{s}{}

    const char* what() const noexcept{
        return message.c_str();
    }

};

#endif