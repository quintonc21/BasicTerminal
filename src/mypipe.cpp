 //mypipe.h
 #include "mypipe.h"
 #include <string>
 #include <array>
 #include <unistd.h>
 #include <sys/wait.h>
#include <iostream>
 // Class mypipe provides a simple wrapper around a Unix pipe,
 // allowing redirection of standard output and capturing of output via read()
 
// Constructor: Creates a unidirectional pipe using pipe().
// pipe() initializes two file descriptors: fd[0] for reading, fd[1] for writing.
mypipe::mypipe() {
    pipe(&fd[0]);

}

// Destructor: Closes both ends of the pipe to release resources
mypipe::~mypipe() {
    close(fd[0]);
    close(fd[1]);
}

// redirect(): Redirects standard output (STDOUT) to the pipe's write end.
// This allows capturing output that would normally go to the console.
void mypipe::redirect(){
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

// read(): Reads data from the pipe's read end and returns it as a std::string.
// Typically used to capture the output that was redirected into the pipe.
std::string mypipe::read() {
    std::array<char, 256> buf;
    
    std::size_t bytes;
    bytes = ::read(fd[0], buf.data(), buf.size());
    if(bytes > 0)
    return std::string(buf.data(), bytes);
    else
    return std::string();
}
 