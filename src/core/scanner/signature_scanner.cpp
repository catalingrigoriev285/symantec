#include "../../../include/core/scanner/signature_scanner.h"

namespace scanner
{
    Signature::Signature(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm)
        : name(name), description(description), hash(hash), algorithm(algorithm), created_at(std::time(nullptr)), updated_at(std::time(nullptr)) {}

    Signature::~Signature() {}

    SignatureScanner::SignatureScanner() : Signature("", "", {}, HashAlgorithm::SHA256) {}
    SignatureScanner::SignatureScanner(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm)
        : Signature(name, description, hash, algorithm) {}
    SignatureScanner::~SignatureScanner() {}

    Signature SignatureScanner::getFileSignatureSHA1(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return Signature("SHA1", "Failed to compute SHA1", {}, HashAlgorithm::SHA1);
        }

        size_t digestLength = SHA_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA_CTX sha1;
        if (!SHA1_Init(&sha1))
        {
            throw std::runtime_error("SHA1_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA1_Update(&sha1, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA1_Update failed");
            }
        }

        if (!SHA1_Final(hashData, &sha1))
        {
            throw std::runtime_error("SHA1_Final failed");
        }

        return Signature("SHA1", "SHA1 file signature", hash, HashAlgorithm::SHA1);
    }

    Signature SignatureScanner::getFileSignatureSHA224(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return Signature("SHA224", "Failed to compute SHA224", {}, HashAlgorithm::SHA224);
        }

        size_t digestLength = SHA224_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA256_CTX sha224;
        if (!SHA224_Init(&sha224))
        {
            throw std::runtime_error("SHA224_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA224_Update(&sha224, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA224_Update failed");
            }
        }

        if (!SHA224_Final(hashData, &sha224))
        {
            throw std::runtime_error("SHA224_Final failed");
        }

        return Signature("SHA224", "SHA224 file signature", hash, HashAlgorithm::SHA224);
    }

    Signature SignatureScanner::getFileSignatureSHA256(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return Signature("SHA256", "Failed to compute SHA256", {}, HashAlgorithm::SHA256);
        }

        size_t digestLength = SHA256_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA256_CTX sha256;
        if (!SHA256_Init(&sha256))
        {
            throw std::runtime_error("SHA256_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA256_Update(&sha256, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA256_Update failed");
            }
        }

        if (!SHA256_Final(hashData, &sha256))
        {
            throw std::runtime_error("SHA256_Final failed");
        }

        return Signature("SHA256", "SHA256 file signature", hash, HashAlgorithm::SHA256);
    }

    Signature SignatureScanner::getFileSignatureSHA384(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return Signature("SHA384", "Failed to compute SHA384", {}, HashAlgorithm::SHA384);
        }

        size_t digestLength = SHA384_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA512_CTX sha384;
        if (!SHA384_Init(&sha384))
        {
            throw std::runtime_error("SHA384_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA384_Update(&sha384, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA384_Update failed");
            }
        }

        if (!SHA384_Final(hashData, &sha384))
        {
            throw std::runtime_error("SHA384_Final failed");
        }

        return Signature("SHA384", "SHA384 file signature", hash, HashAlgorithm::SHA384);
    }

    Signature SignatureScanner::getFileSignatureSHA512(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return Signature("SHA512", "Failed to compute SHA512", {}, HashAlgorithm::SHA512);
        }

        size_t digestLength = SHA512_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA512_CTX sha512;
        if (!SHA512_Init(&sha512))
        {
            throw std::runtime_error("SHA512_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA512_Update(&sha512, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA512_Update failed");
            }
        }

        if (!SHA512_Final(hashData, &sha512))
        {
            throw std::runtime_error("SHA512_Final failed");
        }

        return Signature("SHA512", "SHA512 file signature", hash, HashAlgorithm::SHA512);
    }
}