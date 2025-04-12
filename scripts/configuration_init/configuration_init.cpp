#include "configuration_init.h"
#include <filesystem>

namespace Scripts {
    bool verifyConfiguration(){
        if(verify_env_file_exists()) return false;
        return true;
    }

    void initConfiguration(Database::Database &db){
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
            std::ifstream configFile("config.ini");
            if (configFile.is_open()) {
                std::string line;
                while (std::getline(configFile, line)) {
                    if (line.find("DB_CONNECTION=") == 0) {
                        db.setConnectionType(line.substr(14));
                    } else if (line.find("DB_HOST=") == 0) {
                        db.setHost(line.substr(8));
                    } else if (line.find("DB_PORT=") == 0) {
                        db.setPort(std::stoi(line.substr(8)));
                    } else if (line.find("DB_DATABASE=") == 0) {
                        db.setDatabaseName(line.substr(12));
                    } else if (line.find("DB_USERNAME=") == 0) {
                        db.setUsername(line.substr(12));
                    } else if (line.find("DB_PASSWORD=") == 0) {
                        db.setPassword(line.substr(12));
                    }
                }
                configFile.close();
            }
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