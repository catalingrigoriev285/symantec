#include <iostream>

#include "include/core/scanner/signature_scanner.h"

int main(){
    scanner::SignatureScanner scanner;
    std::string filePath = "example.txt";
    std::vector<unsigned char> hash = scanner.getFileHash(filePath, scanner::HashAlgorithm::SHA512);
    if (!hash.empty()) {
        std::cout << "SHA512 hash of the file: ";
        for (unsigned char byte : hash) {
            printf("%02x", byte);
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Failed to compute SHA512 hash." << std::endl;
    }

    getchar();
    return 0;
}