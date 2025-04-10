#ifndef SIGNATURE_SCANNER_H
#define SIGNATURE_SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <openssl/sha.h>

namespace scanner
{
    enum class HashAlgorithm
    {
        SHA1,
        SHA256,
        SHA512,
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