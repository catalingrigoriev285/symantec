#ifndef SIGNATURE_SCANNER_H
#define SIGNATURE_SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>

#include <openssl/sha.h>

namespace scanner
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
    private:
        std::string name;
        std::string description;
        std::vector<unsigned char> hash;
        HashAlgorithm algorithm;
        std::time_t created_at;
        std::time_t updated_at;

    public:
        Signature(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm);
        virtual ~Signature();
    };

    class SignatureScanner : public Signature
    {
    public:
        SignatureScanner();
        SignatureScanner(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm);
        ~SignatureScanner() override;

        std::vector<unsigned char> getFileSignatureSHA1(const std::string &filePath);
        std::vector<unsigned char> getFileSignatureSHA224(const std::string &filePath);
        std::vector<unsigned char> getFileSignatureSHA256(const std::string &filePath);
        std::vector<unsigned char> getFileSignatureSHA384(const std::string &filePath);
        std::vector<unsigned char> getFileSignatureSHA512(const std::string &filePath);
    };
};

#endif