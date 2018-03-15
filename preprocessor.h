#ifndef __PREPROCESSOR_H_INCLUDED__
#define __PREPROCESSOR_H_INCLUDED__

#include <fstream>
#include <string>
#include <vector>

class preprocessor
{
  private:
    std::string file_handle;
    std::vector<std::string> processed_file;

  public:

    // constructor
    preprocessor();
    preprocessor(std::string file_handle);

    // getter
    std::string get_file_handle();
    
    // setter
    void set_file_handle(std::string file_handle);

    // process file function 
    std::vector<std::string> process_file();
};

#endif