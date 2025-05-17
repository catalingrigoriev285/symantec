#include "database.h"

namespace app::modules::database
{
    Database::Database(connection_enum_type connection, std::string host, int port, std::string database, std::string user, std::string password)
        : db_connection(connection), db_host(host), db_port(port), db_database(database), db_user(user), db_password(password)
    {

        switch (db_connection)
        {
        case connection_enum_type::SQLITE:
            // SQLite connection
            break;
        case connection_enum_type::MYSQL:
            // MySQL connection
            break;
        case connection_enum_type::POSTGRESQL:
            // PostgreSQL connection
            break;
        case connection_enum_type::MONGODB:
            // MongoDB connection
            break;
        case connection_enum_type::REDIS:
            // Redis connection
            break;
        case connection_enum_type::ORACLE:
            // Oracle connection
            break;
        default:
            app::models::logs::Logs log("Database", "Invalid database connection type", app::models::logs::enum_log_type::ERROR);
        }
    }

    void Database::set_connection(connection_enum_type connection)
    {
        this->db_connection = connection;
    }

    void Database::set_path(std::string path)
    {
        this->db_path = path;
    }

    void Database::set_file(std::string file)
    {
        this->db_file = file;
    }

    void Database::set_host(std::string host)
    {
        this->db_host = host;
    }

    void Database::set_port(int port)
    {
        this->db_port = port;
    }

    void Database::set_database(std::string database)
    {
        this->db_database = database;
    }

    void Database::set_user(std::string user)
    {
        this->db_user = user;
    }

    void Database::set_password(std::string password)
    {
        this->db_password = password;
    }

    connection_enum_type Database::get_connection()
    {
        return this->db_connection;
    }

    std::string Database::get_path()
    {
        return this->db_path;
    }

    std::string Database::get_file()
    {
        return this->db_file;
    }

    std::string Database::get_host()
    {
        return this->db_host;
    }

    int Database::get_port()
    {
        return this->db_port;
    }

    std::string Database::get_database()
    {
        return this->db_database;
    }

    std::string Database::get_user()
    {
        return this->db_user;
    }

    std::string Database::get_password()
    {
        return this->db_password;
    }
}