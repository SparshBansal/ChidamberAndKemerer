#ifndef __CLASS_INFORMATION_PACKAGE_H_INCLUDED__
#define __CLASS_INFORMATION_PACKAGE_H_INCLUDED__

#include <vector>
#include <unordered_set>
#include <string>

class Class_Information_Package
{
  private:
    int _id, scope_id;
	std::string name;

	std::vector<int> parents;
	std::unordered_set<std::string> methods;

	// methods calls 
	std::vector<int> self_method_calls;
	std::vector<int> out_method_calls;
	
	// member accesses
	std::vector<int> data_accessess;

  public:
    
    Class_Information_Package();
	Class_Information_Package(int _id, std::string name);

    // getter methods
	std::string get_name();
    int get_id();
	int get_scope_id();
	std::vector<int>& get_parents();
	std::unordered_set<std::string>& get_methods_set();

	std::vector<int>& get_self_method_calls();
	std::vector<int>& get_out_method_calls();
	std::vector<int>& get_data_accesses();

	// setter methods
	void set_name(std::string name);
	void set_id(int _id);
	void set_scope_id(int _id);
};

#endif
