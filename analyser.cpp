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

std::vector<Class_Information_Package*> analyser::get_package_list()
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
	std::unordered_set<std::string> function_set;
	/* 
	 * the role of the block stack is to determine the 
	 * scope of the current class definition as well as 
	 * method definition
	 * Each element in the block stack is a pair of elements 
	
	 * First element defines the type of block -- class_block , function_block , code_block
	 * Second element defines the scope of the block -- id of the scope 
	 * Global scope is defined by id = -1;
	*/

	std::stack<std::pair<int,int>> block_stack;
	/*
	 * The purpose of package stack is to handle nested classes , we want to push the right methods 
	 * in the right class package
	 *
	 * */
	std::stack<Class_Information_Package*> package_stack;
	
	// initialize block stack
	block_stack.push({TYPE_CODE,-1});
	
	int last_statement_type = TYPE_CODE;

	// Initialize regular expressions 
	boost::regex class_def_regex(CLASS_DEF);
	boost::regex function_def_regex(FUNCTION_DEF);
	boost::regex block_open_regex(BLOCK_OPEN_DEF);
	boost::regex block_close_regex(BLOCK_CLOSE_DEF);


	// analyse code line by line
	for (std::string line : this->file)
	{
		boost::smatch matches;
		// check for class definition
		// if class definition is found
		if (boost::regex_match(line,matches,class_def_regex,boost::match_extra))
		{

			Class_Information_Package* package = new Class_Information_Package();
			package_stack.push(package);


			// extract groups
			// base class
			std::string base_class = matches[1];

			// create a new entry in the map if not there already
			const int _id = class_map.size();
			std::map<std::string,int>::iterator it = class_map.find(base_class);
			if (it == class_map.end())	
				class_map.insert({base_class,_id});
			else
				std::cout<<"Duplicate class exception\n";
			
			
			package->set_name(base_class);
			package->set_id(_id);

			std::vector<std::string> parents;
			std::vector<int> parents_id;

			// extract parent class information
			if (matches.size() > 2)  // optional inheritance expression exists
			{
				parents.push_back(matches[4]);
				
				if (matches.size() > 5) // extended inheritance list pattern exists
				{
					for (int i=0; i< matches.captures(matches.size()-1).size(); i++)
						parents.push_back(matches.captures(matches.size()-1)[i]);
				}
			}

			for (int i=0; i<parents.size(); i++)
			{
				if(class_map.find(parents[i])!=class_map.end())
				{
					const int parent_id = class_map[parents[i]];

					// add to package
					parents_id.push_back(parent_id);
					package->get_parents().push_back(parent_id);
				}
			}

			package->set_scope_id(block_stack.top().second);
			last_statement_type = TYPE_CLASS;
		}
		
		// if function definition is found
		else if (boost::regex_match(line,matches,function_def_regex))
		{
			// extract method name
			std::string function_name = matches[3];

			Class_Information_Package* cpackage = NULL;
			if (!package_stack.empty())
				cpackage = package_stack.top();
			
			// method belongs to a class 
			if (cpackage != NULL)
				cpackage->get_methods_set().insert(function_name);
			
			// method is in global scope
			else 
				function_set.insert(function_name);

			last_statement_type = TYPE_FUNCTION;
		}
		
		// if opening block is found
		else if (boost::regex_match(line, block_open_regex))
		{
			switch(last_statement_type)
			{
				case TYPE_CLASS:
					// push the scope of the latest class on the stack
					block_stack.push({TYPE_CLASS, package_stack.top()->get_id()});
					break;

				case TYPE_FUNCTION:
					// push the scope of the previous element
					block_stack.push({TYPE_FUNCTION, block_stack.top().second});
					break;

				case TYPE_CODE:
					// push the scope of the previous element
					block_stack.push({TYPE_CODE, block_stack.top().second});
					break;
			}
		}
		
		// if closing block is found 
		else if (boost::regex_match(line, block_close_regex))
		{
			switch(block_stack.top().first)
			{
				// end of a class is found
				case TYPE_CLASS:
					// add the package to the list of vectors
					package_list.push_back(package_stack.top());

					package_stack.pop();
					block_stack.pop();
					break;
				
				// end of function or code block
				case TYPE_FUNCTION:
				case TYPE_CODE:
					block_stack.pop();

			}
		}

	}

	return this->package_list;
}

