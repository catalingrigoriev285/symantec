#ifndef DATABASE_SCHEMA_H
#define DATABASE_SCHEMA_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

#include "../../include/models/log/log.h"
#include "../../include/models/exception/exception.h"

#include "../dotenv_reader/dotenv_reader.h"

#include "../../include/database/database.h"

namespace Scripts
{
    void setupSignaturesTable(Database::Database &global_db);
    void setupSchema(Database::Database &global_db);
}

#endif