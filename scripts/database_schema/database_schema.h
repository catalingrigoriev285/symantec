#ifndef DATABASE_SCHEMA_H
#define DATABASE_SCHEMA_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

#include "../../include/models/log/log.h"
#include "../../include/models/exception/exception.h"

namespace Scripts
{
    void setupSignaturesTable();

    void setupSchema();
}

#endif