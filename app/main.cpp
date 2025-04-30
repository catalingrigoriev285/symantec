#include "main.h"

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
            ImGui::Text("Protected");
        }
        else if (active_frame == "scanning")
        {
            ImGui::Text("Scanning Options:");
            ImGui::Dummy(ImVec2(0.0f, 10.0f)); // Add vertical spacing

            float buttonWidth = ImGui::GetContentRegionAvail().x / 2.0f - 5.0f; // Half width with spacing
            float buttonHeight = 50.0f;

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
            ImGui::Text("This is Frame 4.");
        }
        else if (active_frame == "settings")
        {
            ImGui::Text("This is Frame 5.");
        }
        else if (active_frame == "administration")
        {
            ImGui::Text("Administration Panel:");
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            if (ImGui::Selectable("Add a new signature to database"))
            {
                // Handle Scanning History logic
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