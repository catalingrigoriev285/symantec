#include "../../include/database/database.h"

namespace Database {
    Database::Database() : db_host("localhost"), db_name("test.db"), db_user("user"), db_password("password"), db_port(0), db_type(DatabaseType::SQLITE), db_path("") {}

    Database::~Database() {}

    void Database::verifySQLiteConnection() {
        try {
            SQLite::Database db(db_path, SQLite::OPEN_READONLY);
            std::cout << "SQLite connection verified successfully." << std::endl;
        } catch (const SQLite::Exception& e) {
            std::cerr << "SQLite connection failed: " << e.what() << std::endl;
        }
    }
}