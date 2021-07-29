#ifndef __RGX
#define __RGX
#include <iostream>
#include <vector>
class RegexSearch{
    public:
        void set_regex_pattern(std::string pattern);
        std::vector<std::string> search(std::string to_be_searched);
    private:
        std::string pattern;
};
#endif