#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

#include "semaphore.hpp"
#include "threads.h"
#include "curlapi.h"
#include "regex.h"

void ThreadAPI::set_threads_number(int threads_number){//maximum semaphore value setter
    this->threads_number=threads_number;
    this->m_value=threads_number;
}
