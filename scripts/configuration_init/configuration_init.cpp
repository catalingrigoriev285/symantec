#include "configuration_init.h"
#include <filesystem>

namespace Scripts {
    bool verifyConfiguration(){
        if(verify_env_file_exists()) return false;
        return true;
    }

    void initConfiguration(){
        if (!std::ifstream("config.ini").good()) {
            Models::Log log(Models::LogType::INFO, "Configuration Init", "Configuration file not found. Generating...");
            std::cout << log << std::endl;

            std::ofstream configFile("config.ini");
            if (configFile.is_open()) {
                configFile << "[Database]" << std::endl;
                configFile << "DB_CONNECTION=SQLite" << std::endl;
                configFile << "DB_HOST=127.0.0.1" << std::endl;
                configFile << "DB_PORT=3306" << std::endl;
                configFile << "DB_DATABASE=database.sqlite" << std::endl;
                configFile << "DB_USERNAME=root" << std::endl;
                configFile << "DB_PASSWORD=password" << std::endl;
                configFile.close();
            } else {
                Models::Log errorLog(Models::LogType::ERROR, "Configuration Init", "Failed to create configuration file.");
                std::cout << errorLog << std::endl;
            }

            log.setParameters(Models::LogType::INFO, "Configuration Init", "Configuration file generated.");
            std::cout << log << std::endl;
        } else {
            Models::Log log(Models::LogType::INFO, "Configuration Init", "Configuration file found.");
            std::cout << log << std::endl;
        }
    }

    void cleanConfiguration(){
        if (std::filesystem::exists("config.ini")) {
            std::filesystem::remove("config.ini");
            Models::Log log(Models::LogType::INFO, "Configuration Clean", "Configuration file removed.");
            std::cout << log << std::endl;
        } else {
            Models::Log log(Models::LogType::INFO, "Configuration Clean", "No configuration file found to remove.");
            std::cout << log << std::endl;
        }
    }
}