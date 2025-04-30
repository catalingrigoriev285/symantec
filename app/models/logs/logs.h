#ifndef LOGS_H
#define LOGS_H

#include <iostream>
#include <string>
#include <ctime>
#include <filesystem>

#include "../model.h"

#include "../../modules/configuration/configuration.h"

namespace app::models::logs
{
    enum enum_log_type
    {
        INFO = 0,
        WARNING = 1,
        ERROR = 2,
        DEBUG = 3,
    };

    class Logs : public app::models::Model
    {
    private:
        std::string title;
        std::string description;
        enum_log_type type;

        std::time_t created_at;
        std::time_t updated_at;

    public:
        Logs(std::string title, std::string description, enum_log_type type);

        ~Logs();

        void display() const;

        friend std::ostream &operator<<(std::ostream &os, const Logs &log)
        {
            os << "[" << &log << "](" << std::put_time(std::localtime(&log.created_at), "%Y-%m-%d %H:%M:%S") << ") " << log.title << ": " << log.description;
            return os;
        }
    };
}

#endif