#include "database_schema.h"

namespace Scripts
{
    void setupSignaturesTable()
    {
        try
        {
            SQLite::Database db("database.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

            SQLite::Statement query(db, "SELECT name FROM sqlite_master WHERE type='table' AND name='signatures';");
            if (query.executeStep())
            {
                Models::Log log(Models::INFO, "setupSignaturesTable", "Signatures table already exists.");
                std::cout << log << std::endl;
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

    void setupSchema()
    {
        try
        {
            setupSignaturesTable();
            Models::Log log(Models::INFO, "setupSchema", "Database schema setup completed.");
            std::cout << log << std::endl;
        }
        catch (const std::exception &e)
        {
            Models::Exception exception("setupSchema", "Failed to setup database schema: " + std::string(e.what()));
            std::cout << exception << std::endl;
        }
    }
}