#include "signature_scanner.h"

namespace app::core::scanner::signature_scanner
{
    SignatureScanner::SignatureScanner(std::string path, app::models::signature::HashAlgorithm algorithm)
        : path(path), algorithm(algorithm) {}

    app::models::signature::Signature SignatureScanner::scanFile(const std::string &filePath, const app::models::signature::HashAlgorithm &algorithm)
    {
        switch (algorithm)
        {
        case app::models::signature::HashAlgorithm::SHA1:
            return getFileSignatureSHA1(filePath);
        case app::models::signature::HashAlgorithm::SHA224:
            return getFileSignatureSHA224(filePath);
        case app::models::signature::HashAlgorithm::SHA256:
            return getFileSignatureSHA256(filePath);
        case app::models::signature::HashAlgorithm::SHA384:
            return getFileSignatureSHA384(filePath);
        case app::models::signature::HashAlgorithm::SHA512:
            return getFileSignatureSHA512(filePath);
        default:
            throw std::invalid_argument("Unsupported hash algorithm");
        }
    }

    std::vector<app::models::signature::Signature> SignatureScanner::scanDirectory(const std::string &directoryPath, const app::models::signature::HashAlgorithm &algorithm)
    {
        std::vector<app::models::signature::Signature> signatures;
        for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath))
        {
            if (entry.is_regular_file())
            {
                try
                {
                    signatures.push_back(scanFile(entry.path().string(), algorithm));
                }
                catch (const std::exception &e)
                {
                    app::models::logs::Logs log("Signature Scanner", "Error scanning file: " + std::string(e.what()), app::models::logs::ERROR);
                }
            }
        }
        return signatures;
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA1(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            app::models::logs::Logs log("Signature Scanner", "Failed to open file: " + filePath, app::models::logs::ERROR);
            std::cout << log << std::endl;
            return app::models::signature::Signature("SHA1", "Failed to compute SHA1", {}, app::models::signature::HashAlgorithm::SHA1);
        }

        size_t digestLength = SHA_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA_CTX sha1;
        if (!SHA1_Init(&sha1))
        {
            throw std::runtime_error("SHA1_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA1_Update(&sha1, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA1_Update failed");
            }
        }

        if (!SHA1_Final(hashData, &sha1))
        {
            throw std::runtime_error("SHA1_Final failed");
        }

        // Use the singleton instance of Configuration
        app::modules::configuration::Configuration &config = app::modules::configuration::Configuration::getInstance();
        if (config.exists() && config.get("log_enabled").second == "true")
        {
            app::models::logs::Logs log("Signature Scanner", "Scanning file: " + filePath, app::models::logs::INFO);
            std::cout << log << std::endl;

            std::ostringstream oss;
            for (unsigned char byte : hash)
            {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::string hashString = oss.str();

            app::models::logs::Logs log_result("Signature Scanner", "File Hash: " + hashString, app::models::logs::INFO);
            std::cout << log_result << std::endl;
        }

        return app::models::signature::Signature("SHA1", "SHA1 file signature", hash, app::models::signature::HashAlgorithm::SHA1);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA224(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            app::models::logs::Logs log("Signature Scanner", "Failed to open file: " + filePath, app::models::logs::ERROR);
            std::cout << log << std::endl;
            return app::models::signature::Signature("SHA224", "Failed to compute SHA224", {}, app::models::signature::HashAlgorithm::SHA224);
        }

        size_t digestLength = SHA224_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA256_CTX sha224;
        if (!SHA224_Init(&sha224))
        {
            throw std::runtime_error("SHA224_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA224_Update(&sha224, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA224_Update failed");
            }
        }

        if (!SHA224_Final(hashData, &sha224))
        {
            throw std::runtime_error("SHA224_Final failed");
        }

        // Use the singleton instance of Configuration
        app::modules::configuration::Configuration &config = app::modules::configuration::Configuration::getInstance();
        if (config.exists() && config.get("log_enabled").second == "true")
        {
            app::models::logs::Logs log("Signature Scanner", "Scanning file: " + filePath, app::models::logs::INFO);
            std::cout << log << std::endl;

            std::ostringstream oss;
            for (unsigned char byte : hash)
            {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::string hashString = oss.str();

            app::models::logs::Logs log_result("Signature Scanner", "File Hash: " + hashString, app::models::logs::INFO);
            std::cout << log_result << std::endl;
        }

        return app::models::signature::Signature("SHA224", "SHA224 file signature", hash, app::models::signature::HashAlgorithm::SHA224);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA256(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            app::models::logs::Logs log("Signature Scanner", "Failed to open file: " + filePath, app::models::logs::ERROR);
            std::cout << log << std::endl;
            return app::models::signature::Signature("SHA256", "Failed to compute SHA256", {}, app::models::signature::HashAlgorithm::SHA256);
        }

        size_t digestLength = SHA256_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA256_CTX sha256;
        if (!SHA256_Init(&sha256))
        {
            throw std::runtime_error("SHA256_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA256_Update(&sha256, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA256_Update failed");
            }
        }

        if (!SHA256_Final(hashData, &sha256))
        {
            throw std::runtime_error("SHA256_Final failed");
        }

        // Use the singleton instance of Configuration
        app::modules::configuration::Configuration &config = app::modules::configuration::Configuration::getInstance();
        if (config.exists() && config.get("log_enabled").second == "true")
        {
            app::models::logs::Logs log("Signature Scanner", "Scanning file: " + filePath, app::models::logs::INFO);
            std::cout << log << std::endl;

            std::ostringstream oss;
            for (unsigned char byte : hash)
            {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::string hashString = oss.str();

            app::models::logs::Logs log_result("Signature Scanner", "File Hash: " + hashString, app::models::logs::INFO);
            std::cout << log_result << std::endl;
        }

        return app::models::signature::Signature("SHA256", "SHA256 file signature", hash, app::models::signature::HashAlgorithm::SHA256);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA384(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            app::models::logs::Logs log("Signature Scanner", "Failed to open file: " + filePath, app::models::logs::ERROR);
            std::cout << log << std::endl;
            return app::models::signature::Signature("SHA384", "Failed to compute SHA384", {}, app::models::signature::HashAlgorithm::SHA384);
        }

        size_t digestLength = SHA384_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA512_CTX sha384;
        if (!SHA384_Init(&sha384))
        {
            throw std::runtime_error("SHA384_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA384_Update(&sha384, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA384_Update failed");
            }
        }

        if (!SHA384_Final(hashData, &sha384))
        {
            throw std::runtime_error("SHA384_Final failed");
        }

        // Use the singleton instance of Configuration
        app::modules::configuration::Configuration &config = app::modules::configuration::Configuration::getInstance();
        if (config.exists() && config.get("log_enabled").second == "true")
        {
            app::models::logs::Logs log("Signature Scanner", "Scanning file: " + filePath, app::models::logs::INFO);
            std::cout << log << std::endl;

            std::ostringstream oss;
            for (unsigned char byte : hash)
            {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::string hashString = oss.str();

            app::models::logs::Logs log_result("Signature Scanner", "File Hash: " + hashString, app::models::logs::INFO);
            std::cout << log_result << std::endl;
        }

        return app::models::signature::Signature("SHA384", "SHA384 file signature", hash, app::models::signature::HashAlgorithm::SHA384);
    }

    app::models::signature::Signature SignatureScanner::getFileSignatureSHA512(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            app::models::logs::Logs log("Signature Scanner", "Failed to open file: " + filePath, app::models::logs::ERROR);
            std::cout << log << std::endl;
            return app::models::signature::Signature("SHA512", "Failed to compute SHA512", {}, app::models::signature::HashAlgorithm::SHA512);
        }

        size_t digestLength = SHA512_DIGEST_LENGTH;
        std::vector<unsigned char> hash(digestLength);
        std::vector<char> buffer(8192);
        unsigned char *hashData = hash.data();

        SHA512_CTX sha512;
        if (!SHA512_Init(&sha512))
        {
            throw std::runtime_error("SHA512_Init failed");
        }

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
        {
            if (!SHA512_Update(&sha512, buffer.data(), file.gcount()))
            {
                throw std::runtime_error("SHA512_Update failed");
            }
        }

        if (!SHA512_Final(hashData, &sha512))
        {
            throw std::runtime_error("SHA512_Final failed");
        }

        // Use the singleton instance of Configuration
        app::modules::configuration::Configuration &config = app::modules::configuration::Configuration::getInstance();
        if (config.exists() && config.get("log_enabled").second == "true")
        {
            app::models::logs::Logs log("Signature Scanner", "Scanning file: " + filePath, app::models::logs::INFO);
            std::cout << log << std::endl;

            std::ostringstream oss;
            for (unsigned char byte : hash)
            {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::string hashString = oss.str();

            app::models::logs::Logs log_result("Signature Scanner", "File Hash: " + hashString, app::models::logs::INFO);
            std::cout << log_result << std::endl;
        }

        return app::models::signature::Signature("SHA512", "SHA512 file signature", hash, app::models::signature::HashAlgorithm::SHA512);
    }
}