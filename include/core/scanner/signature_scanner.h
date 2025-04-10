#ifndef SIGNATURE_SCANNER_H
#define SIGNATURE_SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <openssl/sha.h>

namespace scanner {
    class SignatureScanner {
        public:
            SignatureScanner();
            ~SignatureScanner();

            std::vector<unsigned char> getFileSHA256(const std::string& filePath);
    };
};

#endif