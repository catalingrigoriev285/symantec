#include "configuration.h"
#include <filesystem>
#include <iostream>

namespace app::modules::configuration
{
    Configuration::Configuration(std::string file_path)
        : file_path(file_path),
          app_name("Symantec"),
          app_version(1.0),
          app_author("Catalin Grigoriev"),
          log_level("debug"),
          log_enabled(true),
          log_write_to_file(true),
          log_file_path("symantec.log"),
          log_file_max_size(1048576),
          log_file_max_backups(3),
          log_file_compress(false),
          db_connection("sqlite"),
          db_path("database"),
          db_file("symantec.db"),
          db_host("localhost"),
          db_port(3306),
          db_database("symantec"),
          db_user("root"),
          db_password("password")
    {
        if (std::filesystem::exists(file_path))
        {
            
        }
        else
        {
            std::cerr << "Configuration file not found: " << file_path << "\n";
        }
    }

    bool Configuration::exists()
    {
        std::ifstream file(file_path);
        return file.good();
    }

    std::vector<std::pair<std::string, std::string>> Configuration::read()
    {
        std::vector<std::pair<std::string, std::string>> key_value_pairs;
        std::ifstream file(file_path);

        if (file)
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (line.empty() || line.front() == '[' || line.front() == '#')
                {
                    continue;
                }

                auto delimiter_pos = line.find('=');
                if (delimiter_pos != std::string::npos)
                {
                    std::string key = line.substr(0, delimiter_pos);
                    std::string value = line.substr(delimiter_pos + 1);

                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);

                    key_value_pairs.emplace_back(key, value);
                }
            }
        }

        return key_value_pairs;
    }

    std::pair<std::string, std::string> Configuration::get(std::string key)
    {
        auto key_value_pairs = read();

        for (const auto &pair : key_value_pairs)
        {
            if (pair.first == key)
            {
                return pair;
            }
        }

        return {"", ""};
    }

    void Configuration::set(std::string key, std::string value)
    {
        if (key == "app_name")
            app_name = value;
        else if (key == "app_author")
            app_author = value;
        else if (key == "app_version")
            app_version = std::stod(value);
        else if (key == "log_level")
            log_level = value;
        else if (key == "log_enabled")
            log_enabled = (value == "true");
        else if (key == "log_write_to_file")
            log_write_to_file = (value == "true");
        else if (key == "log_file_path")
            log_file_path = value;
        else if (key == "log_file_max_size")
            log_file_max_size = std::stoul(value);
        else if (key == "log_file_max_backups")
            log_file_max_backups = std::stoi(value);
        else if (key == "log_file_compress")
            log_file_compress = (value == "true");
        else if (key == "db_connection")
            db_connection = value;
        else if (key == "db_host")
            db_host = value;
        else if (key == "db_port")
            db_port = std::stoi(value);
        else if (key == "db_database")
            db_database = value;
        else if (key == "db_user")
            db_user = value;
        else if (key == "db_password")
            db_password = value;

        save();
    }

    void Configuration::save()
    {
        std::ofstream file(file_path, std::ios::trunc);
        if (file)
        {
            file << "[Application]\n"
                 << "app_name=" << app_name << "\n"
                 << "app_author=" << app_author << "\n"
                 << "app_version=" << app_version << "\n\n"
                 << "[Logging]\n"
                 << "log_level=" << log_level << "\n"
                 << "log_enabled=" << (log_enabled ? "true" : "false") << "\n"
                 << "log_write_to_file=" << (log_write_to_file ? "true" : "false") << "\n"
                 << "log_file_path=" << log_file_path << "\n"
                 << "log_file_max_size=" << log_file_max_size << "\n"
                 << "log_file_max_backups=" << log_file_max_backups << "\n"
                 << "log_file_compress=" << (log_file_compress ? "true" : "false") << "\n\n"
                 << "[Database]\n"
                 << "db_connection=" << db_connection << "\n"
                 << "db_host=" << db_host << "\n"
                 << "db_port=" << db_port << "\n"
                 << "db_database=" << db_database << "\n"
                 << "db_user=" << db_user << "\n"
                 << "db_password=" << db_password << "\n";
        }
    }

    Configuration::~Configuration() {}
}