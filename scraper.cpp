#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "scraper.h"
#include "curlapi.h"
#include "regex.h"
#include "threads.h"

std::mutex mtx;//mutex for critical section
std::vector<std::string> already_seen;//already seen filenames, skipped in download
semaphore sem;//semaphore
void Scraper::set_initial_url(std::string url){
    this->url=url;
}
void Scraper::set_threads_number(int threads){
    this->threads=threads;
    sem.set_threads_number(threads);
}
void Scraper::start_scraping(){
    CurlAPI capi;//curl interface instance
    std::string body;//response body
    std::string filename;//name of the file
    std::ofstream out;//output file stream
    RegexSearch rgxsrc;//regex search instance
    std::vector<std::string> other_urls;
    ThreadAPI tapi;//thread api instance
    //first request 
    body=capi.download(this->url);
    //check if request is succesful
        if(body!=""){
            filename="index.html";
            if(std::find(already_seen.begin(),already_seen.end(),filename)==already_seen.end())
            {
                        already_seen.push_back(filename);//adding file to blacklist
                //response output to file

                        out.open("scraped/"+filename);
                        out<<body;
                        out.close();
                //regex url search
                        rgxsrc.set_regex_pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
                        other_urls=rgxsrc.search(body);

                        for(auto url_new:other_urls){
                            sem.down();//semaphore acquire
                            tapi.start_thread<void(std::string)>(
                        Scraper::scraping_function,url_new
                    );

                    }
            }
        }
    }
void Scraper::scraping_function(std::string url){
    std::ofstream out;//output file stream
    std::string body;//response body
    CurlAPI capi;//capi instance
    std::string to_be_added;//string to be added to array
    std::vector<std::string> splitted_url;
    std::string filename;//file name
    std::istringstream url_stream(url);//string stream

    body=capi.download(url);//fetch of the content

    //check if request is ok
    if(body!=""){
        while (std::getline(url_stream, to_be_added, '/')) {
            splitted_url.push_back(to_be_added);
        }
        filename=splitted_url[splitted_url.size()-1];

                //entering critical section
                    mtx.try_lock();//critical section enter
                    already_seen.push_back(filename);//adding file to blacklist
                    mtx.unlock();//critical section exit
                //response output to file

                    out.open("scraped/"+filename);
                    out<<body;
                    out.close();

    }
    sem.up();//semaphore release
}