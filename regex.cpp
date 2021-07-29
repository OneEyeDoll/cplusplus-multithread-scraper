#include <regex>
#include "regex.h"

void RegexSearch::set_regex_pattern(std::string pattern){
    this->pattern=pattern;
}
std::vector<std::string>  RegexSearch::search(std::string to_be_searched){
    std::smatch m;
    std::vector<std::string> to_return;
    while (std::regex_search (to_be_searched,m,std::regex(this->pattern))) {
        for (auto x:m) to_return.push_back(x);
        to_be_searched = m.suffix().str();
  }

   return to_return;

}