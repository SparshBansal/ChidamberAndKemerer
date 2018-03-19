#ifndef __ANALYSER_H_INCLUDED__
#define __ANALYSER_H_INCLUDED__


#include "class_information_package.h"
#include "reg_expressions.h"
#include "types.h"

#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stack>
#include <map>

class analyser
{
	private:
		std::vector<Class_Information_Package*> package_list;
		std::vector<std::string> file;

	public:
		analyser();
		analyser(std::vector<std::string> file);
		
		// getter methods 
		std::vector<Class_Information_Package*> get_package_list();
		std::vector<std::string> get_file();
		
		// setter methods
		void set_file(std::vector<std::string> file);

		// analyse
		std::vector<Class_Information_Package*> analyse();
};

#endif
