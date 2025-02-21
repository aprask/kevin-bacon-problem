#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include "rapidjson/include/rapidjson/document.h"

#define ARGS 4

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
std::string req_hand(const std::string& name, std::string url);
void parse_json(const std::string& res_bod, std::vector<std::string>* res_buffer);
void traverseGraph(const std::string& name, const size_t& depth, std::vector<std::string> urls);

int main(int argc, char** argv) {
    if (argc != ARGS) {
        std::cerr << "Entered <" << argc << ">. Expected <" << ARGS << ">" << std::endl;
        return 1;
    }
    std::string param = "%20";
    const std::string name = argv[1] + param + argv[2];
    const size_t depth = std::stol(argv[3]);
    std::string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/";
    std::vector<std::string> urls;
    urls.push_back(url);
    traverseGraph(name, depth, urls);
    return 0;
}

void traverseGraph(const std::string& name, const size_t& depth, std::vector<std::string> urls) {
    int i = 0;
    std::vector<std::string> res_buffer;
    std::string out;
    int k;
    int j;
    urls[0] = urls[0] + name;
    while (i < depth) {
        for (k = 0; k < urls.size(); ++k) {
            out = req_hand(name, urls[k]);
            parse_json(out, &res_buffer);
            for (j = 0; j < res_buffer.size(); ++j) {
                std::cout << res_buffer[j] << std::endl;
            }
            std::cout << std::endl;
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

std::string req_hand(const std::string& name, std::string url) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to make handle" << std::endl;
        exit(1);
    }
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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