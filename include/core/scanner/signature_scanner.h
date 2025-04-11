#ifndef SIGNATURE_SCANNER_H
#define SIGNATURE_SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>

#include <openssl/sha.h>

namespace Scanner
{
    enum class HashAlgorithm
    {
        SHA1,   // Deprecated due to collision vulnerabilities. Still used in legacy systems.
        SHA224, // Truncated version of SHA-256.
        SHA256, // Widely used and recommended for most applications.
        SHA384, // Stronger than SHA-256; slower.
        SHA512, // Very strong, but uses more resources.
    };

    class Signature
    {
    public:
        std::string name;
        std::string description;
        std::vector<unsigned char> hash;
        HashAlgorithm algorithm;
        std::time_t created_at;
        std::time_t updated_at;

    public:
        Signature() = default;
        Signature(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm);
        virtual ~Signature();
    };

    class SignatureScanner : public Signature
    {
    public:
        SignatureScanner();
        SignatureScanner(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm);
        ~SignatureScanner() override;

        Signature getFileSignatureSHA1(const std::string &filePath);
        Signature getFileSignatureSHA224(const std::string &filePath);
        Signature getFileSignatureSHA256(const std::string &filePath);
        Signature getFileSignatureSHA384(const std::string &filePath);
        Signature getFileSignatureSHA512(const std::string &filePath);
        
        friend std::ostream &operator<<(std::ostream &os, const Signature &signature)
        {
            os << "Signature Name: " << signature.name << "\n"
               << "Description: " << signature.description << "\n"
               << "Hash: ";
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
    };
};

#endif