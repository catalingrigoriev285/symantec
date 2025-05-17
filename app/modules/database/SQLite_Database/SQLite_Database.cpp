#include "SQLite_Database.h"

namespace app::modules::database::sqlite
{
    SQLite_Database::SQLite_Database(std::string path, std::string file)
    {
        Database::set_connection(app::modules::database::connection_enum_type::SQLITE);
        Database::set_path(path);
        Database::set_file(file);

        std::string database_path = Database::get_path() + "/" + Database::get_file();

        if (!std::filesystem::exists(database_path))
        {
            try
            {
                std::filesystem::create_directories(Database::get_path());
                std::ofstream database_file(database_path);
                database_file.close();

                app::models::logs::Logs log("SQLite Database", "Database file created successfully: " + database_path, app::models::logs::enum_log_type::INFO);
            }
            catch (const std::exception &e)
            {
                app::models::logs::Logs log("SQLite Database", "Error creating database file: " + std::string(e.what()), app::models::logs::enum_log_type::ERROR);
            }
        }

        try
        {
            SQLite::Database db(database_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            db.exec("PRAGMA foreign_keys = ON;");

            app::models::logs::Logs log("SQLite Database", "Database file opened successfully: " + database_path, app::models::logs::enum_log_type::INFO);

            // database schema
            try
            {
                SQLite::Statement query(db, "SELECT name FROM sqlite_master WHERE type='table' LIMIT 1;");
                if (!query.executeStep())
                {
                    app::models::signature::Signature signature;
                    std::vector<std::pair<std::string, std::string>> signature_queries = signature.loadQueries();

                    for (const auto &query : signature_queries)
                    {
                        if (query.first == "create_database")
                        {
                            db.exec(query.second);
                        }
                    }

                    app::models::logs::Logs log("SQLite Database", "Database schema created successfully.", app::models::logs::enum_log_type::INFO);
                }
                else
                {
                    app::models::logs::Logs log("SQLite Database", "Database already contains tables. Schema creation skipped.", app::models::logs::enum_log_type::INFO);
                }
            }
            catch (const std::exception &e)
            {
                app::models::logs::Logs log("SQLite Database", "Error creating database schema: " + std::string(e.what()), app::models::logs::enum_log_type::ERROR);
            }
        }
        catch (const std::exception &e)
        {
            app::models::logs::Logs log("SQLite Database", "Error opening database: " + std::string(e.what()), app::models::logs::enum_log_type::ERROR);
        }
    }

    SQLite_Database::~SQLite_Database()
    {
        //
    }

    void SQLite_Database::execute_query(const std::string &query)
    {
        std::string database_path = Database::get_path() + "/" + Database::get_file();

        try
        {
            SQLite::Database db(database_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            db.exec(query);
        }
        catch (...)
        {
            app::models::logs::Logs log("SQLite Database", "Error executing query: " + query, app::models::logs::enum_log_type::ERROR);
        }
    }
}