#pragma once

#include <string>

class ConfigFile {
public:
    ConfigFile();
    std::string getApiKey() const;
    std::string getFilter() const;
private:
    std::string apiKey;
    std::string filter;
    std::string createLocation() const;
};