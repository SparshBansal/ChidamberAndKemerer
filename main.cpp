#include "reg_expressions.h"
#include "preprocessor.h"
#include "analyser.h"
#include "c_and_k.h"

#include <iostream>
#include <boost/regex.hpp>

using namespace std;

void try_to_match(string query,string expression)
{
	boost::regex exp(expression);

    if (boost::regex_match(query, exp))
        cout<<"Regex found\n";
    else
        cout<<"Regex not found\n";
}

int main()
{
    string file_handle = "code.txt";

    // register logger
    auto logger = spd::stdout_color_mt("console");

	string query_string = "object.x = 45";
	boost::regex reg{MEMBER_ACCESS_DEF};
	boost::smatch matches;

	if (boost::regex_search(query_string, matches, reg , boost::match_extra))
	{	
		for (int i=0; i < matches.size(); i++)
			for (int j=0; j< matches.captures(i).size(); j++)
				cout<<i<<","<<j<<" : "<< matches.captures(i)[j]<<endl;
	}

    preprocessor processor(file_handle);

    vector<string> processed_file = processor.process_file();
	cout<<processed_file.size()<<endl;

	for (string line : processed_file)
		cout<<"length : " << line.size()<<" "<<line<<endl;

	analyser code_analyser(processed_file);

	vector<Class_Information_Package*> package_list = code_analyser.analyse();
	
	cout<<"Package list size : "<<package_list.size()<<endl;
	for (int i=0; i< package_list.size() -1; i++)
	{
		cout<<"Class Identified : " << package_list[i]->get_name()<<endl;
		std::unordered_set<string> methods = package_list[i]->get_methods_set();
		map<string,int> members = package_list[i]->get_data_members();
		vector<int> data_accessess = package_list[i]->get_data_accesses();

		cout<<"Following functions in the class have been identified\n";
		for (std::unordered_set<string>::iterator it = methods.begin(); it!=methods.end(); it++)
			cout<<(*it)<<endl;

		
		cout<<"Following members in the class have been identified\n";
		for (map<string,int>::iterator it= members.begin(); it!=members.end(); it++)
		{
			cout<<it->first<<endl;
		}

		cout<<"Following member access have been found\n";
		for (int class_idx : data_accessess)
			cout<<class_idx<<" ";
		cout<<endl;

		cout<<" --------              --------------------------"<<"\n\n";
	}

	for (int i=0; i< package_list.size(); i++)
		cout<<package_list[i]->get_name()<<" "<<package_list[i]->get_id()<<endl;

	c_and_k computer;
	computer.set_package_list(package_list);
	computer._init_();
	computer.compute_metrics();
}
