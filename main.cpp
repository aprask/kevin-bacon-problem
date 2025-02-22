#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include "rapidjson/include/rapidjson/document.h"

#define ARGS 4

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
std::string req_hand(std::string* url, std::string& name);
void parse_json(const std::string& res_bod, std::vector<std::string>* res_buffer);
void traverse_graph(const std::string& name, const size_t& depth, std::vector<std::string>& urls, std::string& url);

int main(int argc, char** argv) {
    if (argc != ARGS) {
        std::cerr << "Entered <" << argc << ">. Expected <" << ARGS << ">" << std::endl;
        return 1;
    }
    std::string name = argv[1];
    name = name + " " + argv[2];
    size_t depth = std::stol(argv[3]);
    std::string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/";
    // std::vector<std::string> urls;
    // urls.push_back(url);
    // traverse_graph(name, depth, urls, url);
    std::string o = req_hand(&url, name);
    std::cout << o << std::endl;
    return 0;
}

void traverse_graph(const std::string& name, const size_t& depth, std::vector<std::string>& urls, std::string& url) {
    int i = 0;
    std::vector<std::string> res_buffer;
    std::string out;
    int k;
    int j;
    while (i < depth) {
        std::cout << "made it" << std::endl;
        for (k = 0; k < urls.size(); ++k) {
            // out = req_hand(urls[k]);
            parse_json(out, &res_buffer);
        }
        for (k = 0; k < res_buffer.size(); ++k) {
        }
        res_buffer.clear();
        i++;
    }
}

void parse_json(const std::string& res_bod, std::vector<std::string>* res_buffer) {
    rapidjson::Document doc;
    doc.Parse(res_bod.c_str());
    bool res = doc.HasMember("neighbors");
    if (!res) {
        std::cout << "Cannot locate neighbors key" << std::endl;
        exit(1);
    }
    res = doc.HasMember("node");
    if (!res) {
        std::cout << "Cannot locate node key" << std::endl;
        exit(1);
    }
    res_buffer->push_back(doc["node"].GetString());
    const rapidjson::Value& neighbors = doc["neighbors"];
    for (size_t i = 0; i < neighbors.Size(); ++i) {
        res_buffer->push_back(neighbors[i].GetString());
    }
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::string* str = (std::string*)userdata;
    for (size_t i = 0; i < nmemb; ++i) {
        str->push_back(ptr[i]);
    }
    return nmemb;
}

std::string req_hand(std::string* url, std::string& name) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to make handle" << std::endl;
        exit(1);
    }
    CURLcode response;
    char* encoded_name = curl_easy_escape(curl, name.c_str(), name.size());
    if (encoded_name == NULL) {
        std::cerr << "Cannot encode url" << std::endl;
        exit(1);
    }
    *url = *url + encoded_name;
    curl_easy_setopt(curl, CURLOPT_URL, url->c_str());
    std::string out;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &out);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    response = curl_easy_perform(curl);
    if (response) {
        std::cerr << "error: " << curl_easy_strerror(response) << std::endl;
        exit(1);
    }
    curl_easy_cleanup(curl);
    return out;
}


/*
Structure
l1: HEAD
l2: HEAD's Movies
l3: Movie's actors
l4: Actor's movies
l5: Movie's actors
l6: Actor's movies
*/