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
	
}
