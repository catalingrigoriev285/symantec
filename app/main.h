#ifndef APP_H
#define APP_H

#include <sstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "modules/configuration/configuration.h"
#include "modules/database/SQLite_Database/SQLite_Database.h"
#include "modules/session/session.h"

#include "models/logs/logs.h"
#include "models/signature/signature.h"

#include "core/analytics/analytics.h"
#include "core/scanner/signature_scanner/signature_scanner.h"

static void glfw_error_callback(int error, const char *description)
{
    // fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    std::string error_message = "{Glfw Error} " + std::to_string(error);
    app::models::logs::Logs log(error_message, description, app::models::logs::enum_log_type::ERROR);

    app::modules::configuration::Configuration config("symantec.ini");
    if (config.exists() && config.get("log_enabled").second == "true")
    {
        std::cout << log << std::endl;
    }
}

class ImGuiConsoleBuffer : public std::streambuf
{
public:
    std::ostringstream buffer;

protected:
    int overflow(int c) override
    {
        if (c != EOF)
        {
            buffer.put(static_cast<char>(c));
        }
        return c;
    }
};

#endif