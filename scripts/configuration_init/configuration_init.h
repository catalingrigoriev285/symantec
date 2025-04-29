#ifndef CONFIGURATION_INIT_H
#define CONFIGURATION_INIT_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "../../include/models/log/log.h"
#include "../dotenv_reader/dotenv_reader.h"
#include "../dotenv_generate/dotenv_generate.h"

#include "../../include/database/database.h"

namespace Scripts {
    bool verifyConfiguration();
    void initConfiguration(Database::Database &db);
    void cleanConfiguration();
}

#endif