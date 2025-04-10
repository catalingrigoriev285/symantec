#include <iostream>
#include <string>
#include "include/core/scanner/signature_scanner.h"

void printHelp(const std::string& programName) {
    std::cout << "Commands:" << std::endl;
    std::cout << "  -getFileSignature1\t<file>\tGet SHA1 signature of the file" << std::endl;
    std::cout << "  -getFileSignature224\t<file>\tGet SHA224 signature of the file" << std::endl;
    std::cout << "  -getFileSignature256\t<file>\tGet SHA256 signature of the file" << std::endl;
    std::cout << "  -getFileSignature384\t<file>\tGet SHA384 signature of the file" << std::endl;
    std::cout << "  -getFileSignature512\t<file>\tGet SHA512 signature of the file" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        if (argc == 2 && std::string(argv[1]) == "-help") {
            printHelp(argv[0]);
            return 0;
        }

        return 1;
    }

    std::string command = argv[1];
    std::string filePath = argv[2];

    scanner::SignatureScanner scanner;

    if (command == "-getFileSignature1") {
        scanner::Signature signature = scanner.getFileSignatureSHA1(filePath);
        std::cout << "SHA1 Signature: " << signature << std::endl;
    } else if (command == "-getFileSignature224") {
        scanner::Signature signature = scanner.getFileSignatureSHA224(filePath);
        std::cout << "SHA224 Signature: " << signature << std::endl;
    } else if (command == "-getFileSignature256") {
        scanner::Signature signature = scanner.getFileSignatureSHA256(filePath);
        std::cout << "SHA256 Signature: " << signature << std::endl;
    } else if (command == "-getFileSignature384") {
        scanner::Signature signature = scanner.getFileSignatureSHA384(filePath);
        std::cout << "SHA384 Signature: " << signature << std::endl;
    } else if (command == "-getFileSignature512") {
        scanner::Signature signature = scanner.getFileSignatureSHA512(filePath);
        std::cout << "SHA512 Signature: " << signature << std::endl;
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}