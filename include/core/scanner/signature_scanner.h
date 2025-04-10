#ifndef SIGNATURE_SCANNER_H
#define SIGNATURE_SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include <openssl/sha.h>

namespace scanner
{
    enum class HashAlgorithm
    {
        SHA1, // Deprecated due to collision vulnerabilities. Still used in legacy systems.
        SHA224, // Truncated version of SHA-256.
        SHA256, // Widely used and recommended for most applications.
        SHA384, // Stronger than SHA-256; slower.
        SHA512, // Very strong, but uses more resources.
    };

    class SignatureScanner
    {
    public:
        SignatureScanner();
        ~SignatureScanner();

        std::vector<unsigned char> getFileHash(const std::string &filePath, HashAlgorithm algorithm);
    };
};

#endif