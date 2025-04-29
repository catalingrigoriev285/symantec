#ifndef DOTENV_READER_H
#define DOTENV_READER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace Scripts {
    struct DotenvEntry {
        std::string key;
        std::string value;
    };

    std::vector<DotenvEntry> read_dotenv_file(const std::string &filePath);
    std::vector<std::pair<std::string, std::string>> read_dotenv_key(const std::string &filePath, const std::string &key);
}

#endif