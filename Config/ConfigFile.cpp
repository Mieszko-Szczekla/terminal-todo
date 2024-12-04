#include "ConfigFile.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

ConfigFile::ConfigFile()
{
    const std::string filename = createLocation();
    std::ifstream file(filename);
    if (!file.good())
    {
        std::ofstream newFile(filename);
        newFile << "# Fill the following fields. Do not use spaces in values.\napi_key: PLACE_KEY_HERE>\nfilter: today";
        newFile.close();
        std::cout << "Config file created. Please edit the file." << std::endl;
        exit(1);
    }

    std::string key;
    std::string value;

    for(std::string line; std::getline(file, line);)
    {
        std::string key, value;
        std::stringstream ss(line);
        ss >> key >> value;
        if (key[0] == '#')
        {
            continue;
        }
        else if (key == "api_key:")
        {
            apiKey = value;
        }
        else if (key == "filter:")
        {
            filter = value;
        }
        else 
        {
            std::cout << "Invalid key: " << key << std::endl;
        }
    }
}

std::string ConfigFile::getApiKey() const
{
    return apiKey;
}

std::string ConfigFile::getFilter() const
{
    return filter;
}

std::string ConfigFile::createLocation() const
{
    std::string location = "";
    location += std::getenv("HOME");
    location += "/.config/terminal-todo";
    const auto path = std::filesystem::path(location);
    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directories(path);
    }
    return location+"/config";
}
