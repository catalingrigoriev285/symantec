#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>

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

    class Signature
    {
    private:
        std::string value;
        HashAlgorithm algorithm;
        std::vector<unsigned char> hash;

        std::time_t created_at;
        std::time_t updated_at;

    public:
        Signature() = default;

        Signature(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm);

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
    };
}

#endif