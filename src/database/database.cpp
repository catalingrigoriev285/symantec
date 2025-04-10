#include "../../include/database/database.h"

namespace Database {
    Database::Database() : db_host("localhost"), db_name("test.db"), db_user("user"), db_password("password"), db_port(0), db_type(DatabaseType::SQLite), db_path("") {}
    Database::~Database() {}

    SQLiteDatabase::~SQLiteDatabase() {}

    void SQLiteDatabase::verifyConnection() {
        try {
            SQLite::Database db(db_path, SQLite::OPEN_READONLY);
            std::cout << "SQLite connection verified successfully." << std::endl;
        } catch (const SQLite::Exception& e) {
            std::cerr << "SQLite connection failed: " << e.what() << std::endl;
        }
    }

    void SQLiteDatabase::createDatabase() {
        try {
            SQLite::Database db(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            std::cout << "SQLite database created successfully." << std::endl;
        } catch (const SQLite::Exception& e) {
            std::cerr << "SQLite database creation failed: " << e.what() << std::endl;
        }
    }
}