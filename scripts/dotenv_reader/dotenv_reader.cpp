#include "dotenv_reader.h"

namespace Scripts
{
    std::vector<DotenvEntry> read_dotenv_file(const std::string &filePath = ".env")
    {
        std::ifstream file(filePath);
        std::vector<DotenvEntry> entries;

        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            return entries;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (!line.empty() && line[0] != '#')
            {
                size_t delimiterPos = line.find('=');
                if (delimiterPos != std::string::npos)
                {
                    std::string key = line.substr(0, delimiterPos);
                    std::string value = line.substr(delimiterPos + 1);
                    entries.push_back({key, value});
                }
            }
        }

        file.close();
        return entries;
    }

    std::vector<std::pair<std::string, std::string>> read_dotenv_key(const std::string &filePath, const std::string &key)
    {
        auto entries = read_dotenv_file(filePath);
        std::vector<std::pair<std::string, std::string>> result;

        for (const auto &entry : entries)
        {
            if (entry.key == key)
            {
                result.emplace_back(entry.key, entry.value);
            }
        }

        return result;
    }
}