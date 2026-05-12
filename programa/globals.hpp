#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cctype>
#include <set>

const std::vector<std::string> FILE_PATHS = {
    "../input/sample.txt",
    "../output/output.txt",
    "../output/cross-reference-table.txt",
    "../output/url-list.txt",
    "../input/tld_list.txt"
};

const std::set<char> punctuation = {
    ',', 
    '.', 
    '!',
    ';',
    ':',
    '?',
    '(',
    ')',
    '{',
    '}',
    '[',
    ']',
    '"',
    '&'
};

const std::vector<std::string> url_start = {
    "http://",
    "https://",
    "www."
};

void file_input(std::map<std::string, int>& words, std::map<std::string, std::set<int>>& location, const std::string filename, const std::string url_file, std::set<std::string>& links);
void word_count_output(const std::map<std::string, int>& words, const std::string filename);
void cross_reference_table_output(const std::map<std::string, std::set<int>>& location, const std::map<std::string, int>& words, std::string filename);
std::string normalize_word(std::string temp);
void url_output(const std::set<std::string>& links, const std::string filename);
bool is_link(std::string word, std::set<std::string>& tld_set);
