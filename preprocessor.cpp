#include "preprocessor.h"

preprocessor::preprocessor(std::string file_handle)
{
    this->file_handle = file_handle;
    this->processed_file.clear();
}

preprocessor::preprocessor()
{
    preprocessor("");
}


// getter methods
std::string preprocessor::get_file_handle()
{
    return this->file_handle;
}

// setter methods
void preprocessor::set_file_handle(std::string file_handle)
{
    // set file handle and invalidate processed file
    this->file_handle = file_handle;
    this->processed_file.clear();
    return;
}

std::vector<std::string> preprocessor::process_file()
{
    // if null file_handler throw an error
    if (this->file_handle.empty())
    {
        throw file_handle;
    }

    // preprocess  the file
    // Steps to preprocess the file --
    // 1. read the file 

    
}