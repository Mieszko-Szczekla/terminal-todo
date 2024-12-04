#pragma once

#include <curl/curl.h>
#include <string>

namespace Curl {
    size_t writeData(char *ptr, size_t size, size_t nmemb, void *userdata);
    void curlTodosInto(std::string& readBuffer, const std::string& url, const std::string& api_key);
}