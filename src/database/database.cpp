#include "../../include/database/database.h"

namespace Database
{
    /* Database */
    Database::Database() : db_host("localhost"), db_name("test.db"), db_user("user"), db_password("password"), db_port(0), db_type(DatabaseType::SQLite), db_path("")
    {
        if(Scripts::verify_env_file_exists()){
            std::ifstream env_file("../../.env");
            std::string line;
            while (std::getline(env_file, line))
            {
                if (line.find("DB_CONNECTION=") == 0)
                {
                    db_type = (line.substr(15) == "SQLite") ? DatabaseType::SQLite : DatabaseType::Raw;
                }
                else if (line.find("DB_HOST=") == 0)
                {
                    db_host = line.substr(8);
                }
                else if (line.find("DB_DATABASE=") == 0)
                {
                    db_name = line.substr(12);
                }
                else if (line.find("DB_USERNAME=") == 0)
                {
                    db_user = line.substr(12);
                }
                else if (line.find("DB_PASSWORD=") == 0)
                {
                    db_password = line.substr(12);
                }
            }
            env_file.close();
        }
    }
    Database::~Database() {}

    /* RawDatabase */
    RawDatabase::~RawDatabase() {}

    void RawDatabase::verifyConnection()
    {
        std::ifstream file(db_path);
        if (file.is_open())
        {
            std::cout << "Raw database connection verified successfully." << std::endl;
            file.close();
        }
        else
        {
            std::cerr << "Raw database connection failed: Unable to open file." << std::endl;
        }
    }

    void RawDatabase::createDatabase()
    {
        std::ofstream file(db_path);
        if (file.is_open())
        {
            std::cout << "Raw database created successfully." << std::endl;
            file.close();
        }
        else
        {
            std::cerr << "Raw database creation failed: Unable to create file." << std::endl;
        }
    }

    /* SQliteDatabase */
    SQLiteDatabase::~SQLiteDatabase() {}

    void SQLiteDatabase::verifyConnection()
    {
        try
        {
            SQLite::Database db(db_path, SQLite::OPEN_READONLY);
            std::cout << "SQLite connection verified successfully." << std::endl;
        }
        catch (const SQLite::Exception &e)
        {
            std::cerr << "SQLite connection failed: " << e.what() << std::endl;
        }
    }

    void SQLiteDatabase::createDatabase()
    {
        try
        {
            SQLite::Database db(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            std::cout << "SQLite database created successfully." << std::endl;
        }
        catch (const SQLite::Exception &e)
        {
            std::cerr << "SQLite database creation failed: " << e.what() << std::endl;
        }
    }
}