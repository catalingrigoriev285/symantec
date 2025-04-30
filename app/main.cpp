#include "main.h"

int main(){
    app::core::scanner::signature_scanner::SignatureScanner scanner;
    
    scanner.scanFile("symantec.2ini", app::models::signature::HashAlgorithm::SHA256);

    return 0;
}