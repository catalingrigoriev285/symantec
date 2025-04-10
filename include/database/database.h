#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>

namespace Database {
    enum class DatabaseType {
        SQLITE,
    };

    class Database {
        private:
            std::string db_host;
            std::string db_name;
            std::string db_user;
            std::string db_password;
            int db_port;

            DatabaseType db_type;

        public:
            Database();
            Database(const std::string& host, const std::string& name, const std::string& user, const std::string& password, int port, DatabaseType type)
                : db_host(host), db_name(name), db_user(user), db_password(password), db_port(port), db_type(type){};

            ~Database();
    };
}

#endif