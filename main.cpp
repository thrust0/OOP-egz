#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>

const std::vector<std::string> FILE_PATHS = {
    "input/sample.txt",
    "output/output.txt"
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

/*
TODO:

*/

void file_input(std::map<std::string, int>& words, const std::string filename);
void file_output(const std::map<std::string, int>& words, const std::string filename);

int main()
{
    std::map<std::string, int> words;
    file_input(words, FILE_PATHS.at(0));
    file_output(words, FILE_PATHS.at(1));
    return 0;
}

void file_input(std::map<std::string, int>& words, const std::string filename)
{
    std::ifstream ist {filename};
    if(!ist)
    {
        throw std::runtime_error("Neisejo atidaryti failo irasymui...");
        return;
    }
    std::string line;
    while(std::getline(ist, line))
    {
        std::stringstream ss{line};

        for(std::string temp; ss >> temp;)
        {
            for(int i = 0; i < temp.size(); i++)
            {
                for(int j = 0; j < punctuation.size(); j++)
                {
                    if(temp[i] == punctuation.at(j))
                        temp.erase(i);
                }
            }
            ++words[temp]; 
        }
    }
    ist.close();
}

void file_output(const std::map<std::string, int>& words, const std::string filename)
{
    std::ofstream ost{filename};
    if(!ost)
    {
        throw std::runtime_error("Neisejo atidaryti failo irasymui!");
        return;
    }

    for(const auto& [key, value] : words)
        if(value > 0)
            ost << key << ": " << value << "\n";
    
}