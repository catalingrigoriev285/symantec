#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "../log/log.h"

namespace Models
{
    class Exception : Log
    {
    public:
        Exception(const std::string &title, const std::string &description)
            : Log(LogType::ERROR, title, description) {}

        ~Exception() = default;

        void setParameters(const std::string &title, const std::string &description);

        friend std::ostream &operator<<(std::ostream &os, const Exception &exception)
        {
            os << "[ #" << &exception << " ] " << exception.title << " - " << exception.description;
            return os;
        }
    };
}

#endif