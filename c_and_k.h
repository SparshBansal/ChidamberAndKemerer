#ifndef __C_AND_K_INCLUDED__
#define __C_AND_K_INCLUDED__

#include "spdlog/spdlog.h"
#include "class_information_package.h"

#include <iostream>
#include <vector>
#include <map>

namespace spd = spdlog;

class c_and_k
{
	private:
		std::vector<Class_Information_Package*> package_list;
		std::map<std::string, int> class_map;
		std::shared_ptr<spd::logger> console;

		// graph of classes
		std::vector<std::vector<int>> graph;
		std::vector<int> indegree,outdegree;

		double depth_of_inheritance_tree();

	public:
		c_and_k();

		// getter methods
		std::vector<Class_Information_Package*> get_package_list();
		
		// setter methods
		void set_package_list(std::vector<Class_Information_Package*> package_list);

		// setup method
		void _init_();

		// metrics computation
		double* compute_metrics();

};


#endif
