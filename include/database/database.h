#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <SQLiteCpp/SQLiteCpp.h>

#include "../../scripts/dotenv_generate/dotenv_generate.h"

namespace Database {
    enum class DatabaseType {
        Raw,
        SQLite,
    };

    class Database {
        private:
            std::string db_host;
            std::string db_name;
            std::string db_user;
            std::string db_password;
            int db_port;

        public:
            std::string db_path;

            DatabaseType db_type;

            Database();
            Database(const std::string& host, const std::string& name, const std::string& user, const std::string& password, int port, DatabaseType type, const std::string& path)
                : db_host(host), db_name(name), db_user(user), db_password(password), db_port(port), db_type(type), db_path(path) {};

            ~Database();

            void verifyConnection();
            void createDatabase();
    };

    class RawDatabase : public Database {
        public:
            RawDatabase() : Database("localhost", "test.db", "user", "password", 0, DatabaseType::Raw, nullptr){};
            RawDatabase(const std::string& host, const std::string& name, const std::string& user, const std::string& password, int port, DatabaseType type, const std::string& path)
                : Database(host, name, user, password, port, type, path) {};
            ~RawDatabase();

            void verifyConnection();
            void createDatabase();
    };

    class SQLiteDatabase : public Database {
        public:
            SQLiteDatabase() : Database("localhost", "test.db", "user", "password", 0, DatabaseType::SQLite, nullptr){};
            SQLiteDatabase(const std::string& host, const std::string& name, const std::string& user, const std::string& password, int port, DatabaseType type, const std::string& path)
                : Database(host, name, user, password, port, type, path) {};
            ~SQLiteDatabase();

            void verifyConnection();
            void createDatabase();
    };
}

#endif