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

            void setConnectionType(const std::string& type) {
                if (type == "Raw") {
                    db_type = DatabaseType::Raw;
                } else if (type == "SQLite") {
                    db_type = DatabaseType::SQLite;
                } else {
                    std::cerr << "Invalid database type: " << type << std::endl;
                }
            }

            void setHost(const std::string& host) {
                db_host = host;
            }

            void setDatabaseName(const std::string& name) {
                db_name = name;
            }

            void setUsername(const std::string& user) {
                db_user = user;
            }

            void setPassword(const std::string& password) {
                db_password = password;
            }

            void setPort(int port) {
                db_port = port;
            }

            std::string getHost() const {
                return db_host;
            }

            std::string getDatabaseName() const {
                return db_name;
            }

            std::string getUsername() const {
                return db_user;
            }

            std::string getPassword() const {
                return db_password;
            }

            int getPort() const {
                return db_port;
            }

            DatabaseType getDatabaseType() const {
                return db_type;
            }

            std::string getPath() const {
                return db_path;
            }

            void setParameters(const std::string& host, const std::string& name, const std::string& user, const std::string& password, int port, DatabaseType type, const std::string& path) {
                db_host = host;
                db_name = name;
                db_user = user;
                db_password = password;
                db_port = port;
                db_type = type;
                db_path = path;
            }

            void verifyConnection();
            void createDatabase();

            friend std::ostream& operator << (std::ostream& os, const Database& db) {
                os << "Database Type: " << (db.db_type == DatabaseType::Raw ? "Raw" : "SQLite") << std::endl;
                os << "Host: " << db.db_host << std::endl;
                os << "Name: " << db.db_name << std::endl;
                os << "User: " << db.db_user << std::endl;
                os << "Password: " << db.db_password << std::endl;
                os << "Port: " << db.db_port << std::endl;
                return os;
            }
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