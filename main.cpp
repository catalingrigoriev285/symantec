#include <iostream>
#include <string>
#include "include/core/scanner/signature_scanner.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -getFileSignature256 <filePath>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string filePath = argv[2];

    if (command == "-getFileSignature256") {
        scanner::SignatureScanner scanner;
        scanner::Signature signature = scanner.getFileSignatureSHA256(filePath);
        std::cout << "SHA256 Signature: " << signature << std::endl;
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}