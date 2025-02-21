#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include "rapidjson/include/rapidjson/document.h"

#define ARGS 4

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
void req_hand(std::string& firstName, std::string& lastName, std::string* url);

int main(int argc, char** argv) {
    if (argc != ARGS) {
        std::cerr << "Entered <" << argc << ">. Expected <" << ARGS << ">" << std::endl;
        return 1;
    }

    std::string firstName = argv[1];
    std::string lastName = argv[2];
    size_t depth = std::stol(argv[3]);
    std::string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/";
    req_hand(firstName, lastName, &url);
    return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::string* str = (std::string*)userdata;
    for (size_t i = 0; i < nmemb; ++i) {
        str->push_back(ptr[i]);
    }
    return nmemb;
}

void req_hand(std::string& firstName, std::string& lastName, std::string* url) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to make handle" << std::endl;
        exit(1);
    }
    CURLcode response;
    *url = *url + firstName + "%20" + lastName;
    curl_easy_setopt(curl, CURLOPT_URL, url->c_str());
    std::string out;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &out);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    response = curl_easy_perform(curl);
    if (response) {
        std::cerr << "error: " << curl_easy_strerror(response) << std::endl;
        exit(1);
    }
    std::cout << out << std::endl;
    curl_easy_cleanup(curl);
}