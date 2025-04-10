#include "../../../include/core/scanner/signature_scanner.h"

namespace scanner
{
    SignatureScanner::SignatureScanner() {}
    SignatureScanner::~SignatureScanner() {}

    std::vector<unsigned char> SignatureScanner::getFileHash(const std::string &filePath, HashAlgorithm algorithm = HashAlgorithm::SHA256)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return {};
        }

        size_t digestLength;
        switch (algorithm)
        {
        case HashAlgorithm::SHA1:
            digestLength = SHA_DIGEST_LENGTH;
            break;
        case HashAlgorithm::SHA224:
            digestLength = SHA224_DIGEST_LENGTH;
            break;
        case HashAlgorithm::SHA256:
            digestLength = SHA256_DIGEST_LENGTH;
            break;
        case HashAlgorithm::SHA384:
            digestLength = SHA384_DIGEST_LENGTH;
            break;
        case HashAlgorithm::SHA512:
            digestLength = SHA512_DIGEST_LENGTH;
            break;
        default:
            throw std::invalid_argument("Unsupported hash algorithm");
        }

        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        switch (algorithm)
        {
        case HashAlgorithm::SHA1:
        {
            SHA_CTX sha1;
            if (!SHA1_Init(&sha1))
                throw std::runtime_error("SHA1_Init failed");
            while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
            {
                if (!SHA1_Update(&sha1, buffer.data(), file.gcount()))
                    throw std::runtime_error("SHA1_Update failed");
            }
            if (!SHA1_Final(hashData, &sha1))
                throw std::runtime_error("SHA1_Final failed");
            break;
        }
        case HashAlgorithm::SHA224:
        {
            SHA256_CTX sha224;
            if (!SHA224_Init(&sha224))
                throw std::runtime_error("SHA224_Init failed");
            while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
            {
                if (!SHA224_Update(&sha224, buffer.data(), file.gcount()))
                    throw std::runtime_error("SHA224_Update failed");
            }
            if (!SHA224_Final(hashData, &sha224))
                throw std::runtime_error("SHA224_Final failed");
            break;
        }
        case HashAlgorithm::SHA256:
        {
            SHA256_CTX sha256;
            if (!SHA256_Init(&sha256))
                throw std::runtime_error("SHA256_Init failed");
            while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
            {
                if (!SHA256_Update(&sha256, buffer.data(), file.gcount()))
                    throw std::runtime_error("SHA256_Update failed");
            }
            if (!SHA256_Final(hashData, &sha256))
                throw std::runtime_error("SHA256_Final failed");
            break;
        }
        case HashAlgorithm::SHA384:
        {
            SHA512_CTX sha384;
            if (!SHA384_Init(&sha384))
                throw std::runtime_error("SHA384_Init failed");
            while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
            {
                if (!SHA384_Update(&sha384, buffer.data(), file.gcount()))
                    throw std::runtime_error("SHA384_Update failed");
            }
            if (!SHA384_Final(hashData, &sha384))
                throw std::runtime_error("SHA384_Final failed");
            break;
        }
        case HashAlgorithm::SHA512:
        {
            SHA512_CTX sha512;
            if (!SHA512_Init(&sha512))
                throw std::runtime_error("SHA512_Init failed");
            while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
            {
                if (!SHA512_Update(&sha512, buffer.data(), file.gcount()))
                    throw std::runtime_error("SHA512_Update failed");
            }
            if (!SHA512_Final(hashData, &sha512))
                throw std::runtime_error("SHA512_Final failed");
            break;
        }
        }

        return hash;
    }
}