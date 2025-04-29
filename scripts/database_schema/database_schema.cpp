#include "database_schema.h"

namespace Scripts
{
    void setupSignaturesTable(Database::Database &global_db)
    {
        try
        {
            SQLite::Database db(global_db.getPath().empty() ? "database.sqlite" : global_db.getPath(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

            std::vector<Scripts::DotenvEntry> global_dotenv_entries = Scripts::read_dotenv_file("../../.env");

            if (global_db.getPath().empty())
            {
                for (const auto &entry : global_dotenv_entries)
                {
                    if (entry.key == "LOG_ENABLE" && entry.value == "true")
                    {
                        Models::Exception exception("setupSignaturesTable", "Database path is empty.");
                        std::cout << exception << std::endl;
                    }
                }
            }

            SQLite::Statement query(db, "SELECT name FROM sqlite_master WHERE type='table' AND name='signatures';");
            if (query.executeStep())
            {
                for (const auto &entry : global_dotenv_entries)
                {
                    if (entry.key == "LOG_ENABLE" && entry.value == "true")
                    {
                        Models::Log log(Models::INFO, "setupSignaturesTable", "Signatures table already exists.");
                        std::cout << log << std::endl;
                    }
                }
                return;
            }

            db.exec(
                "CREATE TABLE IF NOT EXISTS signatures ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT NOT NULL, "
                "description TEXT, "
                "hash TEXT NOT NULL, "
                "algorithm TEXT NOT NULL, "
                "created_at TEXT NOT NULL, "
                "updated_at TEXT NOT NULL"
                ");");

            Models::Log log(Models::INFO, "setupSignaturesTable", "Signatures table created successfully.");
            std::cout << log << std::endl;
        }
        catch (const std::exception &e)
        {
            Models::Exception exception("setupSignaturesTable", "Failed to create signatures table: " + std::string(e.what()));
            std::cout << exception << std::endl;
        }
    }

    void setupSchema(Database::Database &global_db)
    {
        try
        {
            setupSignaturesTable(global_db);

            std::vector<Scripts::DotenvEntry> global_dotenv_entries = Scripts::read_dotenv_file("../../.env");

            for (const auto &entry : global_dotenv_entries)
            {
                if (entry.key == "LOG_ENABLE" && entry.value == "true")
                {
                    Models::Log log(Models::INFO, "setupSchema", "Database schema setup completed.");
                    std::cout << log << std::endl;
                }
            }
        }
        catch (const std::exception &e)
        {
            Models::Exception exception("setupSchema", "Failed to setup database schema: " + std::string(e.what()));
            std::cout << exception << std::endl;
        }
    }
}