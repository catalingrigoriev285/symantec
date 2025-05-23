#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>

#include "../model.h"

namespace app::models::signature
{
    enum class HashAlgorithm
    {
        SHA1 = 0,   // Deprecated due to collision vulnerabilities. Still used in legacy systems.
        SHA224 = 1, // Truncated version of SHA-256.
        SHA256 = 2, // Widely used and recommended for most applications.
        SHA384 = 3, // Stronger than SHA-256; slower.
        SHA512 = 4, // Very strong, but uses more resources.
    };

    inline const char *HashAlgorithm_to_string(HashAlgorithm algorithm)
    {
        switch (algorithm)
        {
        case HashAlgorithm::SHA1:
            return "SHA1";
        case HashAlgorithm::SHA224:
            return "SHA224";
        case HashAlgorithm::SHA256:
            return "SHA256";
        case HashAlgorithm::SHA384:
            return "SHA384";
        case HashAlgorithm::SHA512:
            return "SHA512";
        default:
            return "Unknown";
        }
    }

    class Signature : public app::models::Model
    {
    private:
        int id;
        std::string name;
        std::string description;
        std::string value;
        HashAlgorithm algorithm;
        std::vector<unsigned char> hash;

        std::time_t created_at;
        std::time_t updated_at;

    public:
        Signature() : Model("signatures"), value(""), algorithm(HashAlgorithm::SHA256), hash({}), created_at(std::time(nullptr)), updated_at(std::time(nullptr)) {}

        Signature(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm);

        std::string getName() const { return name; }
        std::string getDescription() const { return description; }
        std::string getValue() const { return value; }
        HashAlgorithm getAlgorithm() const { return algorithm; }
        std::string getAlgorithmString() const
        {
            switch (algorithm)
            {
            case HashAlgorithm::SHA1:
                return "SHA1";
            case HashAlgorithm::SHA224:
                return "SHA224";
            case HashAlgorithm::SHA256:
                return "SHA256";
            case HashAlgorithm::SHA384:
                return "SHA384";
            case HashAlgorithm::SHA512:
                return "SHA512";
            default:
                return "Unknown";
            }
        }
        std::vector<unsigned char> getHash() const { return hash; }
        std::string getHashString() const
        {
            std::ostringstream oss;
            for (const auto &byte : hash)
            {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            return oss.str();
        }
        std::time_t getCreatedAt() const { return created_at; }
        std::time_t getUpdatedAt() const { return updated_at; }

        friend std::ostream &operator<<(std::ostream &os, const Signature &signature)
        {
            os << "Hash: ";
            for (const auto &byte : signature.hash)
            {
                os << std::hex << static_cast<int>(byte);
            }
            os << "\n"
               << "Hash Algorithm: " << static_cast<int>(signature.algorithm) << "\n"
               << "Created At: " << std::ctime(&signature.created_at)
               << "Updated At: " << std::ctime(&signature.updated_at);
            return os;
        };

        ~Signature() = default;

        std::vector<std::pair<std::string, std::string>> loadQueries() const
        {
            std::vector<std::pair<std::string, std::string>> queries;
            std::string queriesPath = std::filesystem::path(__FILE__).parent_path().string() + "/queries";

            try
            {
                for (const auto &entry : std::filesystem::directory_iterator(queriesPath))
                {
                    if (entry.is_regular_file() && entry.path().extension() == ".sql")
                    {
                        std::ifstream file(entry.path());
                        if (file.is_open())
                        {
                            std::ostringstream content;
                            content << file.rdbuf();
                            queries.emplace_back(entry.path().stem().string(), content.str());
                        }
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading queries: " << e.what() << "\n";
            }

            return queries;
        }
    };
}

#endif