#ifndef SQLITE_DATABASE_H
#define SQLITE_DATABASE_H

#include <string>
#include <filesystem>
#include <fstream>
#include <SQLiteCpp/SQLiteCpp.h>

#include "../database.h"

#include "../../../models/logs/logs.h"
#include "../../../models/signature/signature.h"

#include "../../configuration/configuration.h"

namespace app::modules::database::sqlite
{
    class SQLite_Database : public app::modules::database::Database
    {
    public:
        SQLite_Database(std::string path, std::string file);
        ~SQLite_Database();

        void execute_query(const std::string &query);
    };
}

#endif