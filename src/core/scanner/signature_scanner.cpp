#include "../../../include/core/scanner/signature_scanner.h"

namespace scanner
{
    SignatureScanner::SignatureScanner() {}
    SignatureScanner::~SignatureScanner() {}

    std::vector<unsigned char> SignatureScanner::getFileHash(const std::string &filePath, HashAlgorithm algorithm = HashAlgorithm::SHA256)
    {
        std::vector<unsigned char> hash;

        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filePath << "\n";
            return {};
        }

        switch (algorithm)
        {
        case HashAlgorithm::SHA1:
            hash.resize(SHA_DIGEST_LENGTH);
            {
                SHA_CTX sha1;
                SHA1_Init(&sha1);

                std::vector<char> buffer(8192);
                while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
                {
                    SHA1_Update(&sha1, buffer.data(), file.gcount());
                }

                SHA1_Final(hash.data(), &sha1);
            }
            break;

        case HashAlgorithm::SHA256:
            hash.resize(SHA256_DIGEST_LENGTH);
            {
                SHA256_CTX sha256;
                SHA256_Init(&sha256);

                std::vector<char> buffer(8192);
                while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
                {
                    SHA256_Update(&sha256, buffer.data(), file.gcount());
                }

                SHA256_Final(hash.data(), &sha256);
            }
            break;
        case HashAlgorithm::SHA512:
            hash.resize(SHA512_DIGEST_LENGTH);
            {
                SHA512_CTX sha512;
                SHA512_Init(&sha512);

                std::vector<char> buffer(8192);
                while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
                {
                    SHA512_Update(&sha512, buffer.data(), file.gcount());
                }

                SHA512_Final(hash.data(), &sha512);
            }
            break;
        }

        return hash;
    }
}