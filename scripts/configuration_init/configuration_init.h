#ifndef CONFIGURATION_INIT_H
#define CONFIGURATION_INIT_H

#include <iostream>

#include "../../include/models/log/log.h"
#include "../dotenv_generate/dotenv_generate.h"

namespace Scripts {
    bool verifyConfiguration();
    void initConfiguration();
}

#endif