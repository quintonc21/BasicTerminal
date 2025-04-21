#include "utility.h"
#include <string>
#include <vector>

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& cmd) {
    std::vector<char*> argv;
    for (const auto& arg : cmd) {
    argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // null-terminate
    return argv;
}

// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string& command, char delimiter) {
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