#ifndef SIGNATURE_SCANNER
#define SIGNATURE_SCANNER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>

#include <openssl/sha.h>

#include "../../../models/signature/signature.h"

namespace app::core::scanner::signature_scanner {
    class SignatureScanner : public app::models::signature::Signature {
    private:
        std::string path;
        app::models::signature::HashAlgorithm algorithm;
        std::vector<unsigned char> hash;
    public:
        SignatureScanner() = default;
        SignatureScanner(std::string path, app::models::signature::HashAlgorithm algorithm);

        Signature scanFile(const std::string& filePath, const app::models::signature::HashAlgorithm& algorithm);

        Signature getFileSignatureSHA1(const std::string &filePath);
        Signature getFileSignatureSHA224(const std::string &filePath);
        Signature getFileSignatureSHA256(const std::string &filePath);
        Signature getFileSignatureSHA384(const std::string &filePath);
        Signature getFileSignatureSHA512(const std::string &filePath);

        ~SignatureScanner() = default;
    };
}

#endif