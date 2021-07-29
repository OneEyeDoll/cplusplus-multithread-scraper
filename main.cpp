
#include <iostream>
#include <string>
#ifndef WIN32
#include <unistd.h>
#endif
#include <pthread.h>
 
#include "argparse.h"
#include "threads.h"
#include "tests.h"
#include "scraper.h"
int main(int argc, const char** argv){
    ArgumentParser parser;//argument parser
    std::string usage;//usage string
    std::string domain;//domain to analyze
    Scraper scraper;
    int threads;//number of threads

    //app name setup to argparse lib

    parser.appName("MassScraper");

    //add arguments to the library, they will be retrieved later
    parser.addArgument("-t","--threads",1,false);
    parser.addArgument("-d","--domain",1,false);

    
    parser.parse(argc,argv);

    //retrieving required arguments
    domain=parser.retrieve<std::string>("d");
    threads=std::stoi(parser.retrieve<std::string>("t"));

    
    //validating args data
    if(domain==""){
        std::cout<<parser.usage();
    }
    else if(threads==NULL){
        std::cout<<parser.usage();
    }
    else if(threads>=1000){
        threads=1000;
    }
    #ifdef __TESTS
    test_suite();//tests
    #endif

    scraper.set_initial_url(domain);
    scraper.set_threads_number(threads);
    scraper.start_scraping();
    pthread_exit(0);//trick to mantain other threads alive


        
}