#ifndef HTML_SCRAPE_H
#define HTML_SCRAPE_H

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <unordered_map>


  //"google": "https://scholar.google.com/scholar?q=%s&start=%d",
  //"arxiv": "search_query=%s&start=0&max_results=%d",
const std::unordered_map<std::string, std::string> databaseUrls = {
  {"google" , "https://scholar.google.com/scholar?q=%s"},
  {"arxiv" , "https://arxiv.org/search/?query=%s&searchtype=all"}
};

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    size_t totalSize = size * nmemb;
    userData->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string fetchHtml(std::string database, std::string& query) {
    std::string baseUrl = databaseUrls.at(database);
    char loadedUrl[1024];
    snprintf(loadedUrl, sizeof(loadedUrl), baseUrl.c_str(), query.c_str());

    CURL* curlHandle(curl_easy_init());
    if (!curlHandle) {
        throw std::runtime_error("Failed to initialize libcurl");
    }
    std::string response;

    curl_easy_setopt(curlHandle, CURLOPT_URL, loadedUrl);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    // Perform the request
    CURLcode res = curl_easy_perform(curlHandle);
    if (res != CURLE_OK) {
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    curl_easy_cleanup(curlHandle);

    return response;
}



#endif

