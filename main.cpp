#include "reg_expressions.h"
#include "preprocessor.h"

#include <iostream>
#include <regex>

using namespace std;

void try_to_match(string query,string expression)
{
    regex exp(expression);

    if (regex_match(query, exp))
        cout<<"Regex found\n";
    else
        cout<<"Regex not found\n";
}

int main()
{
    string file_handle = "code.txt";
    preprocessor processor(file_handle);

    vector<string> processed_file = processor.process_file();
	cout<<processed_file.size()<<endl;
	for (string line : processed_file)
		cout<<"length : " << line.size()<<" "<<line<<endl;
}
