#ifndef APP_H
#define APP_H

#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "modules/configuration/configuration.h"

#include "models/logs/logs.h"

static void glfw_error_callback(int error, const char *description)
{
    // fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    std::string error_message = "{Glfw Error} " + std::to_string(error);
    app::models::logs::Logs log(error_message, description, app::models::logs::enum_log_type::ERROR);

    app::modules::configuration::Configuration config("symantec.ini");
    if (config.exists() && config.get("log_enabled").second == "true"){
        std::cout << log << std::endl;
    }
}

#endif