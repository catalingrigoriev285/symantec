cmake_minimum_required(VERSION 3.31.3)

project(symantec)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENSSL_ROOT_DIR "libs/openssl")
set(glfw3_DIR "libs/glfw3/share/glfw3/")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/sqlite)

find_package(OpenSSL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB IMGUI_SOURCES
    libs/imgui/*.cpp
    libs/imgui/backends/imgui_impl_glfw.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/libs/imgui
    ${CMAKE_CURRENT_LIST_DIR}/libs/imgui/backends
)

add_executable(${PROJECT_NAME} 
    app/main.cpp

    # modules
    app/modules/configuration/configuration.cpp
    app/modules/database/database.cpp
    app/modules/database/SQLite_Database/SQLite_Database.cpp
    app/modules/session/session.cpp

    # models
    app/models/model.cpp
    app/models/logs/logs.cpp
    app/models/signature/signature.cpp

    # core
    app/core/analytics/analytics.cpp
    app/core/scanner/signature_scanner/signature_scanner.cpp

    ${IMGUI_SOURCES}
)

target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto SQLiteCpp sqlite3 OpenGL::GL glfw)