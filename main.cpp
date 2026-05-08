#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cctype>
#include <set>

/*
TODO
cross reference lentele
*/
const std::vector<std::string> FILE_PATHS = {
    "input/sample.txt",
    "output/output.txt",
    "output/cross-reference-table.txt"
};

const std::vector<char> punctuation = {
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
    '"'
};

void file_input(std::map<std::string, int>& words, std::map<std::string, std::set<int>>& location, const std::string filename);
void word_count_output(const std::map<std::string, int>& words, const std::string filename);
void cross_reference_table_output(const std::map<std::string, std::set<int>>& location, const std::map<std::string, int>& words, std::string filename);

int main()
{
    std::map<std::string, int> words;                       //map for duplicate words
    std::map<std::string, std::set<int>> location;          //cross reference table which stores the line where the duplicate words are
    file_input(words, location, FILE_PATHS.at(0));
    word_count_output(words, FILE_PATHS.at(1));
    cross_reference_table_output(location, words, FILE_PATHS.at(2));
    return 0;
}

void file_input(std::map<std::string, int>& words, std::map<std::string, std::set<int>>& location, const std::string filename)
{
    std::ifstream ist {filename};
    if(!ist)
    {
        throw std::runtime_error("Neisejo atidaryti failo irasymui...");
        return;
    }

    std::string line;
    int line_count = 1;

    while(std::getline(ist, line))
    {
        std::stringstream ss{line};

        for(std::string temp; ss >> temp;)
        {
            for(int i = 0; i < temp.size(); i++)
            {
                if(std::isupper(temp[i]))                   //check if character ir uppercase, if yes -> make it lower case
                    temp[i] = std::tolower(temp[i]);
                
                for(int j = 0; j < punctuation.size(); j++)         //remove punctuation
                {
                    if(temp[i] == punctuation.at(j))
                        temp.erase(i);
                }
            }
            ++words[temp]; 
            location[temp].insert(line_count);
        }
        ++line_count;
    }
    ist.close();
}

void word_count_output(const std::map<std::string, int>& words, const std::string filename)
{
    std::ofstream ost{filename};
    if(!ost)
    {
        throw std::runtime_error("Neisejo atidaryti failo irasymui!");
        return;
    }

    for(const auto& [key, value] : words)
        if(value > 1)
            ost << key << ": " << value << "\n";
        
}

void cross_reference_table_output(const std::map<std::string, std::set<int>>& location, const std::map<std::string, int>& words, std::string filename)
{
    std::ofstream ost{filename};
    if(!ost)
    {
        throw std::runtime_error("Neisejo atidaryti failo irasymui!");
        return;
    }

    for(const auto& [key, value] : words)
        if(value > 1)
        {
            auto location_value = location.find(key);
            ost << key << ": ";
            for(const auto& line : location_value->second)
                ost << line << " ";
            ost << "\n";
        }

}