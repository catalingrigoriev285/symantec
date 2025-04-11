#include "../../../include/models/exception/exception.h"

namespace Models
{
    void Exception::setParameters(const std::string &title, const std::string &description)
    {
        this->title = title;
        this->description = description;
    }
}