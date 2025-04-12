#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "include/core/scanner/signature_scanner.h"

#include "include/database/database.h"

#include "include/models/exception/exception.h"
#include "include/models/log/log.h"

#include "scripts/configuration_init/configuration_init.h"
#include "scripts/database_schema/database_schema.h"
#include "scripts/dotenv_generate/dotenv_generate.h"

#endif