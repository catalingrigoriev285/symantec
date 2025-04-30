#include "main.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
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
            ImGui::InputTextWithHint("##signature_hash", "Enter hash here", signature_hash, ImGui::GetContentRegionAvail().x);
            ImGui::SameLine();

            static const char* signature_algorithm[] = {
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA1),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA224),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA256),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA384),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA512)
            };

            static int selectedType = 0;
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::Combo("##signature_algorithm", &selectedType, signature_algorithm, IM_ARRAYSIZE(signature_algorithm));

            if (ImGui::Button("Save", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                // Handle Add Signature logic
            }
        }
        else if (active_frame == "settings")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Logging System:");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            static bool enableFeature = false;
            ImGui::Checkbox("##EnableFeature", &enableFeature);
            ImGui::SameLine();
            ImGui::Text("Display logs in console");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            static bool enableFeature2 = false;
            ImGui::Checkbox("##EnableFeature2", &enableFeature2);
            ImGui::SameLine();
            ImGui::Text("Write logs in file");
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
                active_frame = "administration_database_add";
            }
        }
        else if(active_frame == "administration_database_add")
        {
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Text("Add a new signature to database");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            static char signature_hash[128] = "";
            ImGui::InputTextWithHint("##signature_hash", "Enter hash here", signature_hash, ImGui::GetContentRegionAvail().x);
            ImGui::SameLine();

            static const char* signature_algorithm[] = {
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA1),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA224),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA256),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA384),
                app::models::signature::HashAlgorithm_to_string(app::models::signature::HashAlgorithm::SHA512)
            };
            
            static int selectedType = 0;
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::Combo("##signature_algorithm", &selectedType, signature_algorithm, IM_ARRAYSIZE(signature_algorithm));

            if (ImGui::Button("Save", ImVec2(ImGui::GetContentRegionAvail().x, buttonHeight)))
            {
                // Handle Add Signature logic
            }
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

    return 0;
}