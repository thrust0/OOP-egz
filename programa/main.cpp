#include "globals.hpp"

/*
TODO:
readme
*/

int main()
{
    std::locale::global(std::locale("lt_LT.UTF-8"));

    std::map<std::string, int> words;                       //map for duplicate words
    std::map<std::string, std::set<int>> location;          //cross reference table which stores the line where the duplicate words are
    std::set<std::string> links;

    file_input(words, location, FILE_PATHS.at(0), FILE_PATHS.at(4), links);
    word_count_output(words, FILE_PATHS.at(1));
    cross_reference_table_output(location, words, FILE_PATHS.at(2));
    url_output(links, FILE_PATHS.at(3));
    return 0;
}

