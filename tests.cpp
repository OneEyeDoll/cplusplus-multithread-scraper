#include <iostream>
#include <fstream>

#include "curlapi.h"
#include "scraper.h"
#include "threads.h"
#include "regex.h"

void test_threading(){
    ThreadAPI threadapi;//thread interface
    threadapi.set_threads_number(1000);
    threadapi.start_thread<void(std::string)>(
            Scraper::scraping_function,"https://www.ansa.it"
        );
}

std::string test_curl(){
    std::ofstream fstream;//output stream
    CurlAPI curlapi;//curl wrapper class
    fstream.open("index.html");
    std::string body=curlapi.download("https://www.ansa.it");//downloading home page
    fstream<<body<<'\n';
    return body;
}

void test_regex(std::string value){//regex test
    std::ofstream fstream;
    fstream.open("entries_test.txt",std::ios_base::app);
    RegexSearch rgxsrc;//regex search wrapper class
    rgxsrc.set_regex_pattern("^[a-zA-Z0-9-_]+[:./\\\\]+([a-zA-Z0-9 -_./:=&\"'?%+@#$!])+$");
    for(auto value:rgxsrc.search(value))
        fstream<<value<<'\n';
}

void test_suite(){
    test_threading();
    //std::string test_curl_returned=test_curl();
    //test_regex(test_curl_returned);
}