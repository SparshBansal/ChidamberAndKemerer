#include "analyser.h"

analyser::analyser()
{
	this->file.clear();
	this->package_list.clear();
}

analyser::analyser(std::vector<std::string> file)
{
	this->file = file;
	this->package_list.clear();
}

std::vector<std::string> analyser::get_file()
{
	return this->file;
}

std::vector<Class_Information_Package> analyser::get_package_list()
{
	return this->package_list;
}

std::vector<Class_Information_Package> analyser::analyse()
{
	// analyse the preprocessed code
	if (this->file.empty())
	{
		throw this->file;
	}
	
	// the role of the class_map is to determine 
	// the classes we have encountered so far so 
	// as to find the accesses 
	std::map<std::string, int> class_map;

	// the role of the block stack is to determine the 
	// scope of the current class definition as well as 
	// method definition
	// Each element in the block stack is a pair of elements 
	//
	// First element defines the type of block -- class_block , function_block , code_block
	// Second element defines the scope of the block -- id of the scope 
	// Global scope is defined by id = -1;
	//
	std::stack<std::pair<int,int>> block_stack;
	block_stack.push({TYPE_CODE,-1});
	
	// create an empty class package
	Class_Information_Package package;
	
	// analyse code line by line
	for (std::string line : this->file)
	{
		// check for class definition
		std::regex class_def_regex(CLASS_DEF);
		if (std::regex_match(line,class_def_regex))
		{
			// extract groups
			
		}
	}

	return this->package_list;
}
