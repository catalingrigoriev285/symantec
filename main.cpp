#include <iostream>

#include "include/core/scanner/signature_scanner.h"

int main(){
    // Example usage of the SignatureScanner class
    scanner::SignatureScanner scanner;
    std::string filePath = "example.txt"; // Replace with your file path
    scanner::Signature signature = scanner.getFileSignatureSHA256(filePath);
    std::cout << signature << std::endl;

    getchar();
    return 0;
}