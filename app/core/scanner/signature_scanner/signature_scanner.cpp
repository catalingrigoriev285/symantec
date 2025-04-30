#include "signature_scanner.h"

namespace app::core::scanner::signature_scanner
{
    SignatureScanner::SignatureScanner(std::string path, app::models::signature::HashAlgorithm algorithm)
        : path(path), algorithm(algorithm) {}

    app::models::signature::Signature SignatureScanner::scanFile(const std::string &filePath, const app::models::signature::HashAlgorithm &algorithm)
    {
        switch (algorithm)
        {
        case app::models::signature::HashAlgorithm::SHA1:
            return getFileSignatureSHA1(filePath);
        case app::models::signature::HashAlgorithm::SHA224:
            return getFileSignatureSHA224(filePath);
        case app::models::signature::HashAlgorithm::SHA256:
            return getFileSignatureSHA256(filePath);
        case app::models::signature::HashAlgorithm::SHA384:
            return getFileSignatureSHA384(filePath);
        case app::models::signature::HashAlgorithm::SHA512:
            return getFileSignatureSHA512(filePath);
        default:
            throw std::invalid_argument("Unsupported hash algorithm");
        }
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA1(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return app::models::signature::Signature("SHA1", "Failed to compute SHA1", {}, app::models::signature::HashAlgorithm::SHA1);
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

        return app::models::signature::Signature("SHA1", "SHA1 file signature", hash, app::models::signature::HashAlgorithm::SHA1);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA224(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return app::models::signature::Signature("SHA224", "Failed to compute SHA224", {}, app::models::signature::HashAlgorithm::SHA224);
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

        return app::models::signature::Signature("SHA224", "SHA224 file signature", hash, app::models::signature::HashAlgorithm::SHA224);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA256(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return app::models::signature::Signature("SHA256", "Failed to compute SHA256", {}, app::models::signature::HashAlgorithm::SHA256);
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

        return app::models::signature::Signature("SHA256", "SHA256 file signature", hash, app::models::signature::HashAlgorithm::SHA256);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA384(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return app::models::signature::Signature("SHA384", "Failed to compute SHA384", {}, app::models::signature::HashAlgorithm::SHA384);
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

        return app::models::signature::Signature("SHA384", "SHA384 file signature", hash, app::models::signature::HashAlgorithm::SHA384);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA512(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return app::models::signature::Signature("SHA512", "Failed to compute SHA512", {}, app::models::signature::HashAlgorithm::SHA512);
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

        return app::models::signature::Signature("SHA512", "SHA512 file signature", hash, app::models::signature::HashAlgorithm::SHA512);
    }
}