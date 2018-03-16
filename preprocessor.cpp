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
    std::ifstream infile;
    infile.open(this->file_handle.c_str(), std::ios::in);

    if (!infile.is_open())
    {
        throw this->file_handle;
    }
	
	char lexical_unit;
	std::vector<char> line;

	line.clear();

    while(infile>>std::noskipws>>lexical_unit)
    {
		// break about semicolons
		if (lexical_unit == ';')
		{
			line.push_back(lexical_unit);
			this->processed_file.push_back(std::string(line.begin(), line.end()));
			line.clear();
		}
		
		// break about blocks
		else if (lexical_unit == '{' || lexical_unit == '}')
		{
			if (!line.empty())
			{
				this->processed_file.push_back(std::string(line.begin(),line.end()));
				line.clear();
			}

			line.push_back(lexical_unit);
			this->processed_file.push_back(std::string(line.begin(), line.end()));
			line.clear();
		}

		else
			line.push_back(lexical_unit);
    }
	
	// remove leading and trailing spaces and tabs
	for (int idx=0; idx < this->processed_file.size(); idx++)
	{
		boost::trim(this->processed_file[idx]);
		boost::trim_if(this->processed_file[idx], boost::is_any_of("\t"));
	}
	
	// remove empty lines from the vector
	for (int idx=0; idx < this->processed_file.size();)
		if (this->processed_file[idx].length() == 0)
			this->processed_file.erase(this->processed_file.begin() + idx);
		else
			idx++;

    return this->processed_file;
}
