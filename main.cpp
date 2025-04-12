#include "main.h"

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && std::string(argv[1]) == "-help")
    {
        std::cout << "Scripts:" << std::endl;
        std::cout << "  -clean\tClean configuration" << std::endl;
        std::cout << "  -dotenvVerify\t\tVerify if .env file exists" << std::endl;
        std::cout << "  -dotenvGenerate\tGenerate .env file" << std::endl;
        std::cout << std::endl;
        std::cout << "Database:" << std::endl;
        std::cout << " Raw:" << std::endl;
        std::cout << "  -dbVerifyRawConnection\t<file>\tVerify raw database connection" << std::endl;
        std::cout << "  -dbCreateRawDatabase\t\t<file>\tCreate raw database" << std::endl;
        std::cout << std::endl;
        std::cout << " SQLite:" << std::endl;
        std::cout << "  -dbVerifySQLiteConnection\t<file>\tVerify SQLite database connection" << std::endl;
        std::cout << "  -dbCreateSQLiteDatabase\t<file>\tCreate SQLite database" << std::endl;
        std::cout << std::endl;
        std::cout << "File Signature:" << std::endl;
        std::cout << "  -getFileSignature1\t<file>\tGet SHA1 signature of the file" << std::endl;
        std::cout << "  -getFileSignature224\t<file>\tGet SHA224 signature of the file" << std::endl;
        std::cout << "  -getFileSignature256\t<file>\tGet SHA256 signature of the file" << std::endl;
        std::cout << "  -getFileSignature384\t<file>\tGet SHA384 signature of the file" << std::endl;
        std::cout << "  -getFileSignature512\t<file>\tGet SHA512 signature of the file" << std::endl;
        return 0;
    }

    if (argc < 2)
    {
        Scripts::initConfiguration();
        Scripts::setupSchema();

        // glfwSetErrorCallback(glfw_error_callback);
        // if (!glfwInit())
        //     return 1;

        // const char *glsl_version = "#version 130";
        // GLFWwindow *window = glfwCreateWindow(800, 600, "Dear ImGui Example", NULL, NULL);
        // if (window == NULL)
        //     return 1;
        // glfwMakeContextCurrent(window);
        // glfwSwapInterval(1);

        // IMGUI_CHECKVERSION();
        // ImGui::CreateContext();
        // ImGuiIO &io = ImGui::GetIO();
        // (void)io;

        // ImGui::StyleColorsDark();

        // ImGui_ImplGlfw_InitForOpenGL(window, true);
        // ImGui_ImplOpenGL3_Init(glsl_version);

        // bool show_window = true;
        // int counter = 0;

        // while (!glfwWindowShouldClose(window))
        // {
        //     glfwPollEvents();

        //     ImGui_ImplOpenGL3_NewFrame();
        //     ImGui_ImplGlfw_NewFrame();
        //     ImGui::NewFrame();

        //     if (show_window)
        //     {
        //         ImGui::Begin("Hello, world!", &show_window);

        //         ImGui::Text("This is a simple counter:");
        //         if (ImGui::Button("Increment"))
        //             counter++;

        //         ImGui::SameLine();
        //         ImGui::Text("Counter = %d", counter);

        //         ImGui::End();
        //     }

        //     ImGui::Render();
        //     int display_w, display_h;
        //     glfwMakeContextCurrent(window);
        //     glfwGetFramebufferSize(window, &display_w, &display_h);
        //     glViewport(0, 0, display_w, display_h);
        //     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //     glClear(GL_COLOR_BUFFER_BIT);
        //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //     glfwSwapBuffers(window);
        // }

        // ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        // ImGui::DestroyContext();

        // glfwDestroyWindow(window);
        // glfwTerminate();

        return 0;
    }

    std::string command = argv[1];
    std::string file = (argc > 2) ? argv[2] : "";

    Scanner::SignatureScanner scanner;

    if (command == "-clean")
    {
        Scripts::cleanConfiguration();
        return 0;
    }
    else if (command == "-dotenvVerify")
    {
        if (Scripts::verify_env_file_exists())
        {
            Models::Log log(Models::INFO, "dotenvVerify", "The .env file exists.");
            std::cout << log << std::endl;
        }
        else
        {
            Models::Exception exception("dotenvVerify", "The .env file does not exist.");
            std::cout << exception << std::endl;
        }
    }
    else if (command == "-dotenvGenerate")
    {
        Scripts::generate_dot_env();
    }
    else if (command == "-dbVerifyRawConnection" || command == "-dbCreateRawDatabase")
    {
        if (file.empty())
        {
            Models::Exception exception("dbVerifyRawConnection", "The <file> parameter is required.");
            std::cout << exception << std::endl;
            return 1;
        }
        Database::RawDatabase db("localhost", "test.db", "user", "password", 0, Database::DatabaseType::Raw, file);
        if (command == "-dbVerifyRawConnection")
        {
            db.verifyConnection();
        }
        else
        {
            db.createDatabase();
        }
    }
    else if (command == "-dbVerifySQLiteConnection" || command == "-dbCreateSQLiteDatabase")
    {
        if (file.empty())
        {
            Models::Exception exception("dbVerifySQLiteConnection", "The <file> parameter is required.");
            std::cout << exception << std::endl;
            return 1;
        }
        Database::SQLiteDatabase db("localhost", "test.db", "user", "password", 0, Database::DatabaseType::SQLite, file);
        if (command == "-dbVerifySQLiteConnection")
        {
            db.verifyConnection();
        }
        else
        {
            db.createDatabase();
        }
    }
    else if (command == "-getFileSignature1" || command == "-getFileSignature224" ||
             command == "-getFileSignature256" || command == "-getFileSignature384" ||
             command == "-getFileSignature512")
    {
        if (file.empty())
        {
            Models::Exception exception(command, "The <file> parameter is required.");
            std::cout << exception << std::endl;
            return 1;
        }

        Scanner::Signature signature;
        if (command == "-getFileSignature1")
        {
            signature = scanner.getFileSignatureSHA1(file);
        }
        else if (command == "-getFileSignature224")
        {
            signature = scanner.getFileSignatureSHA224(file);
        }
        else if (command == "-getFileSignature256")
        {
            signature = scanner.getFileSignatureSHA256(file);
        }
        else if (command == "-getFileSignature384")
        {
            signature = scanner.getFileSignatureSHA384(file);
        }
        else if (command == "-getFileSignature512")
        {
            signature = scanner.getFileSignatureSHA512(file);
        }
        std::cout << command.substr(13) << " Signature: " << signature << std::endl;
    }
    else
    {
        Models::Exception exception(command, "Unknown command.");
        std::cout << exception << std::endl;
        return 1;
    }

    return 0;
}