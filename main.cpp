#include "reg_expressions.h"
#include "preprocessor.h"
#include "analyser.h"

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

	string query_string = "class ABC :: public BCD , private CDE ,  protected EFG , private GHD, protected LHM";
	boost::regex reg{CLASS_DEF};
	boost::smatch matches;

	if (boost::regex_match(query_string, matches, reg , boost::match_extra))
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
		
		cout<<"Following functions in the class have been identified\n";
		for (std::unordered_set<string>::iterator it = methods.begin(); it!=methods.end(); it++)
			cout<<(*it)<<endl;

		cout<<" --------              --------------------------"<<"\n\n";
	}
}
