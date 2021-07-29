#include "semaphore.hpp"
#include <iostream>
void semaphore::down()

{   
        // This locks the mutex until it is destroyed at method exit.
        std::unique_lock<std::mutex> lck(m_mux);
        // Check the mutex value, and wait if need be.
        if(--m_value < 0) {
                // Make us wait.  When we wait, the mutex is unlocked until the
                // wait ends.
                m_waitcond.wait(lck);
        }
}

/* Semaphore up operation. */
void semaphore::up(){
        // This locks the mutex until it is destroyed at method exit.
        std::unique_lock<std::mutex> lck(m_mux);
        // Start a waiting thread if required.
        if(++m_value <= 0) m_waitcond.notify_one();
}

void semaphore::set_threads_number(int threads){
        this->m_value=threads;
}