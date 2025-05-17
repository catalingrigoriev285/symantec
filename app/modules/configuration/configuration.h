#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace app::modules::configuration
{

    class Configuration
    {
    private:
        // Application configuration
        std::string file_path;

        std::string app_name;
        float app_version;
        std::string app_author;

        // Logging configuration
        std::string log_level;
        bool log_enabled;
        bool log_write_to_file;
        std::string log_file_path;
        int log_file_max_size;
        int log_file_max_backups;
        bool log_file_compress;

        // Database configuration
        std::string db_connection;
        std::string db_path;
        std::string db_file;
        std::string db_host;
        int db_port;
        std::string db_database;
        std::string db_user;
        std::string db_password;

    public:
        Configuration(std::string file_path);
        ~Configuration();

        bool exists();
        
        std::vector<std::pair<std::string, std::string>> read();
        std::pair<std::string, std::string> get(std::string key);
        void set(std::string key, std::string value);
        void save();
    };
}

#endif