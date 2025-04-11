#include <iostream>
#include <string>

#include "include/core/scanner/signature_scanner.h"
#include "include/database/database.h"

#include "scripts/dotenv_generate/dotenv_generate.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || (argc == 2 && std::string(argv[1]) == "-help"))
    {
        std::cout << "Scripts:" << std::endl;
        std::cout << "  -dotenvVerify\t\tVerify if .env file exists" << std::endl;
        std::cout << "  -dotenvGenerate\tGenerate .env file" << std::endl;
        std::cout << std::endl;
        std::cout << "Database:" << std::endl;
        std::cout << " Raw:" << std::endl;
        std::cout << "  -dbVerifyRawConnection\t<file>\tVerify raw database connection" << std::endl;
        std::cout << "  -dbCreateRawDatabase\t\t<file>\tCreate raw database" << std::endl;
        std::cout << std::endl;
        std::cout << " SQLite:" << std::endl;
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

    std::string command = argv[1];
    std::string file = (argc > 2) ? argv[2] : "";

    Scanner::SignatureScanner scanner;

    if (command == "-dotenvVerify")
    {
        if (Scripts::verify_env_file_exists())
        {
            std::cout << "The .env file exists." << std::endl;
        }
        else
        {
            std::cout << "The .env file does not exist." << std::endl;
        }
    }
    else if (command == "-dotenvGenerate")
    {
        Scripts::generate_dot_env();
    }
    else if (command == "-dbVerifyRawConnection" || command == "-dbCreateRawDatabase")
    {
        if (file.empty())
        {
            std::cerr << "Error: <file> parameter is required for " << command << std::endl;
            return 1;
        }
        Database::RawDatabase db("localhost", "test.db", "user", "password", 0, Database::DatabaseType::Raw, file);
        if (command == "-dbVerifyRawConnection")
        {
            db.verifyConnection();
        }
        else
        {
            db.createDatabase();
        }
    }
    else if (command == "-dbVerifySQLiteConnection" || command == "-dbCreateSQLiteDatabase")
    {
        if (file.empty())
        {
            std::cerr << "Error: <file> parameter is required for " << command << std::endl;
            return 1;
        }
        Database::SQLiteDatabase db("localhost", "test.db", "user", "password", 0, Database::DatabaseType::SQLite, file);
        if (command == "-dbVerifySQLiteConnection")
        {
            db.verifyConnection();
        }
        else
        {
            db.createDatabase();
        }
    }
    else if (command == "-getFileSignature1" || command == "-getFileSignature224" ||
             command == "-getFileSignature256" || command == "-getFileSignature384" ||
             command == "-getFileSignature512")
    {
        if (file.empty())
        {
            std::cerr << "Error: <file> parameter is required for " << command << std::endl;
            return 1;
        }
        Scanner::Signature signature;
        if (command == "-getFileSignature1")
        {
            signature = scanner.getFileSignatureSHA1(file);
        }
        else if (command == "-getFileSignature224")
        {
            signature = scanner.getFileSignatureSHA224(file);
        }
        else if (command == "-getFileSignature256")
        {
            signature = scanner.getFileSignatureSHA256(file);
        }
        else if (command == "-getFileSignature384")
        {
            signature = scanner.getFileSignatureSHA384(file);
        }
        else if (command == "-getFileSignature512")
        {
            signature = scanner.getFileSignatureSHA512(file);
        }
        std::cout << command.substr(13) << " Signature: " << signature << std::endl;
    }
    else
    {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}