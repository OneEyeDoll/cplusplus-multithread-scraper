#ifndef __TAPI
#define __TAPI
#include <thread>
#include <vector>

#include <pthread.h>
#include "semaphore.hpp"
/* Inheriting semaphore properties. Before starting thread, call the set_semaphore_value function*/
class ThreadAPI:semaphore{
    public:
        void set_threads_number(int threads_number);//setter for the threads number. used in semaphore
        template<typename T> //method to start a thread function
            void start_thread(T func,//function to be parallelized
            std::string args//arguments of the function
            ){
                std::thread to_detach(func,args);
                to_detach.detach();
            };
        private:
        bool isStart=true;
        std::vector<std::thread> allThreads;
        int threads_number;//maximum semaphore number
        std::vector<std::string> already_seen;
};

#endif