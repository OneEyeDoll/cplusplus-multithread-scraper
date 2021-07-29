scraper:
	g++ main.cpp regex.cpp  tests.cpp curlapi.cpp threads.cpp semaphore.cpp scraper.cpp -lpthread -lcurl -o scraper.o