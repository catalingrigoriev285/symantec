cmake_minimum_required(VERSION 3.31.3)

project(symantec)

set(OPENSSL_ROOT_DIR "libs/openssl")

find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)