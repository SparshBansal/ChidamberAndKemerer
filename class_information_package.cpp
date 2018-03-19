#include "class_information_package.h"

// constructor 
Class_Information_Package::Class_Information_Package()
{
	this->_id = -1;
	this->name = "";

	this->data_accessess.clear();

	this->self_method_calls.clear();
	this->out_method_calls.clear();

	this->parents.clear();
}

Class_Information_Package::Class_Information_Package(int _id , std::string name)
{
	this->_id = _id;
	this->name = name;

	this->data_accessess.clear();

	this->self_method_calls.clear();
	this->out_method_calls.clear();

	this->parents.clear();
}

// Getter methods
int Class_Information_Package::get_id()
{
	return this->_id;
}

std::string Class_Information_Package::get_name()
{
	return this->name;
}

std::vector<int>& Class_Information_Package::get_parents()
{
	return this->parents;
}

std::vector<int>& Class_Information_Package::get_self_method_calls()
{
	return this->self_method_calls;
}

std::vector<int>& Class_Information_Package::get_out_method_calls()
{
	return this->out_method_calls;
}

std::vector<int>& Class_Information_Package::get_data_accesses()
{
	return this->data_accessess;
}

std::unordered_set<std::string>& Class_Information_Package::get_methods_set()
{
	return this->methods;
}

int Class_Information_Package::get_scope_id()
{
	return this->scope_id;
}

//
// Setter methods
void Class_Information_Package::set_name(std::string name)
{
	this->name = name;
}

void Class_Information_Package::set_id(int _id)
{
	this->_id = _id;
}

void Class_Information_Package::set_scope_id(int _id)
{
	this->scope_id = _id;
}
