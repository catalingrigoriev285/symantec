#include "../../../include/core/engine/engine_interface.h"

namespace Engine
{
    EngineInterface::~EngineInterface(){}

    bool EngineInterface::initialize()
    {
        return true;
    }

    bool EngineInterface::scan(const std::string &directory_path)
    {
        const std::string random_signature = "RANDOM_SIGNATURE";

        if (std::filesystem::exists(directory_path))
        {
            if (std::filesystem::is_directory(directory_path))
            {
                Signature signature_scanner;
                EngineReport report;

                for (const auto &entry : std::filesystem::directory_iterator(directory_path))
                {
                    std::cout << "Scanning file: " << entry.path() << std::endl;
                    std::cout << "Signature: " << signature_scanner.getFileSignatureSHA256(entry.path().string()) << std::endl;
                }
                return true;
            }
            else
            {
                std::cerr << "Path is not a directory: " << directory_path << std::endl;
            }
        }
        else
        {
            std::cerr << "Directory does not exist: " << directory_path << std::endl;
        }

        return false;
    }
}