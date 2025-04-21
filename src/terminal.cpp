#include "terminal.h"
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include "utility.h"


// run_cmd:
// Takes a vector of C-style strings (char*), representing the command and its arguments.
// Forks a child process, redirects its standard output, and executes the command.
// Captures the output using a custom pipe (mypipe) and prints it to the terminal.
// Returns 0 on success, non-zero on failure.
int run_cmd(std::vector<char*> argv) {
    
    if (argv.empty()) {
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[0], argv.data());
        perror("exec failed");
        exit(127);
    }
    int status{0};
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return 1;
    }
    return status;
}

// terminal_app:
// Implements a simple interactive terminal loop.
// Continuously prompts the user for input, parses it into command and arguments,
// and executes the command using run_cmd().
// Exits the loop when the user types "exit".
void terminal_app() {
    std::string input;

    while (true) {
        std::cout << "terminal> ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        if (input == "exit") break;

        std::vector<std::string> args = cmd2vec(input);
        std::vector<char*> c_args = castArgs(args);
        c_args.push_back(nullptr); 

        run_cmd(c_args);

        for (char* arg : c_args) {
            delete[] arg;
        }
    }
}