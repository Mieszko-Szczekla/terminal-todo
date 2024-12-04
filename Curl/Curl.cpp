#include "Curl.h"

#include <iostream>

size_t Curl::writeData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    static_cast<std::string*>(userdata) -> append(ptr, size * nmemb);
    return size * nmemb;
}

void Curl::curlTodosInto(std::string &readBuffer, const std::string &url, const std::string &api_key)
{
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    
    if(!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        exit(-3);
    }

    std::string headers = "Authorization: Bearer ";
    headers += api_key;
    
    struct curl_slist *header = NULL;
    header = curl_slist_append(header, headers.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    try {
        res = curl_easy_perform(curl);
    } catch (std::exception& e) {
        std::cerr << "Failed to perform curl request" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
    
    curl_easy_cleanup(curl);
}