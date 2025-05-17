#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include <SQLiteCpp/SQLiteCpp.h>

namespace app::models
{
    class Model
    {
    protected:
        std::string table;
        std::map<std::string, std::string> attributes;

        static SQLite::Database &db()
        {
            static SQLite::Database database("database.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            return database;
        }

    public:
        Model(const std::string &tableName) : table(tableName) {}

        void set(const std::string &key, const std::string &value)
        {
            attributes[key] = value;
        }

        std::string get(const std::string &key)
        {
            return attributes[key];
        }

        bool save()
        {
            std::ostringstream keys, values, placeholders;
            for (const auto &[key, value] : attributes)
            {
                keys << key << ",";
                values << "'" << value << "',";
            }

            std::string sql = "INSERT INTO " + table + " (" +
                              keys.str().substr(0, keys.str().size() - 1) + ") VALUES (" +
                              values.str().substr(0, values.str().size() - 1) + ");";

            try
            {
                db().exec(sql);
                return true;
            }
            catch (const std::exception &e)
            {
                std::cerr << "SQLite error: " << e.what() << "\n";
                return false;
            }
        }

        void all()
        {
            try
            {
                SQLite::Statement query(db(), "SELECT * FROM " + table);
                while (query.executeStep())
                {
                    for (int i = 0; i < query.getColumnCount(); ++i)
                    {
                        std::cout << query.getColumnName(i) << ": " << query.getColumn(i) << "\n";
                    }
                    std::cout << "---------------------------\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "SQLite error: " << e.what() << "\n";
            }
        }
    };
}

#endif