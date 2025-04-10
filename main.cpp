#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h> // SQLiteCpp library

#include "include/core/scanner/signature_scanner.h"

int main()
{
    try
    {
        // Open a database file
        SQLite::Database db("example.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Create a table named 'users'
        db.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);");

        // Insert random values into the 'users' table
        db.exec("INSERT INTO users (name, age) VALUES ('Alice', 25);");
        db.exec("INSERT INTO users (name, age) VALUES ('Bob', 30);");
        db.exec("INSERT INTO users (name, age) VALUES ('Charlie', 35);");

        // Query and display the inserted data
        SQLite::Statement userQuery(db, "SELECT * FROM users;");
        while (userQuery.executeStep())
        {
            int id = userQuery.getColumn(0);
            const char *name = userQuery.getColumn(1);
            int age = userQuery.getColumn(2);

            std::cout << "User: " << id << ", " << name << ", " << age << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    return 0;
}