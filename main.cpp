#include "reg_expressions.h"

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
    string query_string= "void func (int a , int b)";
    try_to_match(query_string , FUNCTION_DEF);
}