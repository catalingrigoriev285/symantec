#include "configuration_init.h"

namespace Scripts {
    bool verifyConfiguration(){
        if(!verify_env_file_exists()) return false;
        return true;
    }

    void initConfiguration(){
        if(!verify_env_file_exists()){
            Models::Log log(Models::LogType::INFO, "Configuration Init", "Configuration file not found. Generating...");
            std::cout << log << std::endl;
            generate_dot_env();
            log.setParameters(Models::LogType::INFO, "Configuration Init", "Configuration file generated.");
            std::cout << log << std::endl;
        } else {
            Models::Log log(Models::LogType::INFO, "Configuration Init", "Configuration file found.");
            std::cout << log << std::endl;
        }
    }
}