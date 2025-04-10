#include <iostream>
#include <string>

#include "include/core/scanner/signature_scanner.h"
#include "include/database/database.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        if (argc == 2 && std::string(argv[1]) == "-help")
        {
            std::cout << "Database:" << std::endl;
            std::cout << "  -dbVerifySQLiteConnection\t<file>\tVerify SQLite database connection" << std::endl;
            std::cout << "  -dbCreateSQLiteDatabase\t<file>\tCreate SQLite database" << std::endl;
            std::cout << std::endl;
            std::cout << "File Signature:" << std::endl;
            std::cout << "  -getFileSignature1\t<file>\tGet SHA1 signature of the file" << std::endl;
            std::cout << "  -getFileSignature224\t<file>\tGet SHA224 signature of the file" << std::endl;
            std::cout << "  -getFileSignature256\t<file>\tGet SHA256 signature of the file" << std::endl;
            std::cout << "  -getFileSignature384\t<file>\tGet SHA384 signature of the file" << std::endl;
            std::cout << "  -getFileSignature512\t<file>\tGet SHA512 signature of the file" << std::endl;
            return 0;
        }

        return 1;
    }

    Scanner::SignatureScanner scanner;

    if (std::string(argv[1]) == "-dbVerifySQLiteConnection")
    {
        Database::SQLiteDatabase db("localhost", "test.db", "user", "password", 0, Database::DatabaseType::SQLite, argv[2]);
        db.verifyConnection();
    }
    else if (std::string(argv[1]) == "-dbCreateSQLiteDatabase")
    {
        Database::SQLiteDatabase db("localhost", "test.db", "user", "password", 0, Database::DatabaseType::SQLite, argv[2]);
        db.createDatabase();
    }
    else if (std::string(argv[1]) == "-getFileSignature1")
    {
        Scanner::Signature signature = scanner.getFileSignatureSHA1(argv[2]);
        std::cout << "SHA1 Signature: " << signature << std::endl;
    }
    else if (std::string(argv[1]) == "-getFileSignature224")
    {
        Scanner::Signature signature = scanner.getFileSignatureSHA224(argv[2]);
        std::cout << "SHA224 Signature: " << signature << std::endl;
    }
    else if (std::string(argv[1]) == "-getFileSignature256")
    {
        Scanner::Signature signature = scanner.getFileSignatureSHA256(argv[2]);
        std::cout << "SHA256 Signature: " << signature << std::endl;
    }
    else if (std::string(argv[1]) == "-getFileSignature384")
    {
        Scanner::Signature signature = scanner.getFileSignatureSHA384(argv[2]);
        std::cout << "SHA384 Signature: " << signature << std::endl;
    }
    else if (std::string(argv[1]) == "-getFileSignature512")
    {
        Scanner::Signature signature = scanner.getFileSignatureSHA512(argv[2]);
        std::cout << "SHA512 Signature: " << signature << std::endl;
    }
    else
    {
        std::cerr << "Unknown command: " << argv[1] << std::endl;
        return 1;
    }

    return 0;
}