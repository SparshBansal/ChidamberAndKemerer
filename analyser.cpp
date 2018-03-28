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

std::vector<Class_Information_Package*> analyser::analyse()
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
	/* 
	 * the role of the block stack is to determine the 
	 * scope of the current class definition as well as 
	 * method definition
	 * Each element in the block stack is a pair of elements 
	
	 * First element defines the type of block -- class_block , function_block , code_block
	 * Second element defines the scope of the block -- id of the scope 
	 * Global scope is defined by id = -1;
	*/

	// function parameter map is used to keep track of the function
	// parameters
	std::map<std::string, int> function_parameter_map;

	std::stack<std::pair<int,int>> block_stack;
	/*
	 * The purpose of package stack is to handle nested classes , we want to push the right methods 
	 * in the right class package
	 *
	 * */
	std::stack<Class_Information_Package*> package_stack;
	
	// initialize block stack
	block_stack.push({TYPE_CODE,-1});
	
	// initialize the package stack with global package
	Class_Information_Package *global_package = new Class_Information_Package();
	global_package->set_id(-1);
	global_package->set_name("global");
	package_stack.push(global_package);
	
	int last_statement_type = TYPE_CODE;

	// Initialize regular expressions 
	boost::regex identifier_def_regex(IDENTIFIER_DEF);
	boost::regex class_def_regex(CLASS_DEF);
	boost::regex function_def_regex(FUNCTION_DEF);
	boost::regex member_def_regex(MEMBER_DEF);
	boost::regex member_access_regex(MEMBER_ACCESS_DEF);
	boost::regex block_open_regex(BLOCK_OPEN_DEF);
	boost::regex block_close_regex(BLOCK_CLOSE_DEF);


	// analyse code line by line
	for (std::string line : this->file)
	{
		std::cout<<"Analysing line : "<<line<<std::endl;
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
			
			
			// extract parameter info
			if (matches.size() > 5)
			{
				std::string type= matches[5];
				std::string parameter = matches[7];
				
				int parameter_type_idx = -2;
				
				if (class_map.find(type) != class_map.end())
					parameter_type_idx = class_map[type];
				else
					parameter_type_idx = -1;

				function_parameter_map.insert({parameter, parameter_type_idx});
			}
			
			// optional list is present
			if (matches.size() > 8)
			{
				int type_capture_idx = matches.size() - 3;
				int parameter_capture_idx = matches.size() -1;
				
				std::vector<int> parameter_type_vector;
				std::vector<std::string> parameter_name_vector;

				for (int i=0; i<matches.captures(type_capture_idx).size(); i++)
				{
					const std::string type = matches.captures(type_capture_idx)[i];
					if (class_map.find(type) != class_map.end())
						parameter_type_vector.push_back(class_map[type]);
					else
						parameter_type_vector.push_back(-1);
				}

				for (int i=0; i<matches.captures(parameter_capture_idx).size(); i++)
					parameter_name_vector.push_back(matches.captures(parameter_capture_idx)[i]);
				
				// insert into map
				for (int i=0; i<parameter_name_vector.size(); i++)
					function_parameter_map.insert({parameter_name_vector[i],parameter_type_vector[i]});

			}

			Class_Information_Package* cpackage = NULL;
			cpackage = package_stack.top();
			cpackage->get_methods_set().insert(function_name);
			
			last_statement_type = TYPE_FUNCTION;
		}
		
		// member definition found 
		else if (boost::regex_match(line,matches , member_def_regex, boost::match_extra))
		{
			std::string type_string = matches[1];
			std::vector<std::string> members;

			std::cout<<"Type string : "<<type_string<<std::endl;
		
			members.push_back(matches[3]);
			
			// more members have been defined
			if (matches.size()>2)
			{
				for (int i=0; i<matches.captures(matches.size()-1).size(); i++)
					members.push_back(matches.captures(matches.size()-1)[i]);
			}
			
			int class_type_id = -1;
			std::map<std::string,int> data_members = package_stack.top()->get_data_members();

			// 
			// check if a class object is found
			if (boost::regex_match(type_string , identifier_def_regex))
				class_type_id = class_map[type_string];
			else 
				class_type_id = TYPE_BASIC;

			
			// add the data members
			for (int i=0; i< members.size(); i++)
			{
				std::cout<<"adding data member : "<<members[i]<<" of type : " << class_type_id<<std::endl;
				package_stack.top()->add_member(members[i],class_type_id);
			}
		}
			
		// member access is found
		else if (boost::regex_search(line,matches, member_access_regex))
		{
			std::cout<<"Found member access\n";
			
			std::string instance = matches[1];
			std::cout<<"Member " << instance<<std::endl;
			std::map<std::string, int> member_map = package_stack.top()->get_data_members();
			// look for instance in class_map
			if (member_map.find(instance)!= member_map.end())
			{
				package_stack.top()->add_data_access(member_map[instance]);
				std::cout<<"Found in class";
			}
			else if (function_parameter_map.find(instance)!= function_parameter_map.end())
				package_stack.top()->add_data_access(function_parameter_map[instance]);
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
					function_parameter_map.clear();
				case TYPE_CODE:
					block_stack.pop();

			}
		}

	}

	// add global_package to the list
	package_list.push_back(package_stack.top());
	return this->package_list;
}

