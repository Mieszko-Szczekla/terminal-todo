#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "Config/ConfigFile.h"
#include "Curl/Curl.h"

using json = nlohmann::json;



static void printTodos(const std::string& readBuffer) {
    try {
        json data = json::parse(readBuffer);
    
        for(json& task : data) {
            std::string name = task["content"];
            std::cout << name << std::endl;
        }
    } catch (nlohmann::detail::parse_error& e) {
        std::cerr << "Failed to parse json. API changed or you provided wrong details." << std::endl;
        exit(-2);
    }
}

int main() {
    ConfigFile config;

    const std::string url = std::string("https://api.todoist.com/rest/v2/tasks?filter=") + config.getFilter();
    const std::string api_key = config.getApiKey();

    std::string readBuffer;

    Curl::curlTodosInto(readBuffer, url, api_key);
    printTodos(readBuffer);
}