#ifndef __CLASS_INFORMATION_PACKAGE_H_INCLUDED__
#define __CLASS_INFORMATION_PACKAGE_H_INCLUDED__

#include <vector>
#include <string>

class Class_Information_Package
{
  private:
    int _id;
	std::string name;

	std::vector<int> parents;
	std::vector<int> method_calls;
	std::vector<int> data_accessess;

  public:
    
    Class_Information_Package();

    // getter methods
	std::string get_name();
    int get_id();
	std::vector<int> get_parents();
	std::vector<int> get_method_calls();
	std::vector<int> get_data_accesses();
};

#endif
