#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include "../../models/logs/logs.h"

namespace app::modules::database
{
    enum class connection_enum_type
    {
        SQLITE, // the only working one and default
        // for future implementation
        MYSQL,
        POSTGRESQL,
        MONGODB,
        REDIS,
        ORACLE,
    };

    class Database
    {
    private:
        connection_enum_type db_connection;

        std::string db_path;
        std::string db_file;

        std::string db_host;
        int db_port;
        std::string db_database;
        std::string db_user;
        std::string db_password;

    public:
        Database(connection_enum_type connection = connection_enum_type::SQLITE, std::string host = "127.0.0.1", int port = 3306, std::string database = "symantec", std::string user = "root", std::string password = "password");
        ~Database() {};

        void set_connection(connection_enum_type connection);
        void set_path(std::string path);
        void set_file(std::string file);
        void set_host(std::string host);
        void set_port(int port);
        void set_database(std::string database);
        void set_user(std::string user);
        void set_password(std::string password);

        connection_enum_type get_connection();
        std::string get_path();
        std::string get_file();
        std::string get_host();
        int get_port();
        std::string get_database();
        std::string get_user();
        std::string get_password();
    };
}

#endif