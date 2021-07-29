#ifndef __SCRP
#define __SCRP

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>


class Scraper{
    public:
        void set_initial_url(std::string url);//url setter
        void start_scraping();//scraper start
        static void scraping_function(std::string url);//thread scraping function
        void set_threads_number(int threads);//threads setter
    private:
        std::string url;//initial url
        int threads;//threads number
};

#endif