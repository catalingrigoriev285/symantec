#include <iostream>

#include "include/core/scanner/signature_scanner.h"

int main(){
    scanner::SignatureScanner scanner;
    std::string filePath = "example.txt";
    std::vector<unsigned char> hash = scanner.getFileSHA256(filePath);
    if (!hash.empty()) {
        std::cout << "SHA256 hash of the file: ";
        for (unsigned char byte : hash) {
            printf("%02x", byte);
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Failed to compute SHA256 hash." << std::endl;
    }

    getchar();
    return 0;
}