#include "curlapi.h"
#include <curl/curl.h>


CurlAPI::CurlAPI()//initializing the curl and easy curl
{
     curl_global_init(CURL_GLOBAL_SSL);
     this->curl=curl_easy_init();
}
CurlAPI::~CurlAPI(){
     curl_easy_cleanup(this->curl);
}
std::string CurlAPI::download(std::string url){
     CURLcode res;//result
     std::string readBuffer;//output buffer

     if(this->curl) {
     curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//setting the url
     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);//binding the function 
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);//fetching the content
     res = curl_easy_perform(curl);
     }
     return readBuffer;
}

size_t CurlAPI::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
