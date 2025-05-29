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

#include "../../modules/configuration/configuration.h"

namespace app::models
{
    class Model
    {
    protected:
        std::string table;
        std::map<std::string, std::string> attributes;

        static int modelCount;

        static SQLite::Database &db()
        {
            app::modules::configuration::Configuration config("symantec.ini");

            std::string database_path = config.get("db_path").second + "/" + config.get("db_file").second;

            static SQLite::Database database(database_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            return database;
        }

    public:
        Model(const std::string &tableName) : table(tableName)
        {
            ++modelCount;
        }

        virtual ~Model()
        {
            --modelCount;
        }

        static int getModelCount()
        {
            return modelCount;
        }

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

        std::vector<std::map<std::string, std::string>> allAsVector()
        {
            std::vector<std::map<std::string, std::string>> results;
            try
            {
                SQLite::Statement query(db(), "SELECT * FROM " + table);
                while (query.executeStep())
                {
                    std::map<std::string, std::string> row;
                    for (int i = 0; i < query.getColumnCount(); ++i)
                    {
                        row[query.getColumnName(i)] = query.getColumn(i).getText();
                    }
                    results.push_back(row);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "SQLite error: " << e.what() << "\n";
            }
            return results;
        }

        bool operator==(const Model &other) const
        {
            return this->attributes == other.attributes;
        }

        bool operator!=(const Model &other) const
        {
            return !(*this == other);
        }

        bool operator<(const Model &other) const
        {
            return this->attributes.size() < other.attributes.size();
        }

        bool operator>(const Model &other) const
        {
            return this->attributes.size() > other.attributes.size();
        }

        bool operator<=(const Model &other) const
        {
            return !(*this > other);
        }

        bool operator>=(const Model &other) const
        {
            return !(*this < other);
        }
    };
}

#endif