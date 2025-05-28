#include "main.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ShlObj.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#undef ERROR

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    app::modules::configuration::Configuration config("symantec.ini");
    app::modules::database::sqlite::SQLite_Database db(config.get("db_path").second, config.get("db_file").second);
    app::modules::session::Session session;

    ImGuiConsoleBuffer consoleBuffer;
    std::ostream consoleStream(&consoleBuffer);

    std::streambuf *oldCoutBuffer = std::cout.rdbuf(consoleStream.rdbuf());

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char *glsl_version = "#version 130";
    GLFWwindow *window = glfwCreateWindow(1200, 800, "Symantec Antivirus", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Custom modern style
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Load fonts
    ImFont* defaultFont = io.Fonts->AddFontDefault();
    
    // Configure and add a larger font
    ImFontConfig fontConfig;
    fontConfig.SizePixels = 24.0f; // Set the desired font size
    ImFont* largeFont = io.Fonts->AddFontDefault(&fontConfig);
    
    io.Fonts->Build();

    // Colors
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    colors[ImGuiCol_Header]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    // Style
    style.WindowPadding = ImVec2(15, 15);
    style.WindowRounding = 5.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 3.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.DisplayWindowPadding = ImVec2(19, 19);
    style.DisplaySafeAreaPadding = ImVec2(3, 3);
    style.ChildRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;

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

        // Main menu window
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.25f, io.DisplaySize.y));
        ImGui::Begin("menu_frame", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        // Logo and title
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::PushFont(largeFont); // Use the larger font
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("SYMANTEC").x) * 0.5f);
        ImGui::TextColored(ImVec4(0.11f, 0.64f, 0.92f, 1.0f), "SYMANTEC");
        ImGui::PopFont(); // Pop the larger font
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        float buttonWidth = ImGui::GetContentRegionAvail().x - 20.0f;
        float buttonHeight = 40.0f;
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10));

        // Menu buttons with icons
        if (ImGui::Button("  Home", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "home";
        }
        if (ImGui::Button("  Scanning", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "scanning";
        }
        if (ImGui::Button("  Updates", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "updates";
        }
        if (ImGui::Button("  Services", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "services";
        }
        if (ImGui::Button("  Settings", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "settings";
        }
        if (ImGui::Button("  Administration", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "administration";
        }
        if (ImGui::Button("  Console", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "console";
        }
        if (ImGui::Button("  About", ImVec2(buttonWidth, buttonHeight)))
        {
            active_frame = "about";
        }

        ImGui::PopStyleVar();

        // Version info at bottom
        float windowHeight = ImGui::GetWindowHeight();
        float textHeight = ImGui::CalcTextSize("Version 1.0.0").y;
        ImGui::SetCursorPosY(windowHeight - textHeight - 20);
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Version 1.0.0").x) * 0.5f);
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Version 1.0.0");

        ImGui::End();

        // Main content window
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.25f, 0));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.75f, io.DisplaySize.y));
        ImGui::Begin("main_frame", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        // Add a subtle gradient background
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 window_pos = ImGui::GetWindowPos();
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 gradient_start = window_pos;
        ImVec2 gradient_end = ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y);
        draw_list->AddRectFilledMultiColor(
            gradient_start,
            gradient_end,
            ImGui::GetColorU32(ImVec4(0.15f, 0.16f, 0.17f, 1.0f)),
            ImGui::GetColorU32(ImVec4(0.15f, 0.16f, 0.17f, 1.0f)),
            ImGui::GetColorU32(ImVec4(0.13f, 0.14f, 0.15f, 1.0f)),
            ImGui::GetColorU32(ImVec4(0.13f, 0.14f, 0.15f, 1.0f))
        );

        // Content padding
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

        if (active_frame == "home")
        {
            // Home page content
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::TextColored(ImVec4(0.11f, 0.64f, 0.92f, 1.0f), "Welcome to Symantec Antivirus");
            ImGui::PopFont();
            ImGui::Dummy(ImVec2(0.0f, 20.0f));
            
            // Status cards
            float cardWidth = (ImGui::GetContentRegionAvail().x - 20.0f) / 3.0f;
            float cardHeight = 120.0f;
            
            // Protection Status Card
            ImGui::BeginChild("protection_status", ImVec2(cardWidth, cardHeight), true);
            ImGui::TextColored(ImVec4(0.11f, 0.64f, 0.92f, 1.0f), "Protection Status");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Your system is protected");
            ImGui::Text("Last scan: Today");
            ImGui::EndChild();
            
            ImGui::SameLine();
            
            // Threats Card
            ImGui::BeginChild("threats", ImVec2(cardWidth, cardHeight), true);
            ImGui::TextColored(ImVec4(0.11f, 0.64f, 0.92f, 1.0f), "Threats");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("No threats detected");
            ImGui::Text("Last threat: Never");
            ImGui::EndChild();
            
            ImGui::SameLine();
            
            // Updates Card
            ImGui::BeginChild("updates", ImVec2(cardWidth, cardHeight), true);
            ImGui::TextColored(ImVec4(0.11f, 0.64f, 0.92f, 1.0f), "Updates");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Database is up to date");
            ImGui::Text("Last update: Today");
            ImGui::EndChild();
        }
        else if (active_frame == "scanning")
        {
            // Scanning page content
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::TextColored(ImVec4(0.11f, 0.64f, 0.92f, 1.0f), "Scanning Options");
            ImGui::PopFont();
            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            float buttonWidth = ImGui::GetContentRegionAvail().x / 2.0f - 10.0f;
            float buttonHeight = 60.0f;

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));

            // Scan buttons with improved styling
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
                active_frame = "scanning_custom_frame";
            }
            ImGui::SameLine();
            if (ImGui::Button("Scheduled Scan", ImVec2(buttonWidth, buttonHeight)))
            {
                // Handle Scheduled Scan logic
            }

            ImGui::PopStyleVar();

            ImGui::Dummy(ImVec2(0.0f, 20.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            if (ImGui::Selectable("View Scanning History"))
            {
                // Handle Scanning History logic
            }
        }
        else if (active_frame == "scanning_custom_frame")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Custom Scanning");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            static char directory_path[128] = "";

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::InputTextWithHint("##directory_path", "Enter file path here", directory_path, sizeof(directory_path));

            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            if (ImGui::Button("Browse", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                BROWSEINFO bi = {0};
                bi.lpszTitle = TEXT("Select Directory");
                LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

                if (pidl != NULL)
                {
                    wchar_t path[MAX_PATH];
                    if (SHGetPathFromIDListW(pidl, path))
                    {
                        wcstombs(directory_path, path, sizeof(directory_path));
                    }
                    CoTaskMemFree(pidl);
                }
            }

            if (ImGui::Button("Start scanning", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                if (strlen(directory_path) == 0)
                {
                    ImGui::OpenPopup("Error");
                }
                else
                {
                    try
                    {
                        app::core::scanner::signature_scanner::SignatureScanner signature_scanner;

                        std::string directory_path_str = directory_path;
                        std::vector<app::models::signature::Signature> signatures_scanned = signature_scanner.scanDirectory(directory_path_str, app::models::signature::HashAlgorithm::SHA256);

                        if (signatures_scanned.empty())
                        {
                            // No signatures found
                        }
                        else
                        {
                            std::ostringstream oss;
                            for (const auto &signature : signatures_scanned)
                            {
                                session.setVariable("signature", signature.getHashString(), true);

                                oss << "Signature scanned: " << signature.getHashString() << "\n";
                            }
                            consoleBuffer.buffer << oss.str();

                            app::models::signature::Signature db_signature;
                            std::vector<std::map<std::string, std::string>> signatures_vect = db_signature.allAsVector();
                            std::vector<std::pair<std::string, std::string>> session_signatures = session.getVariableVector("signature");
                            for (const auto &signature : signatures_vect)
                            {
                                auto it = std::find_if(session_signatures.begin(), session_signatures.end(),
                                                       [&signature](const std::pair<std::string, std::string> &pair)
                                                       {
                                                           return pair.second == signature.at("value");
                                                       });
                                if (it != session_signatures.end())
                                {
                                    app::models::logs::Logs log("Signature Scanner", "Signature found in database: " + signature.at("value"), app::models::logs::INFO);
                                    consoleBuffer.buffer << "Signature found in database: " << signature.at("value") << "\n";

                                    ImGui::OpenPopup("signature_found_alert");
                                }
                            }
                        }
                    }
                    catch (const std::exception &e)
                    {
                        app::models::logs::Logs log("Signature Scanner", "Error: " + std::string(e.what()), app::models::logs::ERROR);
                        consoleBuffer.buffer << "Error: " << e.what() << "\n";
                    }
                }
            }

            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopup("Error"))
            {
                ImGui::Text("Error: Please enter a valid directory path.");
                if (ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("signature_found_alert", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Signature found in database!");
                ImGui::Separator();

                if (ImGui::Button("Close", ImVec2(120, 0)))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
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
                    size_t convertedChars = 0;
                    wcstombs_s(&convertedChars, signature_hash, sizeof(signature_hash), szFile, _TRUNCATE);
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

                    try
                    {
                        db.execute_query("INSERT INTO signatures (name, description, value, algorithm, hash) VALUES (?, ?, ?, ?, ?)",
                                         {signature.getName(), signature.getDescription(), signature.getHashString(), signature.getAlgorithmString(), "0x" + signature.getAlgorithmString()});
                    }
                    catch (const std::exception &e)
                    {
                        app::models::logs::Logs log("Signature Scanner", "Failed to add signature to database: " + std::string(e.what()), app::models::logs::ERROR);
                        ImGui::OpenPopup("Error");
                    }

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
        else if (active_frame == "administration_database_signatures_load")
        {
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
                    ImGui::Text("Signature #%s: %s", signature.at("id").c_str(), signature.at("value").c_str());
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

        ImGui::PopStyleVar(); // Pop the window padding style

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