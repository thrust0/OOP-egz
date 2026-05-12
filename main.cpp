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
TODO:
nx kazkaip atkopijuot ta temp string kad patikrint tld
wstring
url funkcionalumas:
    patikrint:
    bet kokie slashai po TLD pvz vu.lt/pagalba/lt/
makefile
readme
refractoring failus



*/
const std::vector<std::string> FILE_PATHS = {
    "input/sample.txt",
    "output/output.txt",
    "output/cross-reference-table.txt",
    "output/url-list.txt",
    "input/tld_list.txt"
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

int main()
{
    std::map<std::string, int> words;                       //map for duplicate words
    std::map<std::string, std::set<int>> location;          //cross reference table which stores the line where the duplicate words are
    std::set<std::string> links;

    file_input(words, location, FILE_PATHS.at(0), FILE_PATHS.at(4), links);
    word_count_output(words, FILE_PATHS.at(1));
    cross_reference_table_output(location, words, FILE_PATHS.at(2));
    url_output(links, FILE_PATHS.at(3));
    return 0;
}

void file_input(std::map<std::string, int>& words, std::map<std::string, std::set<int>>& location, const std::string filename, const std::string url_file, std::set<std::string>& links)
{
    std::ifstream ist {filename}; //source file of text
    std::ifstream url {url_file};
    if(!ist)
    {
        throw std::runtime_error("Neisejo atidaryti failo irasymui...");
        return;
    }

    if(!url)
    {
        throw std::runtime_error("Neisejo atidaryti url failo");
        return;
    }

    std::set<std::string> tld_set;
    std::string line;
    while(url >> line)
        tld_set.insert(line);
    
    line.clear();
    int line_count = 1;

    while(std::getline(ist, line))      
    {
        std::stringstream ss{line};

        for(std::string temp; ss >> temp;)                  //split words in line
        {
            if(is_link(temp, tld_set))
                links.insert(temp);
            else
            {
                normalize_word(temp);
                ++words[temp]; 
                location[temp].insert(line_count);
            }
            
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

std::string normalize_word(std::string temp)
{
    for(int i = 0; i < temp.size(); i++)            //iterate through the word
    {
        if(std::isupper(temp[i]))                   //check if character ir uppercase, if yes -> make it lower case
            temp[i] = std::tolower(temp[i]);
                
        for(int j = 0; j < punctuation.size(); j++)         //remove punctuation
        {
            if(temp[i] == punctuation.at(j))
            {    
                temp.erase(i);
                i--;
                break;
            }   
        }
    }
    return temp;
}
bool is_link(std::string word, std::set<std::string>& tld_set)
{
    std::string temp;

    for(int i = 0; i < 8; i++)          //pachekinam ar pradzia https ar www, jei jo tai iskart return true
    {
        temp += word[i];
        for(auto x : url_start)
            if(temp == x)
                return true;
        
    }

    auto it = word.find('.');
    if(it == std::string::npos)
        return false;
    
    std::string tld = word.substr(it + 1);
    for(int i = 0; i < tld.size(); i++)
        tld[i] = toupper(tld[i]);

    if(tld_set.find(tld) != tld_set.end())
        return true;

    return false;                           //nieko neradom tai false
}

void url_output(const std::set<std::string>& links, const std::string filename)
{
    std::ofstream ost{filename};
    if(!ost)
    {
        throw std::runtime_error("Neisejo atidaryti failo url outputui...");
        return;
    }

    for(auto p = links.begin(); p!=links.end(); ++p)
        ost << *p << "\n";
    ost.close();
}