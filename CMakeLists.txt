# Cmake
cmake_minimum_required(VERSION 3.0)
project(mysql_test)
set(CMAKE_CXX_STANDARD 20)

#openssl
set(OPENSSL_ROOT_DIR "/opt/homebrew/Cellar/openssl@1.1/1.1.1o/")
find_package(OpenSSL REQUIRED)


# Mysql
set(MYSQL_DIR PATHS "/usr/local/mysql-connector-c++-8.0.29/include")
find_library(MYSQL_LIBS NAMES mysqlcppconn-static PATHS /usr/local/mysql-connector-c++-8.0.29/lib64)

#json
set(JSON_DIR PATHS "/opt/homebrew/opt/jsoncpp")
include_directories(${JSON_DIR}/Include/json)


# Mysql-Test
add_executable(mysql_test)

#SHA256
add_library(sha256
        SHA256/sha256.cpp
        )
target_include_directories(sha256 PUBLIC "${PROJECT_SOURCE_DIR}/Header-files")

target_sources(mysql_test PRIVATE main.cpp)

target_include_directories(mysql_test PRIVATE "${MYSQL_DIR}")


target_link_libraries(mysql_test PRIVATE sha256)
target_link_libraries(mysql_test PRIVATE ${MYSQL_LIBS})
target_link_libraries(mysql_test PRIVATE resolv)
target_link_libraries(mysql_test PRIVATE OpenSSL::SSL)
target_link_libraries(mysql_test PRIVATE /opt/homebrew/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib)
target_compile_definitions(mysql_test PRIVATE RESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/Database\")