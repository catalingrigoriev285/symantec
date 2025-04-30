#include "logs.h"

namespace app::models::logs
{
    Logs::Logs(std::string title, std::string description, enum_log_type type) : Model("logs")
    {
        this->title = title;
        this->description = description;
        this->type = type;

        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        this->created_at = now_time_t;
        this->updated_at = now_time_t;

        app::modules::configuration::Configuration config("symantec.ini");
        if (config.exists() && config.get("log_write_to_file").second == "true")
        {
            std::filesystem::path log_folder = "logs";
            if (!std::filesystem::exists(log_folder))
            {
                std::filesystem::create_directory(log_folder);
            }

            std::filesystem::path log_file = log_folder / config.get("log_file_path").second;

            std::ofstream file(log_file, std::ios::app);
            if (file.is_open())
            {
                file << "[" << &this->created_at << "](" << std::put_time(std::localtime(&this->created_at), "%Y-%m-%d %H:%M:%S") << ") " << this->title << ": " << this->description << "\n";
                file.close();
            }
            else
            {
                std::cerr << "Unable to open log file: " << log_file << std::endl;
            }
        }
    }

    void Logs::display() const
    {
        app::modules::configuration::Configuration config("symantec.ini");

        if (config.exists() && config.get("log_enabled").second == "true")
        {
            std::cout << "Title: " << title << "\n"
                      << "Description: " << description << "\n"
                      << "Type: " << (type == INFO ? "INFO" : type == WARNING ? "WARNING"
                                                          : type == ERROR     ? "ERROR"
                                                                              : "DEBUG")
                      << "\n"
                      << "Created At: " << std::put_time(std::localtime(&created_at), "%Y-%m-%d %H:%M:%S") << "\n"
                      << "Updated At: " << std::put_time(std::localtime(&updated_at), "%Y-%m-%d %H:%M:%S") << std::endl;
        }
    }

    Logs::~Logs() {}
}