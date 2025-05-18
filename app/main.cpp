#include "main.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#undef ERROR

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    app::modules::configuration::Configuration config("symantec.ini");
    app::modules::database::sqlite::SQLite_Database db(config.get("db_path").second, config.get("db_file").second);

    ImGuiConsoleBuffer consoleBuffer;
    std::ostream consoleStream(&consoleBuffer);

    std::streambuf *oldCoutBuffer = std::cout.rdbuf(consoleStream.rdbuf());

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char *glsl_version = "#version 130";
    GLFWwindow *window = glfwCreateWindow(800, 600, "Symantec Antivirus", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::string active_frame = "home";

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.25f, io.DisplaySize.y));
        ImGui::Begin("menu_frame", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        float buttonWidth = ImGui::GetContentRegionAvail().x - 10.0f;
        float buttonHeight = 30.0f;
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10));

        if (ImGui::Button("Home", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "home";
        }
        if (ImGui::Button("Scanning", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "scanning";
        }
        if (ImGui::Button("Updates", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "updates";
        }
        if (ImGui::Button("Services", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "services";
        }
        if (ImGui::Button("Settings", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "settings";
        }
        if (ImGui::Button("Administration", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "administration";
        }
        if (ImGui::Button("Console", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "console";
        }
        if (ImGui::Button("About", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "about";
        }

        float windowHeight = ImGui::GetWindowHeight();
        float textHeight = ImGui::CalcTextSize("Version 1.0.0").y;
        ImGui::SetCursorPosY(windowHeight - textHeight - 10);
        ImGui::Text("Version 1.0.0");

        ImGui::PopStyleVar();
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.25f, 0));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.75f, io.DisplaySize.y));
        ImGui::Begin("main_frame", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        if (active_frame == "home")
        {
            ImGui::Text("home");
        }
        else if (active_frame == "scanning")
        {
            float buttonWidth = ImGui::GetContentRegionAvail().x / 2.0f - 5.0f;
            float buttonHeight = 50.0f;

            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Scanning:");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));

            if (ImGui::Button("Quick Scan", ImVec2(buttonWidth, buttonHeight)))
            {
                // Handle Quick Scan logic
            }
            ImGui::SameLine();
            if (ImGui::Button("Full Scan", ImVec2(buttonWidth, buttonHeight)))
            {
                // Handle Full Scan logic
            }
            if (ImGui::Button("Custom Scan", ImVec2(buttonWidth, buttonHeight)))
            {
                // Handle Custom Scan logic
            }
            ImGui::SameLine();
            if (ImGui::Button("Scheduled Scan", ImVec2(buttonWidth, buttonHeight)))
            {
                // Handle Scheduled Scan logic
            }

            ImGui::PopStyleVar();

            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            if (ImGui::Selectable("View Scanning History"))
            {
                // Handle Scanning History logic
            }
        }
        else if (active_frame == "updates")
        {
            ImGui::Text("This is Frame 3.");
        }
        else if (active_frame == "services")
        {
            if (ImGui::Button("Get file signature", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                active_frame = "services_get_file_signature";
            }
        }
        else if (active_frame == "services_get_file_signature")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Get file signature");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            static char signature_hash[128] = "";

            ImGui::InputTextWithHint("##signature_hash", "Enter file path there", signature_hash, ImGui::GetContentRegionAvail().x);
            ImGui::SameLine();

            static const char *signature_algorithm[] = {
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA1),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA224),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA256),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA384),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA512)};

            static int selectedType = 0;
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::Combo("##signature_algorithm", &selectedType, signature_algorithm, IM_ARRAYSIZE(signature_algorithm));

            static std::string file_hash_result = "";
            static std::string file_hash_only = "";

            if (ImGui::Button("Browse", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                OPENFILENAMEW ofn;
                wchar_t szFile[260];

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = glfwGetWin32Window(window);
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = L'\0';
                ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
                ofn.lpstrFilter = L"All Files\0*.*\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileNameW(&ofn) == TRUE)
                {
                    wcstombs(signature_hash, szFile, sizeof(signature_hash)); // Convert wide-char to narrow-char
                }
            }

            if (ImGui::Button("Get file hash", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                std::string file_path = signature_hash;

                std::ifstream file(file_path);
                if (!file.good())
                {
                    ImGui::OpenPopup("Error");
                    file_hash_result = "Error: File does not exist.";
                }
                else
                {
                    app::models::signature::HashAlgorithm algorithm = static_cast<app::models::signature::HashAlgorithm>(selectedType);

                    app::core::scanner::signature_scanner::SignatureScanner scanner;
                    app::models::signature::Signature file_hashes = scanner.scanFile(file_path, algorithm);

                    file_hash_result = "File Hash: ";

                    std::ostringstream oss;
                    for (const auto &byte : file_hashes.getHash())
                    {
                        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
                    }
                    file_hash_result += oss.str();
                    file_hash_only = oss.str();

                    file_hash_result += "\nHash Algorithm: " + std::string(app::models::signature::HashAlgorithm_to_string(file_hashes.getAlgorithm()));
                }
            }

            if (!file_hash_only.empty())
            {
                ImGui::BeginChild("file_hash_result", ImVec2(0, 0), false);
                ImGui::TextWrapped(file_hash_result.c_str());

                ImGui::Dummy(ImVec2(0.0f, 10.0f));
                ImGui::Separator();
                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                if (ImGui::Button("Copy to clipboard", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
                {
                    ImGui::SetClipboardText(file_hash_only.c_str());
                    ImGui::OpenPopup("clipboard_copy_alert");
                    app::models::logs::Logs log("Signature Scanner", "File hash copied to clipboard: " + file_hash_only, app::models::logs::INFO);
                }

                ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                if (ImGui::BeginPopup("clipboard_copy_alert"))
                {
                    ImGui::Text("Hash hash copied to clipboard!");
                    if (ImGui::Button("Close"))
                    {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }

                ImGui::EndChild();
            }

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopup("Error"))
            {
                ImGui::Text("Error: File does not exist. Please check the file path.");
                if (ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        else if (active_frame == "settings")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Logging System:");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            // LOG_ENABLED
            static bool log_enabled = false;

            if (config.exists() && config.get("log_enabled").second == "true")
            {
                log_enabled = true;
            }

            if (ImGui::Checkbox("##log_enabled", &log_enabled))
            {
                if (log_enabled)
                {
                    config.set("log_enabled", "true");
                }
                else
                {
                    config.set("log_enabled", "false");
                }
                config.save();
            }
            ImGui::SameLine();
            ImGui::Text("Display logs in console");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            // LOG_WRITE_TO_FILE
            static bool log_write_to_file = false;
            if (config.exists() && config.get("log_write_to_file").second == "true")
            {
                log_write_to_file = true;
            }

            if (ImGui::Checkbox("##log_write_to_file", &log_write_to_file))
            {
                if (log_write_to_file)
                {
                    config.set("log_write_to_file", "true");
                }
                else
                {
                    config.set("log_write_to_file", "false");
                }
                config.save();
            }

            ImGui::SameLine();
            ImGui::Text("Write logs to file");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
        }
        else if (active_frame == "administration")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Database:");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            if (ImGui::Button("Add a new signature to database", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                active_frame = "administration_database_signatures_add";
            }

            if (ImGui::Button("Load all signatures from database", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                active_frame = "administration_database_signatures_load";
            }
        }
        else if (active_frame == "administration_database_signatures_add")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Add a new signature to database");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            static char signature_hash[128] = "";
            ImGui::InputTextWithHint("##signature_hash", "Enter hash here", signature_hash, ImGui::GetContentRegionAvail().x);
            ImGui::SameLine();

            static const char *signature_algorithm[] = {
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA1),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA224),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA256),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA384),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA512)};

            static int selectedType = 0;
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::Combo("##signature_algorithm", &selectedType, signature_algorithm, IM_ARRAYSIZE(signature_algorithm));

            if (ImGui::Button("Save", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                std::vector<unsigned char> hash;
                for (size_t i = 0; i < strlen(signature_hash); i += 2)
                {
                    unsigned int byte;
                    std::stringstream ss;
                    ss << std::hex << std::string(signature_hash + i, 2);
                    ss >> byte;
                    hash.push_back(static_cast<unsigned char>(byte));
                }

                if (hash.empty() || hash.size() % 2 != 0)
                {
                    app::models::logs::Logs log("Signature Scanner", "Invalid signature format: " + std::string(signature_hash), app::models::logs::ERROR);
                    ImGui::OpenPopup("Error");
                }
                else
                {
                    app::models::signature::HashAlgorithm algorithm = static_cast<app::models::signature::HashAlgorithm>(selectedType);

                    app::models::signature::Signature signature = app::models::signature::Signature(
                        std::string(signature_algorithm[selectedType]), std::string(signature_algorithm[selectedType]) + " file signature", hash, algorithm);

                    db.execute_query("INSERT INTO signatures (name, description, value, algorithm, hash) VALUES (?, ?, ?, ?, ?)",
                                     {signature.getName(), signature.getDescription(), signature.getHashString(), signature.getAlgorithmString(), "0x" + signature.getAlgorithmString()});

                    app::models::logs::Logs log("Signature Scanner", std::string(signature_hash) + " successfully added to database!", app::models::logs::INFO);
                    ImGui::OpenPopup("Success");
                }
            }

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopup("Error"))
            {
                ImGui::Text("Invalid signature format. Please check the input.");
                if (ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopup("Success"))
            {
                ImGui::Text("Signature successfully added to the database!");
                if (ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        else if (active_frame == "administration_database_signatures_load"){
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Load all signatures from database");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            std::vector<std::map<std::string, std::string>> signatures_vect;
            app::models::signature::Signature signatures;
            signatures_vect = signatures.allAsVector();

            if (signatures_vect.empty())
            {
                ImGui::Text("No signatures found in the database.");
            }
            else
            {
                for (const auto &signature : signatures_vect)
                {
                    ImGui::Text("Signature: %s", signature);
                }
            }
        }
        else if (active_frame == "console")
        {
            ImGui::BeginChild("ConsoleOutput", ImVec2(0, 0), true);
            ImGui::TextWrapped(consoleBuffer.buffer.str().c_str());
            ImGui::EndChild();
        }
        else if (active_frame == "about")
        {
            ImGui::BeginChild("AboutText", ImVec2(0, 0), false);
            ImGui::TextWrapped("Symantec is an open-source antivirus software developed as a university project. Designed to detect, prevent, and remove malware, it provides essential security features such as real-time scanning, signature-based detection, and heuristic analysis.\n\nCreated by Catalin Grigoriev");
            ImGui::EndChild();
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout.rdbuf(oldCoutBuffer);

    return 0;
}