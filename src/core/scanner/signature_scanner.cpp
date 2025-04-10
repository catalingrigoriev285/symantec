#include "../../../include/core/scanner/signature_scanner.h"

namespace scanner {
    SignatureScanner::SignatureScanner() {}
    SignatureScanner::~SignatureScanner() {}

    std::vector<unsigned char> SignatureScanner::getFileSHA256(const std::string& filePath) {
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return {};
    }

    std::vector<char> buffer(8192);
    while (file.good()) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = file.gcount();
        if (bytesRead > 0) {
            SHA256_Update(&sha256, buffer.data(), bytesRead);
        }
    }

    SHA256_Final(hash.data(), &sha256);
    return hash;
}
}