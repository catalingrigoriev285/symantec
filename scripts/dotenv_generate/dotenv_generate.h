#ifndef DOTENV_GENERATE_H
#define DOTENV_GENERATE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <io.h>
#include <fcntl.h>

namespace Scripts
{
    bool verify_env_file_exists();
    void generate_dot_env();
}

#endif