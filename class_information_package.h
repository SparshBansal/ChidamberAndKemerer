#ifndef __CLASS_INFORMATION_PACKAGE_H_INCLUDED__
#define __CLASS_INFORMATION_PACKAGE_H_INCLUDED__

#include <vector>
#include <string>

class Class_Information_Package
{
  private:
    int _id;
    string name;

    vector<int> parents;
    vector<int> method_calls;
    vector<int> data_accessess;

  public:
    
    Class_Information_Package();

    // getter methods
    string get_name();
    int get_id();
    vector<int> get_parents();
    vector<int> get_method_calls();
    vector<int> get_data_accesses();
}

#endif