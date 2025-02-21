#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

struct memory {
    char *response;
    size_t size;
};  

int main(int argc, char** argv) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to make handle" << std::endl;
        exit(1);
    }
    CURLcode response;
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/");
    std::string out;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &out);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    response = curl_easy_perform(curl);
    if (response) {
        std::cerr << curl_easy_strerror(response) << std::endl;
        exit(1);
    }
    std::cout << out << std::endl;
    curl_easy_cleanup(curl);
    return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::string* str = (std::string*)userdata;
    for (size_t i = 0; i < nmemb; ++i) {
        str->push_back(ptr[i]);
    }
    return nmemb;
}