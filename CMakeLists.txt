cmake_minimum_required(VERSION 3.30)
project(terminal_todo)

set(CMAKE_CXX_STANDARD 20)

add_executable(terminal_todo 
        main.cpp 
        Config/ConfigFile.cpp
        Curl/Curl.cpp
)

find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(terminal_todo nlohmann_json::nlohmann_json)
target_link_libraries(terminal_todo CURL::libcurl)