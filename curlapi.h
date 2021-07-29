#ifndef __CAPI
#define __CAPI
#include <iostream>
#include <curl/curl.h>
class CurlAPI{
    public:
        CurlAPI();
        ~CurlAPI();
        std::string download(std::string url);
    private:
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        CURL* curl;
};

#endif