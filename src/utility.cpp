#include "utility.h"
#include <string>
#include <vector>

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& cmd) {
    std::vector<char*> charVector;
    
    for (const std::string& str : cmd) {
        char* cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
        charVector.push_back(cstr);
    }
    return charVector;
}

// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string& command, char delimiter = ' ') {
    std::string newWord = "";
    std::vector<std::string> list;
    for (const char ch : command) {
        if(ch == ' ') {
            list.push_back(newWord);
            newWord = "";
        }
        else
            newWord += ch;
    }
    if (!newWord.empty()) 
        list.push_back(newWord);
    return list;
}